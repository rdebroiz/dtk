/* dtkLogEngine.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 16:18:42 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar  1 21:55:25 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 52
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkLog.h"
#include "dtkLogger.h"
#include "dtkLogger_p.h"
#include "dtkLogEngine.h"

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

QString dtkLogLevel2String(dtkLog::Level level)
{
    switch(level) {
    case dtkLog::Trace: return "TRACE"; break;
    case dtkLog::Debug: return "DEBUG"; break;
    case dtkLog::Info:  return "INFO "; break;
    case dtkLog::Warn:  return "WARN "; break;
    case dtkLog::Error: return "ERROR"; break;
    case dtkLog::Fatal: return "FATAL"; break;
    default:
        return "UNKNOWN";
        break;
    };
}

// /////////////////////////////////////////////////////////////////
// dtkLogEnginePrivate
// /////////////////////////////////////////////////////////////////

class dtkLogEnginePrivate
{
public:
    dtkLogEnginePrivate(void) : stream(&buffer) {}

public:
    void write(void);

public:
    dtkLog::Level level;

public:
    QDebug stream;

public:
    QString buffer;
};

void dtkLogEnginePrivate::write(void)
{
    const QString message = QString("%1 - %2 - %3")
        .arg(qPrintable(dtkLogLevel2String(this->level)))
        .arg(QDateTime::currentDateTime().toString())
        .arg(this->buffer);

    QMutexLocker lock(&(dtkLogger::instance().d->mutex));

    dtkLogger::instance().write(message);
}

// /////////////////////////////////////////////////////////////////
// dtkLogEngine
// /////////////////////////////////////////////////////////////////

dtkLogEngine::dtkLogEngine(dtkLog::Level level) : d(new dtkLogEnginePrivate)
{
    d->level = level;
}

dtkLogEngine::~dtkLogEngine(void)
{
    d->write();

    delete d;

    d = NULL;
}

QDebug dtkLogEngine::stream(void)
{
    return d->stream;
}
