/* dtkHelpController.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 16:02:30 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Feb  6 13:35:30 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 32
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkHelpController.h"

class dtkHelpControllerPrivate
{
public:
    QHelpEngine *engine;
    
    QString path;
};

dtkHelpController *dtkHelpController::instance(void)
{
    if(!s_instance)
        s_instance = new dtkHelpController;

    return s_instance;
}

void dtkHelpController::initialize(void)
{
    this->readSettings();
}

void dtkHelpController::uninitialize(void)
{
    this->writeSettings();
}

void dtkHelpController::readSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("help");
    d->path = settings.value("path").toString();
    settings.endGroup();
}

void dtkHelpController::writeSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("help");
    settings.setValue("path", d->path);
    settings.endGroup();
}

QHelpEngine *dtkHelpController::engine(void)
{
    return d->engine;
}

QString dtkHelpController::path(void) const
{
    return d->path;
}

dtkHelpController::dtkHelpController(void) : QObject(), d(new dtkHelpControllerPrivate)
{
#ifdef Q_WS_MAC
    d->engine = new QHelpEngine(qApp->applicationDirPath() + "/../../../../doc/dtk.qhc", this);
#else
    d->engine = new QHelpEngine(qApp->applicationDirPath() + "/../doc/dtk.qhc", this);
#endif
    d->engine->setupData();
}

dtkHelpController::~dtkHelpController(void)
{
    delete d->engine;
    delete d;

    d = NULL;
}

dtkHelpController *dtkHelpController::s_instance = NULL;
