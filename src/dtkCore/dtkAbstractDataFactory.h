/* dtkAbstractDataFactory.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:48:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Oct 31 19:47:10 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 81
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABSTRACTDATAFACTORY_H
#define DTKABSTRACTDATAFACTORY_H

#include <dtkCore/dtkAbstractFactory.h>

class dtkAbstractData;
class dtkAbstractDataReader;
class dtkAbstractDataWriter;
class dtkAbstractDataConverter;
class dtkAbstractDataFactoryPrivate;

class DTKCORE_EXPORT dtkAbstractDataFactory : public dtkAbstractFactory
{
    Q_OBJECT

public:
    typedef dtkAbstractData          *(*dtkAbstractDataCreator)         (void);
    typedef dtkAbstractDataReader    *(*dtkAbstractDataReaderCreator)   (void);
    typedef dtkAbstractDataWriter    *(*dtkAbstractDataWriterCreator)   (void);
    typedef dtkAbstractDataConverter *(*dtkAbstractDataConverterCreator)(void);

    typedef QHash<               QString,      dtkAbstractDataCreator>          dtkAbstractDataCreatorHash;
    typedef QHash<QPair<QString, QStringList>, dtkAbstractDataReaderCreator>    dtkAbstractDataReaderCreatorHash;
    typedef QHash<QPair<QString, QStringList>, dtkAbstractDataWriterCreator>    dtkAbstractDataWriterCreatorHash;
    typedef QHash<QPair<QString, QPair<QStringList, QString> >, dtkAbstractDataConverterCreator> dtkAbstractDataConverterCreatorHash;
    typedef       QPair<QString, QStringList>  dtkAbstractDataTypeHandler;
    typedef       QPair<QString, QPair<QStringList, QString> >  dtkAbstractDataConverterTypeHandler;

public:
    static dtkAbstractDataFactory *instance(void);

    bool registerDataType         (const QString & type,                      dtkAbstractDataCreator          func);
    bool registerDataReaderType   (const QString & type, const QStringList & handled, dtkAbstractDataReaderCreator    func);
    bool registerDataWriterType   (const QString & type, const QStringList & handled, dtkAbstractDataWriterCreator    func);
    bool registerDataConverterType(const QString & type, const QStringList & fromTypes, const QString & toType,  dtkAbstractDataConverterCreator func);

    unsigned int size(const QString & type) const;

    unsigned int count(const QString & type) const;
    unsigned int countReaders   (const QString & type) const;
    unsigned int countWriters   (const QString & type) const;
    unsigned int countConverters(const QString & type) const;

    dtkAbstractData *get(const QString & type, int index = 0);
    dtkAbstractData *get(const QString & type, const QString & name);

    QList<dtkAbstractDataTypeHandler>          readers(void) const;
    QList<dtkAbstractDataTypeHandler>          writers(void) const;
    QList<dtkAbstractDataConverterTypeHandler> converters(void) const;

signals:
    void created(dtkAbstractData *data, const QString & type);

public slots:
    dtkAbstractData          *create   (const QString & type);
    dtkAbstractDataReader    *reader   (const QString & type, const QStringList & handled);
    dtkAbstractDataWriter    *writer   (const QString & type, const QStringList & handled);
    dtkAbstractDataConverter *converter(const QString & type, const QStringList & fromType, const QString & toType);

protected:
     dtkAbstractDataFactory(void);
    ~dtkAbstractDataFactory(void);

private:
    static dtkAbstractDataFactory *s_instance;

private:
    dtkAbstractDataFactoryPrivate *d;
};

#endif
