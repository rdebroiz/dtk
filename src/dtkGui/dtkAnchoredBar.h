/* dtkAnchoredBar.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar 16 08:43:54 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr 30 18:32:56 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKANCHOREDBAR_H
#define DTKANCHOREDBAR_H

#include <QtGui>

#include "dtkGuiExport.h"

class dtkAnchoredBarPrivate;

class DTKGUI_EXPORT dtkAnchoredBar : public QToolBar
{
    Q_OBJECT

public:
    dtkAnchoredBar(QWidget *parent = 0);

    QSize sizeHint(void) const;

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    dtkAnchoredBarPrivate *d;
};

#endif
