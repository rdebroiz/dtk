/* dtkComposerScene.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:11:39
 * Version: $Id$
 * Last-Updated: Wed Feb  1 11:20:27 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 42
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERSCENE_H
#define DTKCOMPOSERSCENE_H

#include "dtkComposerExport.h"

#include <QtGui>

class dtkComposerMachine;
class dtkComposerFactory;
class dtkComposerSceneEdge;
class dtkComposerSceneNode;
class dtkComposerScenePort;
class dtkComposerScenePrivate;
class dtkComposerStack;

class DTKCOMPOSER_EXPORT dtkComposerScene : public QGraphicsScene
{
    Q_OBJECT

public:
             dtkComposerScene(QObject *parent = 0);
    virtual ~dtkComposerScene(void);

public:
    void setFactory(dtkComposerFactory *factory);
    void setMachine(dtkComposerMachine *machine);
    void setStack(dtkComposerStack *stack);

public:
    void    addNode(dtkComposerSceneNode *node);
    void removeNode(dtkComposerSceneNode *node);

    void    addEdge(dtkComposerSceneEdge *edge);
    void removeEdge(dtkComposerSceneEdge *edge);

    bool contains(dtkComposerSceneEdge *edge);
    bool contains(dtkComposerSceneNode *node);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

protected:
    dtkComposerScenePort *portAt(const QPointF& point) const;

private:
    dtkComposerScenePrivate *d;
};

#endif
