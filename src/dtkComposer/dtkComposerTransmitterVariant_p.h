/* dtkComposerTransmitterVariant_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Aug  3 14:36:46 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep 27 15:00:39 2012 (+0200)
 *           By: tkloczko
 *     Update #: 54
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERVARIANT_P_H
#define DTKCOMPOSERTRANSMITTERVARIANT_P_H

#include <QtCore>

class dtkComposerTransmitter;
class dtkComposerTransmitterVariant;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariantPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterVariantPrivate
{
public:
    enum Type {
        RealStar = 0,
        LongLongStar = 1,
        StringStar = 2,
        BoolStar = 3
    };

public:
    dtkComposerTransmitterVariantPrivate(void) {        
        metatypes[0] = qMetaTypeId<qreal*>(0);
        metatypes[1] = qMetaTypeId<qlonglong*>(0);
        metatypes[2] = qMetaTypeId<QString*>(0);
        metatypes[3] = qMetaTypeId<bool*>(0);
    }

public:
    QList<dtkComposerTransmitter *> emitters;
    QList<dtkComposerTransmitterVariant *> variants;

public:
    dtkComposerTransmitter        *active_emitter;
    dtkComposerTransmitterVariant *active_variant;

public:
    QList<int> data_types;

public:
    dtkComposerTransmitterVariant *twin;

    bool twinned;

    bool already_ask;
    
public:
    bool      value_b;
    qlonglong value_i;
    qreal     value_r;
    QString   value_s;

public:
    int metatypes[4];
    
public:
    QVariant m_variant;
};

#endif
