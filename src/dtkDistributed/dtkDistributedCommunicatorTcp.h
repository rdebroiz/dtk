/* dtkDistributedCommunicatorTcp.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 16:50:54 2010 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. oct.  4 15:04:43 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 75
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCOMMUNICATORTCP_H
#define DTKDISTRIBUTEDCOMMUNICATORTCP_H

#include "dtkDistributedCommunicator.h"
#include "dtkDistributedSocket.h"

#include <dtkCore/dtkAbstractDataSerializer.h>

#include <QtNetwork/QAbstractSocket>

class dtkDistributedCommunicatorTcpPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedCommunicatorTcp : public dtkDistributedCommunicator
{
    Q_OBJECT

public:
     dtkDistributedCommunicatorTcp(void);
    ~dtkDistributedCommunicatorTcp(void);

public:
    dtkDistributedCommunicatorTcp(const dtkDistributedCommunicatorTcp& other);
    dtkDistributedCommunicatorTcp& operator=(const dtkDistributedCommunicatorTcp& other);

public:
    void   initialize(void);
    bool  initialized(void);
    void uninitialize(void);

    int rank(void);
    int size(void);

    void   barrier(void);
    void      send(void *data,             qint64 size, DataType dataType, qint16 target, int tag);
    void   receive(void *data,             qint64 size, DataType dataType, qint16 source, int tag);
    void broadcast(void *data,             qint64 size, DataType dataType, qint16 source);
    void    gather(void *send, void *recv, qint64 size, DataType dataType, qint16 target, bool all = false);
    void   scatter(void *send, void *recv, qint64 size, DataType dataType, qint16 source);
    void    reduce(void *send, void *recv, qint64 size, DataType dataType, OperationType operationType, qint16 target, bool all = false);


    void                 connectToHost(const QString &host , qint16 port);
    void            disconnectFromHost();
    dtkDistributedSocket *socket();

    void    send(dtkAbstractData *data, qint16 target, int tag);
    void receive(dtkAbstractData *&data, qint16 source, int tag);

    void      send(const QString &s, qint16 target, int tag) ;
    void      send(QByteArray &a, qint16 target, int tag) ;

    void   receive(QString &s, qint16 source, int tag) ;
    void   receive(QByteArray &a, qint16 source, int tag) ;

    void flush();

private:
    dtkDistributedCommunicatorTcpPrivate *d;
};

#endif
