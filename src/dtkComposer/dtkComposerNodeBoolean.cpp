/* dtkComposerNodeBoolean.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 16:49:25 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Aug  9 11:19:00 2012 (+0200)
 *           By: tkloczko
 *     Update #: 38
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerMetatype.h"

#include "dtkComposerNodeBoolean.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanPrivate
{
public:
    dtkComposerTransmitterVariant receiver;

public:    
    dtkComposerTransmitterEmitter<bool> emitter;

public:
    bool value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBoolean implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeBoolean::dtkComposerNodeBoolean(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeBooleanPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Bool << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double << QVariant::String;

    d->receiver.setTypes(variant_list);
    this->appendReceiver(&d->receiver);

    d->value = false;
    d->emitter.setData(&d->value);
    this->appendEmitter(&d->emitter);
}

dtkComposerNodeBoolean::~dtkComposerNodeBoolean(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodeBoolean::run(void)
{
    if (!d->receiver.isEmpty())
        d->value = *(d->receiver.data<bool>());
}

bool dtkComposerNodeBoolean::value(void)
{
    return d->value;
}

void dtkComposerNodeBoolean::setValue(bool value)
{
    d->value = value;
}
