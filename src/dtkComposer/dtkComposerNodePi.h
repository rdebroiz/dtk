/* dtkComposerNodePi.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:58:13 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 12:58:32 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEPI_H
#define DTKCOMPOSERNODEPI_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodePiPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodePi : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodePi(void);
    ~dtkComposerNodePi(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "pi";
    }

    inline QString titleHint(void) {
        return "Pi";
    }

    inline QString labelHint(int port) {
        return "value";
    }

private:
    dtkComposerNodePiPrivate *d;
};

#endif
