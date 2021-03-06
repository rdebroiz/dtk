/* dtkPlotViewZoomer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:52:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mer. avril  9 13:22:49 2014 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 57
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTVIEWZOOMER_H
#define DTKPLOTVIEWZOOMER_H

#include "dtkPlotSupportExport.h"

#include <QObject>
#include <QRectF>
#include <QColor>

class dtkPlotView;
class dtkPlotViewZoomerPrivate;

class DTKPLOTSUPPORT_EXPORT dtkPlotViewZoomer : public QObject
{
    Q_OBJECT

public:
     dtkPlotViewZoomer(dtkPlotView *parent);
    ~dtkPlotViewZoomer(void);

public:
    void   activate(void);
    void deactivate(void);

    bool isActivated(void) const;

public:
    QColor color(void) const;

    void setColor(const QColor& color);

public:
    void updateBase(const QRectF& rectf);

private:
    dtkPlotViewZoomerPrivate *d;
};

#endif
