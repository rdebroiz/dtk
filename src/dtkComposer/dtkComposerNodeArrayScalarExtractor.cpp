/* dtkComposerNodeArrayScalarExtractor.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep 10 10:01:20 2012 (+0200)
 *           By: tkloczko
 *     Update #: 209
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeArrayScalarExtractor.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkContainer/dtkContainerVector.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarExtractorPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarExtractorPrivate
{
public:
    dtkComposerTransmitterReceiverVector<qreal> receiver_array;
    dtkComposerTransmitterReceiver<qlonglong>   receiver_index;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_value;

public:
    qreal value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarExtractor implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayScalarExtractor::dtkComposerNodeArrayScalarExtractor(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarExtractorPrivate)
{
    this->appendReceiver(&d->receiver_array);
    this->appendReceiver(&d->receiver_index);

    d->value = 0.;
    d->emitter_value.setData(&d->value);
    this->appendEmitter(&d->emitter_value);
}

dtkComposerNodeArrayScalarExtractor::~dtkComposerNodeArrayScalarExtractor(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeArrayScalarExtractor::inputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "array";
        break;
    case 1:
        return "index";
        break;
    default:
        break;
    }

    return "port";
}

QString dtkComposerNodeArrayScalarExtractor::outputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "value";
        break;
    default:
        break;
    }

    return "port";
}

void dtkComposerNodeArrayScalarExtractor::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty()) {

        dtkContainerVectorReal *array = d->receiver_array.data();
        qlonglong index = *d->receiver_index.data();

        if (!array) {
            dtkError() << "Input array is not defined.";
            return;
        }

        if (index >= array->count()) {
            dtkWarn() << "index > size of the input array. Zero is returned.";

        } else {
            d->value = array->at(index);

        }

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarExtractorSubArrayPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarExtractorSubArrayPrivate
{
public:
    dtkComposerTransmitterReceiverVector<qreal> receiver_array;
    dtkComposerTransmitterVariant               receiver_indices;

public:
    dtkComposerTransmitterEmitterVector<qreal> emitter_subarray;

public:
    dtkContainerVectorReal *subarray;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarExtractorSubArray implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayScalarExtractorSubArray::dtkComposerNodeArrayScalarExtractorSubArray(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarExtractorSubArrayPrivate)
{
    this->appendReceiver(&d->receiver_array);

    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong;
    d->receiver_indices.setTypes(variant_list);
    this->appendReceiver(&d->receiver_indices);

    d->subarray = new dtkContainerVectorReal();
    d->emitter_subarray.setData(d->subarray);
    this->appendEmitter(&d->emitter_subarray);
}

dtkComposerNodeArrayScalarExtractorSubArray::~dtkComposerNodeArrayScalarExtractorSubArray(void)
{
    if (d->subarray)
        delete d->subarray;

    delete d;

    d = NULL;
}

QString dtkComposerNodeArrayScalarExtractorSubArray::inputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "array";
        break;
    case 1:
        return "index array";
        break;
    default:
        break;
    }

    return "port";
}

QString dtkComposerNodeArrayScalarExtractorSubArray::outputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "subarray";
        break;
    default:
        break;
    }

    return "port";
}

void dtkComposerNodeArrayScalarExtractorSubArray::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_indices.isEmpty()) {

        dtkContainerVectorReal *array = d->receiver_array.data();
        dtkAbstractContainerWrapper *indices = d->receiver_indices.container();

        if (!array || !indices) {
            dtkError() << "Inputs are not defined.";
            return;
        }

        d->subarray->clear();
        d->subarray->reserve(indices->count());

        qlonglong index;
        for(qlonglong i = 0; i < indices->count(); ++i) {
            index = indices->at(i).value<qlonglong>();
            if (index >= array->count()) {
                dtkWarn() << "index " << i << " of indices array is greater than the size of the array. Zero is inserted.";
                d->subarray->append(0);
            } else {
                d->subarray->append(array->at(index));
            }
        }

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarExtractorArrayPartPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarExtractorArrayPartPrivate
{
public:
    dtkComposerTransmitterReceiverVector<qreal> receiver_array;
    dtkComposerTransmitterReceiver<qlonglong> receiver_from;
    dtkComposerTransmitterReceiver<qlonglong> receiver_length;

public:
    dtkComposerTransmitterEmitterVector<qreal> emitter_subarray;

public:
    dtkContainerVectorReal *subarray;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarExtractorArrayPart implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayScalarExtractorArrayPart::dtkComposerNodeArrayScalarExtractorArrayPart(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarExtractorArrayPartPrivate)
{
    this->appendReceiver(&d->receiver_array);
    this->appendReceiver(&d->receiver_from);
    this->appendReceiver(&d->receiver_length);

    d->subarray = new dtkContainerVectorReal();
    d->emitter_subarray.setData(d->subarray);
    this->appendEmitter(&d->emitter_subarray);
}

dtkComposerNodeArrayScalarExtractorArrayPart::~dtkComposerNodeArrayScalarExtractorArrayPart(void)
{
    if (d->subarray)
        delete d->subarray;

    delete d;

    d = NULL;
}

QString dtkComposerNodeArrayScalarExtractorArrayPart::inputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "array";
        break;
    case 1:
        return "from";
        break;
    case 2:
        return "length";
        break;
    default:
        break;
    }

    return "port";
}

QString dtkComposerNodeArrayScalarExtractorArrayPart::outputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "subarray";
        break;
    default:
        break;
    }

    return "port";
}

void dtkComposerNodeArrayScalarExtractorArrayPart::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_from.isEmpty()) {

        dtkContainerVectorReal *array = d->receiver_array.data();

        if (!array) {
            dtkError() << "Input array is not defined.";
            return;
        }

        qlonglong from = *d->receiver_from.data();
        if (from >= array->count()) {
            dtkWarn() << "Starting value from is greater than array size:" << from << ">=" << array->count();
            return;
        }

        qlonglong length = array->count();
        if (!d->receiver_length.isEmpty())
            length = *d->receiver_length.data();

        if (length < 0) {
            dtkWarn() << "Length value is negative:" << length << "<" << 0;
            return;
        }

        qlonglong to = qMin((from + length), array->count());

        d->subarray->clear();
        d->subarray->reserve(to - from);

        for(qlonglong i = from; i < to; ++i)
            d->subarray->append(array->at(i));

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}
