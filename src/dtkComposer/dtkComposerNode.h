/* dtkComposerNode.h --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 14:24:23 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 15 16:25:57 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 39
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODE_H
#define DTKCOMPOSERNODE_H

#include "dtkComposerExport.h"

#include <QtCore>

class dtkComposerTransmitter;

// /////////////////////////////////////////////////////////////////
// dtkComposerNode declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNode
{
public: 
             dtkComposerNode(void);
    virtual ~dtkComposerNode(void);

public:
    void appendEmitter(dtkComposerTransmitter *emitter);
    void removeEmitter(dtkComposerTransmitter *emitter);

    void appendReceiver(dtkComposerTransmitter *receiver);
    void removeReceiver(dtkComposerTransmitter *receiver);

    QList<dtkComposerTransmitter *> emitters(void);
    QList<dtkComposerTransmitter *> receivers(void);

public:
    virtual QString type(void) = 0;

public:
    virtual QString titleHint(void);
    virtual QString labelHint(int port);

private:
    dtkComposerNodePrivate *d;
};

#endif
