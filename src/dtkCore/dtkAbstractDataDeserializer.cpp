/* dtkAbstractDataSerializer.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: lun. oct. 17 13:20:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 11:40:22 2012 (+0200)
 *           By: tkloczko
 *     Update #: 17
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkAbstractData.h"
#include "dtkAbstractDataDeserializer.h"
#include "dtkAbstractDataDeserializer_p.h"

// /////////////////////////////////////////////////////////////////
// dtkAbstractDataDeserializer implementation
// /////////////////////////////////////////////////////////////////

dtkAbstractDataDeserializer::dtkAbstractDataDeserializer(void) : dtkAbstractObject(*new dtkAbstractDataDeserializerPrivate(this), 0)
{
    DTK_D(dtkAbstractDataDeserializer);

    d->enabled = false;
}

dtkAbstractDataDeserializer::dtkAbstractDataDeserializer(const dtkAbstractDataDeserializer& other) : dtkAbstractObject(*new dtkAbstractDataDeserializerPrivate(*other.d_func()), other)
{

}

dtkAbstractDataDeserializer::~dtkAbstractDataDeserializer(void)
{

}

bool dtkAbstractDataDeserializer::enabled(void) const
{
    DTK_D(const dtkAbstractDataDeserializer);

    return d->enabled;
}

void dtkAbstractDataDeserializer::enable(void)
{
    DTK_D(dtkAbstractDataDeserializer);

    d->enabled = true;
}

void dtkAbstractDataDeserializer::disable(void)
{
    DTK_D(dtkAbstractDataDeserializer);

    d->enabled = false;
}

dtkAbstractData *dtkAbstractDataDeserializer::data(void) const
{
    DTK_D(const dtkAbstractDataDeserializer);

    return d->data;
}

void dtkAbstractDataDeserializer::setData(dtkAbstractData *data)
{
    DTK_D(dtkAbstractDataDeserializer);

    d->data = data;
}

bool dtkAbstractDataDeserializer::deserialize(const QByteArray &array)
{
    DTK_UNUSED(array);
    return false ;
}

void dtkAbstractDataDeserializer::setProgress(int value)
{
    emit progressed (value);
}

