/* @(#)dtkComposerNodeRemote.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 15:15:12
 * Version: $Id$
 * Last-Updated: mer. juin 13 16:35:55 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 32
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEREMOTE_H
#define DTKCOMPOSERNODEREMOTE_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeLeaf.h"

#include <QDomDocument>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemote declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRemotePrivate;
class dtkDistributedCommunicator;
class dtkDistributedController;
class dtkDistributedSlave;

class DTKCOMPOSER_EXPORT dtkComposerNodeRemote : public QObject, public dtkComposerNodeComposite
{
    Q_OBJECT

public:
             dtkComposerNodeRemote(void);
    virtual ~dtkComposerNodeRemote(void);

public:
    QString type(void);

public:
    QString titleHint(void);

public slots:
    void onJobStarted(QString id);

public:
    void setComposition(QDomDocument document);
    void setController(dtkDistributedController  *controller);
    void setCommunicator(dtkDistributedCommunicator  *communicator);
    void setSlave(dtkDistributedSlave *slave);
    void setJob(QString jobid);

public:
    bool isSlave(void);

public:
    virtual void begin(void);
    virtual void end(void);

private:
    dtkComposerNodeRemotePrivate *d;
};





// /////////////////////////////////////////////////////////////////
// Distributed submit
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRemoteSubmitPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeRemoteSubmit : public QObject, public dtkComposerNodeLeaf
{
    Q_OBJECT

public:
     dtkComposerNodeRemoteSubmit(void);
    ~dtkComposerNodeRemoteSubmit(void);

public:
    void run(void);

public slots:
    void onJobQueued(QString id);

public:
    inline QString type(void) {
        return "remoteSubmit";
    }

    inline QString titleHint(void) {
        return "Remote Submit";
    }


public:
    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "cluster";
        else if (port == 1)
            return "nodes";
        else if (port == 2)
            return "cores";
        else if (port == 3)
            return "walltime";
        else
            return "value";
    }

public:
    inline QString outputLabelHint(int) {
        return "jobid";
    }

protected:
    dtkComposerNodeRemoteSubmitPrivate *d;
};


#endif /* DTKCOMPOSERNODEREMOTE_H */
