/* dtkDistributedServerDaemon.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 11:28:54 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr  3 16:05:30 2012 (+0200)
 *           By: tkloczko
 *     Update #: 682
 */

/* Commentary: 
 * 
 * debug logging: use dtkLog() << "message" or qDebug() << "message"
 *   run logging: use dtkDistributedServiceBase::instance()->logMessage("message");
 */

/* Change log:
 * 
 */

#include "dtkDistributedServerDaemon.h"
#include "dtkDistributedServerManager.h"
#include "dtkDistributedServerManagerOar.h"
#include "dtkDistributedServerManagerTorque.h"
#include "dtkDistributedService.h"
#include "dtkDistributedSocket.h"

#include <dtkCore/dtkGlobal.h>

#include <dtkLog/dtkLog.h>

#define DTK_DEBUG_SERVER_DAEMON 0

class dtkDistributedServerDaemonPrivate
{
public:
    dtkDistributedServerManager *manager;

    QMap<int, dtkDistributedSocket*> sockets;
};

dtkDistributedServerDaemon::dtkDistributedServerDaemon(quint16 port, QObject *parent) : QTcpServer(parent), d(new dtkDistributedServerDaemonPrivate)
{
    d->manager = NULL;

    if (!this->listen(QHostAddress::Any, port)) {
        qDebug() << "Can't listen on port"  << port << ", aborting";
        exit(1);
    } else
        qDebug() << "OK, server is waiting for incoming connection on port"  << port ;

    dtkDistributedServiceBase::instance()->logMessage("Server daemon listening on port " + QString::number(port));
}

dtkDistributedServerDaemon::~dtkDistributedServerDaemon(void)
{
    delete d;

    d = NULL;
}

dtkDistributedServerManager * dtkDistributedServerDaemon::manager(void)
{
    return d->manager;
}

void dtkDistributedServerDaemon::setManager(dtkDistributedServerManager::Type type)
{
    switch(type) {
    case dtkDistributedServerManager::Oar:
        d->manager = new dtkDistributedServerManagerOar;
        break;
    case dtkDistributedServerManager::Torque:
        d->manager = new dtkDistributedServerManagerTorque;
        break;
    default:
        break;
    }
}

void dtkDistributedServerDaemon::incomingConnection(int descriptor)
{
#if defined(DTK_DEBUG_SERVER_DAEMON)
    qDebug() << DTK_PRETTY_FUNCTION << "-- Connection -- " << descriptor ;
#endif

    dtkDistributedSocket *socket = new dtkDistributedSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(discard()));
    socket->setSocketDescriptor(descriptor);

    dtkDistributedServiceBase::instance()->logMessage("New connection");
}

//! Wait for incomming connection
/*! Warning, in its current state, this method may never return if no
 *  connection is established.
 * 
 * \param rank, the identifier of the slave on the cluster side.
 */
void dtkDistributedServerDaemon::waitForConnection(int rank)
{
    while(!d->sockets.keys().contains(rank))
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
}

QByteArray dtkDistributedServerDaemon::waitForData(int rank)
{
    dtkDistributedSocket *socket = d->sockets.value(rank, NULL);

    if(!socket) {
        qDebug() << "WARN: no socket found for rank " << rank;
        return QByteArray();
    }

    socket->blockSignals(true);

    dtkDistributedMessage *data = NULL;

    if (socket->waitForReadyRead(30000))
        data = socket->parseRequest();
    else
        qDebug() << "WARN: data not ready for rank " << rank;

    socket->blockSignals(false);

    if (data) {
        return data->content();
    } else {
        dtkWarn() << "Message not allocated - return void QByteArray";
        return QByteArray();
    }
}

void dtkDistributedServerDaemon::read(void)
{
    dtkDistributedSocket *socket = (dtkDistributedSocket *)sender();
    dtkDistributedMessage *msg = socket->parseRequest();

    QByteArray r;
    QString jobid;

    switch (msg->method()) {
    case dtkDistributedMessage::STATUS:
        r = d->manager->status();
        socket->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::OKSTATUS,"",-2,r.size(),"json",r));
        // GET status is from the controller, store the socket in sockets using rank=-1
        if (!d->sockets.contains(dtkDistributedMessage::CONTROLLER_RANK))
            d->sockets.insert(dtkDistributedMessage::CONTROLLER_RANK, socket);
        break;

    case dtkDistributedMessage::NEWJOB:
        jobid = d->manager->submit(msg->content());
#if defined(DTK_DEBUG_SERVER_DAEMON)
        qDebug() << DTK_PRETTY_FUNCTION << jobid;
#endif
        socket->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::OKJOB, jobid));
        break;

    case dtkDistributedMessage::ENDJOB:
#if defined(DTK_DEBUG_SERVER_DAEMON)
        qDebug() << DTK_PRETTY_FUNCTION << "Job ended " << msg->jobid();
#endif
        //TODO: check if exists
        d->sockets[dtkDistributedMessage::CONTROLLER_RANK]->sendRequest(msg);
        break;

    case dtkDistributedMessage::SETRANK:

#if defined(DTK_DEBUG_SERVER_DAEMON)
        qDebug() << DTK_PRETTY_FUNCTION << "connected remote is of rank " << msg->rank();
#endif
        d->sockets.insert(msg->rank(), socket);
        // rank 0 is alive, warn the controller
        if (msg->rank() == 0 && d->sockets.contains(dtkDistributedMessage::CONTROLLER_RANK))
            (d->sockets[dtkDistributedMessage::CONTROLLER_RANK])->sendRequest(msg);

        break;

    case dtkDistributedMessage::DELJOB:
        jobid = msg->jobid();
        if (d->manager->deljob(jobid).startsWith("OK"))
            socket->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::OKDEL, jobid) );
        else
            socket->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::ERRORDEL, jobid) );
        break;

    case dtkDistributedMessage::DATA:
        msg->addHeader("x-forwarded-for", QString::number(d->sockets.key(socket)));
        (d->sockets[msg->rank()])->sendRequest(msg);
        break;

    default:
        qDebug() << DTK_PRETTY_FUNCTION << "WARNING: Unknown data";
    };

    delete msg;
    if (socket->bytesAvailable() > 0)
        this->read();
}

void dtkDistributedServerDaemon::discard(void)
{
#if defined(DTK_DEBUG_SERVER_DAEMON)
    qDebug() << DTK_PRETTY_FUNCTION << "-- Disconnection --";
#endif

    dtkDistributedSocket *socket = (dtkDistributedSocket *)sender();
    socket->deleteLater();

    dtkDistributedServiceBase::instance()->logMessage("Connection closed");
}
