/* dtkComposerNodeReal.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 29 10:16:48 2012 (+0100)
 *           By: tkloczko
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeReal.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

class dtkComposerNodeRealPrivate
{
public:
    dtkComposerTransmitterReceiver<qreal> *receiver;

public:    
    dtkComposerTransmitterEmitter<qreal> *emitter;
};

dtkComposerNodeReal::dtkComposerNodeReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeRealPrivate)
{
    d->receiver = new dtkComposerTransmitterReceiver<qreal>;
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerTransmitterEmitter<qreal>;
    this->appendEmitter(d->emitter);
}

dtkComposerNodeReal::~dtkComposerNodeReal(void)
{
    delete d->receiver;
    delete d->emitter;
    delete d;
    
    d = NULL;
}

void dtkComposerNodeReal::run(void)
{
    d->emitter->setData(0);
}
