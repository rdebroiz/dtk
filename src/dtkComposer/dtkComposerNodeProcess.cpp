/* dtkComposerNodeProcess.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/29 11:17:21
 * Version: $Id$
 * Last-Updated: Tue Jul  3 13:55:08 2012 (+0200)
 *           By: tkloczko
 *     Update #: 264
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
// dtkComposerNodeProcessPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeProcessPrivate
{
public:
    dtkComposerTransmitterReceiver<qlonglong> receiver_integer_0;
    dtkComposerTransmitterReceiver<qlonglong> receiver_integer_1;
    dtkComposerTransmitterReceiver<double> receiver_real;
    dtkComposerTransmitterReceiver<dtkAbstractData *> receiver_data;
    dtkComposerTransmitterReceiver<QString> receiver_string;
    dtkComposerTransmitterReceiver<dtkAbstractData *> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkAbstractData *> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<qlonglong> emitter_integer;
    dtkComposerTransmitterEmitter<double> emitter_real;
    dtkComposerTransmitterEmitter<dtkAbstractData *> emitter_data;

public:
    dtkAbstractProcess *process;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeProcess implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeProcess::dtkComposerNodeProcess(void) : dtkComposerNodeLeafProcess(), d(new dtkComposerNodeProcessPrivate)
{
    this->appendReceiver(&(d->receiver_string));
    this->appendReceiver(&(d->receiver_integer_0));
    this->appendReceiver(&(d->receiver_integer_1));
    this->appendReceiver(&(d->receiver_real));
    this->appendReceiver(&(d->receiver_data));
    this->appendReceiver(&(d->receiver_lhs));
    this->appendReceiver(&(d->receiver_rhs));

    this->appendEmitter(&(d->emitter_integer));
    this->appendEmitter(&(d->emitter_real));
    this->appendEmitter(&(d->emitter_data));

    d->process = NULL;
}

dtkComposerNodeProcess::~dtkComposerNodeProcess(void)
{
    if (d->process)
        delete d->process;

    delete d;

    d = NULL;
}

bool dtkComposerNodeProcess::isAbstractProcess(void) const
{
    return true;
}

QString dtkComposerNodeProcess::abstractProcessType(void) const 
{
    return "dtkAbstractProcess";
}

void dtkComposerNodeProcess::run(void)
{

    if (this->process())
        d->process = this->process();

    if (!d->process) {
        dtkWarn() << "no process, abort "<<  this->currentImplementation();
        return;
    }

    if (!d->receiver_string.isEmpty())
        d->process->read(d->receiver_string.data());

    if (!d->receiver_integer_0.isEmpty())
        d->process->setParameter((int)d->receiver_integer_0.data(), 0);

    if (!d->receiver_integer_1.isEmpty())
        d->process->setParameter((int)d->receiver_integer_1.data(), 1);

    if (!d->receiver_real.isEmpty())
        d->process->setParameter(d->receiver_real.data());

    if (!d->receiver_data.isEmpty())
        d->process->setInput(d->receiver_data.data());

    if (!d->receiver_lhs.isEmpty())
        d->process->setInput(d->receiver_lhs.data(), 0);

    if (!d->receiver_rhs.isEmpty())
        d->process->setInput(d->receiver_rhs.data(), 1);

    int i = d->process->run();

    d->emitter_integer.setData(i);

    // if (d->process->output())
    //     d->emitter_real.setData(*static_cast<double *>(d->process->data(0)));

    d->emitter_data.setData(d->process->output());
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
        return "string";

    if(port == 1)
        return "integer";

    if(port == 2)
        return "integer";

    if(port == 3)
        return "real";

    if(port == 4)
        return "data";

    if(port == 5)
        return "lhs";

    if(port == 6)
        return "rhs";

    return dtkComposerNodeLeaf::inputLabelHint(port);
}

QString dtkComposerNodeProcess::outputLabelHint(int port)
{
    if(port == 0)
        return "integer";

    if(port == 1)
        return "real";

    if(port == 2)
        return "data";

    return dtkComposerNodeLeaf::outputLabelHint(port);
}
