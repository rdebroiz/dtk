/* dtkComposerNodeControlFor.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:14:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed May  9 09:00:25 2012 (+0200)
 *           By: tkloczko
 *     Update #: 90
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControlForEach.h"

#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProxy.h"

#include "dtkComposerTransmitter.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlForEachPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlForEachPrivate
{
public:    
    dtkComposerNodeProxy header;
    dtkComposerNodeProxy footer;

    dtkComposerNodeComposite body_block;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlForEach implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlForEach::dtkComposerNodeControlForEach(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlForEachPrivate)
{
    d->header.removeEmitter(0);
    d->header.setInputLabelHint("container", 0); 
    d->header.setAsHeader(true);

    d->footer.removeReceiver(0);
    d->footer.removeEmitter(0);
    d->footer.setAsFooter(true);

    d->body_block.setTitleHint("Body");
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
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControlForEach::setOutputs(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControlForEach::setVariables(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

int dtkComposerNodeControlForEach::selectBranch(void)
{
    return -1;
}

void dtkComposerNodeControlForEach::begin(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControlForEach::end(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

QString dtkComposerNodeControlForEach::type(void)
{
    return "foreach";
}

QString dtkComposerNodeControlForEach::titleHint(void)
{
    return "For Each";
}
