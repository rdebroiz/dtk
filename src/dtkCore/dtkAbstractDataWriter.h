/* dtkAbstractDataWriter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 24 21:58:48 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Oct  3 18:17:53 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 28
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATAWRITER_H
#define DTKABSTRACTDATAWRITER_H

#include <dtkCore/dtkAbstractObject.h>

class dtkAbstractData;
class dtkAbstractDataWriterPrivate;

class DTKCORE_EXPORT dtkAbstractDataWriter : public dtkAbstractObject
{
    Q_OBJECT

public:
    dtkAbstractDataWriter(void);
   ~dtkAbstractDataWriter(void);

   virtual QString description(void) const = 0;
   virtual QStringList handled(void) const = 0;

   bool enabled(void);
   void  enable(void);
   void disable(void);

   dtkAbstractData *data(void);

   virtual void setData(dtkAbstractData *data);

public slots:
   virtual bool canWrite(QString file);
   virtual bool canWrite(QStringList files);

   virtual bool write(QString file);
   virtual bool write(QStringList files);

private:
   dtkAbstractDataWriterPrivate *d;
};

#endif
