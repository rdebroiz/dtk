/* dtkLogDestination.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 15:10:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr  4 10:00:13 2012 (+0200)
 *           By: tkloczko
 *     Update #: 49
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKLOGDESTINATION_H
#define DTKLOGDESTINATION_H

#include "dtkLogExport.h"

#include <QtCore>
#include <QtGui>

class dtkLogModel;

// /////////////////////////////////////////////////////////////////
// dtkLogDestination
// /////////////////////////////////////////////////////////////////

class DTKLOG_EXPORT dtkLogDestination
{
public:
    virtual ~dtkLogDestination(void);

public:
    virtual void write(const QString& message) = 0;
};

// /////////////////////////////////////////////////////////////////
// dtkLogDestinationConsole
// /////////////////////////////////////////////////////////////////

class DTKLOG_EXPORT dtkLogDestinationConsole : public dtkLogDestination
{
public:
    void write(const QString& message);
};

// /////////////////////////////////////////////////////////////////
// dtkLogDestinationFile
// /////////////////////////////////////////////////////////////////

class dtkLogDestinationFilePrivate;

class DTKLOG_EXPORT dtkLogDestinationFile : public dtkLogDestination
{
public:
     dtkLogDestinationFile(const QString& path);
    ~dtkLogDestinationFile(void);

public:
    void write(const QString& message);

private:
    dtkLogDestinationFilePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkLogDestinationText
// /////////////////////////////////////////////////////////////////

class dtkLogDestinationTextPrivate;

class DTKLOG_EXPORT dtkLogDestinationText : public dtkLogDestination
{
public:
     dtkLogDestinationText(QPlainTextEdit *editor);
    ~dtkLogDestinationText(void);

public:
    void write(const QString& message);

private:
    dtkLogDestinationTextPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkLogDestinationList
// /////////////////////////////////////////////////////////////////

class dtkLogDestinationModelPrivate;

class DTKLOG_EXPORT dtkLogDestinationModel : public dtkLogDestination
{
public:
     dtkLogDestinationModel(dtkLogModel *model);
    ~dtkLogDestinationModel(void);

public:
    void write(const QString& message);

private:
    dtkLogDestinationModelPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkLogDestinationPointer
// /////////////////////////////////////////////////////////////////

typedef QSharedPointer<dtkLogDestination> dtkLogDestinationPointer;

#endif