/* dtkComposerNodeControlFor.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:14:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. janv. 13 08:43:59 2015 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 286
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControlForEach.h"

#include "dtkComposerNodeMetaData.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProxy.h"

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterProxy.h"
#include "dtkComposerTransmitterProxyLoop.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlForEachPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlForEachPrivate
{
public:
    dtkComposerNodeMetaData header_md;
    dtkComposerNodeProxy header;

    dtkComposerNodeMetaData footer_md;
    dtkComposerNodeProxy footer;

    dtkComposerNodeMetaData body_block_md;
    dtkComposerNodeComposite body_block;

public:
    dtkComposerTransmitterReceiverVariant header_rcv;

    dtkComposerTransmitterProxy              block_container;
    dtkComposerTransmitterEmitter<qlonglong> block_size;
    dtkComposerTransmitterEmitter<qlonglong> block_index;
    dtkComposerTransmitterEmitterVariant     block_item;

public:
    qlonglong counter;
    qlonglong size;

    bool first_iteration;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlForEach implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlForEach::dtkComposerNodeControlForEach(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlForEachPrivate)
{
    d->header_md.setTitle("Header");
    d->header_md.setKind("proxy");
    d->header_md.setType("proxy");
    d->header_md.appendInputLabel("container");

    d->header.removeEmitter(0);
    d->header.removeReceiver(0);
    d->header.appendReceiver(&(d->header_rcv));
    d->header.setAsHeader(true);
    d->header.setNodeMetaData(&d->header_md);

    d->footer_md.setTitle("Footer");
    d->footer_md.setKind("proxy");
    d->footer_md.setType("proxy");

    d->footer.removeReceiver(0);
    d->footer.removeEmitter(0);
    d->footer.setAsFooter(true);
    d->footer.setNodeMetaData(&d->footer_md);

    d->body_block_md.setTitle("Body");
    d->body_block_md.setKind("composite");
    d->body_block_md.setType("composite");
    d->body_block_md.appendInputLabel("container");
    d->body_block_md.appendInputLabel("size");
    d->body_block_md.appendInputLabel("index");
    d->body_block_md.appendInputLabel("item");

    d->body_block.appendReceiver(&(d->block_container));
    d->body_block.appendReceiver(&(d->block_size));
    d->body_block.appendReceiver(&(d->block_index));
    d->body_block.appendReceiver(&(d->block_item));
    d->body_block.setNodeMetaData(&d->body_block_md);

    d->block_container.appendPrevious(&d->header_rcv);
    d->header_rcv.appendNext(&d->block_container);

    d->counter = 0;
    d->size = -1;
}

dtkComposerNodeControlForEach::~dtkComposerNodeControlForEach(void)
{
    delete d;

    d = NULL;
}

int dtkComposerNodeControlForEach::blockCount(void)
{
    return 1;
}

dtkComposerNodeLeaf *dtkComposerNodeControlForEach::header(void)
{
    return &(d->header);
}

dtkComposerNodeLeaf *dtkComposerNodeControlForEach::footer(void)
{
    return &(d->footer);
}

dtkComposerNodeComposite *dtkComposerNodeControlForEach::block(int id)
{
    if(id == 0)
        return &(d->body_block);

    return NULL;
}

void dtkComposerNodeControlForEach::setInputs(void)
{
    for(dtkComposerTransmitterProxyLoop *t : this->inputTwins()) {
        t->disableLoopMode();
    }
    d->first_iteration = true;
}

void dtkComposerNodeControlForEach::setOutputs(void)
{
    if (d->first_iteration) {
        for(dtkComposerTransmitterProxyLoop *t : this->outputTwins()) {
            t->twin()->enableLoopMode();
        }
        d->first_iteration = false;
    }
    for(dtkComposerTransmitterProxyLoop *t : this->outputTwins()) {
        t->twin()->setVariant(t->variant());
    }
}

void dtkComposerNodeControlForEach::setVariables(void)
{
    //d->block_item.setData(d->container->at(d->counter));
    d->block_index.setData((d->counter)++);
}

int dtkComposerNodeControlForEach::selectBranch(void)
{
    return static_cast<int>(!((d->counter) < d->size));
}

void dtkComposerNodeControlForEach::begin(void)
{
    if (d->header_rcv.isEmpty())
        return;

    //d->container = d->header_rcv.constContainer();
    d->counter = 0;
    //d->size = d->container->count();
    d->block_size.setData(d->size);
}

void dtkComposerNodeControlForEach::end(void)
{

}
