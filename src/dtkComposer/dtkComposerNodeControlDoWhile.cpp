/* dtkComposerNodeControlDoWhile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sat Feb 25 00:02:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 21 15:15:50 2012 (+0100)
 *           By: tkloczko
 *     Update #: 46
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControlDoWhile.h"

#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProxy.h"

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlDoWhilePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlDoWhilePrivate
{
public:
    dtkComposerNodeProxy *header;
    dtkComposerNodeProxy *footer;

    dtkComposerNodeComposite *cond_block;
    dtkComposerNodeComposite *body_block;

public:
    dtkComposerTransmitterReceiver<bool> cond;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlDoWhile implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlDoWhile::dtkComposerNodeControlDoWhile(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlDoWhilePrivate)
{
    d->header = new dtkComposerNodeProxy;
    delete d->header->removeReceiver(0);
    delete d->header->removeEmitter(0);
    d->header->setAsHeader(true);

    d->footer = new dtkComposerNodeProxy;
    delete d->footer->removeReceiver(0);
    delete d->footer->removeEmitter(0);
    d->footer->setAsFooter(true);

    d->cond_block = new dtkComposerNodeComposite;
    d->cond_block->setTitleHint("Conditional");
    d->cond_block->appendEmitter(&(d->cond));
    d->cond_block->setOutputLabelHint("cond", 0);

    d->body_block = new dtkComposerNodeComposite;
    d->body_block->setTitleHint("Body");
}

dtkComposerNodeControlDoWhile::~dtkComposerNodeControlDoWhile(void)
{
    delete d->header;
    delete d->footer;
    delete d->cond_block;
    delete d->body_block;
    delete d;

    d = NULL;
}

int dtkComposerNodeControlDoWhile::blockCount(void)
{
    return 2;
}

dtkComposerNodeLeaf *dtkComposerNodeControlDoWhile::header(void)
{
    return d->header;
}

dtkComposerNodeLeaf *dtkComposerNodeControlDoWhile::footer(void)
{
    return d->footer;
}

dtkComposerNodeComposite *dtkComposerNodeControlDoWhile::block(int id)
{
    if(id == 0)
        return d->body_block;

    if(id == 1)
        return d->cond_block;

    return NULL;
}

void dtkComposerNodeControlDoWhile::setInputs(void)
{
    foreach(dtkComposerTransmitterVariant *v, this->inputTwins()) {
        v->setTwinned(false);
        v->setData(v->data());
        v->setTwinned(true);        
    }
}

void dtkComposerNodeControlDoWhile::setConditions(void)
{

}

void dtkComposerNodeControlDoWhile::setOutputs(void)
{
    foreach(dtkComposerTransmitterVariant *v, this->outputTwins())
        v->twin()->setData(v->data());
}

void dtkComposerNodeControlDoWhile::setVariables(void)
{

}

int dtkComposerNodeControlDoWhile::selectBranch(void)
{
    return (int)(!d->cond.data());
}

void dtkComposerNodeControlDoWhile::begin(void)
{

}

void dtkComposerNodeControlDoWhile::end(void)
{

}

QString dtkComposerNodeControlDoWhile::type(void)
{
    return "do while";
}

QString dtkComposerNodeControlDoWhile::titleHint(void)
{
    return "Do While";
}
