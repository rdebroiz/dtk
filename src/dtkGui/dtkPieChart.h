/* dtkPieChart.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: mar. avril 24 15:40:38 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. avril 24 16:51:50 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 43
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKPIECHART_H
#define DTKPIECHART_H

#include <QtGui/QWidget>

#include "dtkGuiExport.h"


class dtkPieChartPrivate;

class DTKGUI_EXPORT dtkPieChart : public QWidget
{
    Q_OBJECT

public:
    dtkPieChart(QWidget *parent = 0, int width = 0, int height = 0);
   ~dtkPieChart(void);

public:
   QSize sizeHint(void) const;

public:
   void addPiece(const QString& key, int val, QColor color);

public:
   void paintEvent(QPaintEvent *ev);

public:
   void clear(void);

private:
    dtkPieChartPrivate *d;
};

#endif
