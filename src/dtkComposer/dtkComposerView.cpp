/* dtkComposerView.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:02:53
 * Version: $Id$
 * Last-Updated: ven. sept. 14 14:35:32 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 115
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerView.h"

class dtkComposerViewPrivate
{
public:

};

dtkComposerView::dtkComposerView(QWidget *parent) : QGraphicsView(parent), d(new dtkComposerViewPrivate)
{
    this->setAcceptDrops(true);
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setBackgroundBrush(QColor(0x55, 0x55, 0x55));
    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setFrameStyle(QFrame::NoFrame);
    this->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    this->setRubberBandSelectionMode(Qt::IntersectsItemShape);
}

dtkComposerView::~dtkComposerView(void)
{

}

void dtkComposerView::wheelEvent( QWheelEvent * event )
{
    if (event->modifiers().testFlag(Qt::ControlModifier)){ //zoom only when CTRL key pressed
        qreal scaleFactor = pow((double)2, event->delta() / 500.0);

        qreal factor = this->matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

        if (factor < 0.1 || factor > 1.0)
            return;

        this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        this->scale(scaleFactor, scaleFactor);
    } else {
        QGraphicsView::wheelEvent(event);
    }
}

void dtkComposerView::scroll(int dx, int dy)
{
    this->centerOn(this->mapToScene(this->viewport()->rect().center()) + QPointF(dx, dy));
}

void dtkComposerView::scrollContentsBy(int dx, int dy)
{
    QGraphicsView::scrollContentsBy(dx, dy);

    emit scrolled();
}
