/* dtkComposerNodeProcess.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/29 11:17:21
 * Version: $Id$
 * Last-Updated: Tue Apr 24 19:34:35 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 224
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeProcess.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkLog/dtkLog.h>

#include <dtkCore>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeProcessPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeProcessPrivate
{
public:
    dtkComposerTransmitterReceiver<qlonglong> *receiver_integer_0;
    dtkComposerTransmitterReceiver<qlonglong> *receiver_integer_1;
    dtkComposerTransmitterReceiver<double> *receiver_real;
    dtkComposerTransmitterReceiver<dtkAbstractData *> *receiver_data;
    dtkComposerTransmitterReceiver<QString> *receiver_type;

public:
    dtkComposerTransmitterEmitter<qlonglong> *emitter_integer;
    dtkComposerTransmitterEmitter<double> *emitter_real;
    dtkComposerTransmitterEmitter<dtkAbstractData *>   *emitter_data;

public:
    dtkAbstractProcess *process;

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeProcess implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeProcess::dtkComposerNodeProcess(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeProcessPrivate)
{
    d->receiver_type = new dtkComposerTransmitterReceiver<QString>(this);
    this->appendReceiver(d->receiver_type);

    d->receiver_integer_0 = new dtkComposerTransmitterReceiver<qlonglong>(this);
    this->appendReceiver(d->receiver_integer_0);

    d->receiver_integer_1 = new dtkComposerTransmitterReceiver<qlonglong>(this);
    this->appendReceiver(d->receiver_integer_1);

    d->receiver_real = new dtkComposerTransmitterReceiver<double>(this);
    this->appendReceiver(d->receiver_real);

    d->receiver_data = new dtkComposerTransmitterReceiver<dtkAbstractData *>(this);
    this->appendReceiver(d->receiver_data);

    d->emitter_integer = new dtkComposerTransmitterEmitter<qlonglong>(this);
    this->appendEmitter(d->emitter_integer);

    d->emitter_real = new dtkComposerTransmitterEmitter<double>(this);
    this->appendEmitter(d->emitter_real);

    d->emitter_data = new dtkComposerTransmitterEmitter<dtkAbstractData *>(this);
    this->appendEmitter(d->emitter_data);
}

dtkComposerNodeProcess::~dtkComposerNodeProcess(void)
{
    delete d->receiver_type;
    delete d->receiver_integer_0;
    delete d->receiver_integer_1;
    delete d->receiver_real;
    delete d->receiver_data;

    delete d->emitter_data;
    delete d->emitter_integer;
    delete d->emitter_real;

    delete d;

    d = NULL;
}

void dtkComposerNodeProcess::run(void)
{
    if (d->receiver_type->isEmpty()) {
        dtkWarn() << "no type speficied in process node! " ;
        return;
    }

    d->process = dtkAbstractProcessFactory::instance()->create(d->receiver_type->data());

    if (!d->process) {
        dtkWarn() << "no process, abort "<<  d->receiver_type->data();
        return;
    }

    if (!d->receiver_integer_0->isEmpty())
        d->process->setParameter((int)d->receiver_integer_0->data(), 0);

    if (!d->receiver_integer_1->isEmpty())
        d->process->setParameter((int)d->receiver_integer_1->data(), 1);

    if (!d->receiver_real->isEmpty())
        d->process->setParameter(d->receiver_real->data());

    if (!d->receiver_data->isEmpty()) {
        d->process->setInput(d->receiver_data->data());
    }

    int i = d->process->run();

    d->emitter_integer->setData(i);

    if (d->process->data(0))
        d->emitter_real->setData(*static_cast<double *>(d->process->data(0)));

    d->emitter_data->setData(d->process->output());
}

QString dtkComposerNodeProcess::type(void)
{
    return "process";
}

QString dtkComposerNodeProcess::titleHint(void)
{
    return "Process";
}

QString dtkComposerNodeProcess::inputLabelHint(int port)
{
    if(port == 0)
        return "type";

    if(port == 1)
        return "integer";

    if(port == 2)
        return "integer";

    if(port == 3)
        return "real";

    if(port == 4)
        return "data";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeProcess::outputLabelHint(int port)
{
    if(port == 0)
        return "integer";

    if(port == 1)
        return "real";

    if(port == 2)
        return "data";

    return dtkComposerNode::outputLabelHint(port);
}
