/* dtkAbstractDataReader_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Apr 24 10:34:11 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 11:37:40 2012 (+0200)
 *           By: tkloczko
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATAREADER_P_H
#define DTKABSTRACTDATAREADER_P_H

#include "dtkCoreExport.h"
#include "dtkAbstractObject_p.h"
#include "dtkSmartPointer.h"

class dtkAbstractDataReader;
class dtkAbstractData;

////////////////////////////////////////////////////
// dtkAbstractDataReaderPrivate interface
////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkAbstractDataReaderPrivate : public dtkAbstractObjectPrivate
{
public:
    dtkAbstractDataReaderPrivate(dtkAbstractDataReader *q = 0) : dtkAbstractObjectPrivate(q) {}
    dtkAbstractDataReaderPrivate(const dtkAbstractDataReaderPrivate& other) : dtkAbstractObjectPrivate(other),
                                                                              enabled(false),
                                                                              data(other.data),
                                                                              file(other.file),
                                                                              files(other.files) {}

public:
    virtual ~dtkAbstractDataReaderPrivate(void) {}

public:
    bool enabled;

public:
    dtkSmartPointer<dtkAbstractData> data;

public:
    QString file;
    QStringList files;
};

////////////////////////////////////////////////////
// dtkAbstractDataReader protected constructors
////////////////////////////////////////////////////

DTK_IMPLEMENT_PRIVATE(dtkAbstractDataReader, dtkAbstractObject);

#endif