/* dtkDistributedGpu.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 16:23:42 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 31 20:05:14 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedGpu.h"

class dtkDistributedGpuPrivate
{
public:
    dtkDistributedNode *parent;

    dtkDistributedGpu::Architecture architecture;
    dtkDistributedGpu::Model model;
    dtkDistributedGpu::Cardinality cardinality;

    QList<dtkDistributedCore *> cores;
};

dtkDistributedGpu::dtkDistributedGpu(dtkDistributedNode *parent) : QObject(), d(new dtkDistributedGpuPrivate)
{
    d->parent = parent;
}

dtkDistributedGpu::~dtkDistributedGpu(void)
{
    delete d;

    d = NULL;
}

dtkDistributedGpu::Architecture dtkDistributedGpu::architecture(void)
{
    return d->architecture;
}

void dtkDistributedGpu::setArchitecture(Architecture arch)
{
    d->architecture = arch;
}

dtkDistributedGpu::Model dtkDistributedGpu::model(void)
{
    return d->model;
}

void dtkDistributedGpu::setModel(Model model)
{
    d->model = model;
}

dtkDistributedGpu::Cardinality dtkDistributedGpu::cardinality(void)
{
    return d->cardinality;
}

void dtkDistributedGpu::setCardinality(Cardinality cardinality)
{
    d->cardinality = cardinality;
}

QList<dtkDistributedCore *> dtkDistributedGpu::cores(void)
{
    return d->cores;
}

void dtkDistributedGpu::operator << (dtkDistributedCore *core)
{
    d->cores << core;
}
