/* dtkComposerNode.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:48:02 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Feb 25 10:07:09 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 227
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODE_H
#define DTKCOMPOSERNODE_H

#include "dtkComposerExport.h"

#include <QtCore>
#include <QtDebug>
#include <QtGui>

class dtkAbstractObject;
class dtkComposerEdge;
class dtkComposerNodePrivate;
class dtkComposerNodeProperty;
class stkComspoerScene;

class DTKCOMPOSER_EXPORT dtkComposerNode : public QObject, public QGraphicsItem
{
    Q_OBJECT

#if QT_VERSION >= 0x040600
    Q_INTERFACES(QGraphicsItem)
#endif

public:
    enum Kind {
        Unknown,
        Atomic,
        Composite,
        Data,
        Process,
        View
    };

             dtkComposerNode(dtkComposerNode *parent = 0);
    virtual ~dtkComposerNode(void);

    virtual QString description(void); 

    void setTitle(const QString& title);
    void setKind(Kind kind);
    void setType(QString type);
    void setObject(dtkAbstractObject *object);

    void addInputProperty(dtkComposerNodeProperty *property);
    void addOutputProperty(dtkComposerNodeProperty *property);

    void removeInputProperty(dtkComposerNodeProperty *property);
    void removeOutputProperty(dtkComposerNodeProperty *property);

    void addInputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void addOutputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

    void addGhostInputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void addGhostOutputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

    void removeInputEdge(dtkComposerEdge *edge);
    void removeOutputEdge(dtkComposerEdge *edge);
    void removeAllEdges(void);

    void removeGhostInputEdge(dtkComposerEdge *edge);
    void removeGhostOutputEdge(dtkComposerEdge *edge);
    void removeAllGhostEdges(void);

    void addAction(const QString& text, const QObject *receiver, const char *slot);

    int  count(dtkComposerNodeProperty *property);
    int number(dtkComposerNodeProperty *property);

    Kind kind(void);
    QString type(void);

    dtkAbstractObject *object(void);

    QList<dtkComposerNodeProperty *> inputProperties(void);
    QList<dtkComposerNodeProperty *> outputProperties(void);

    QList<dtkComposerEdge *> inputEdges(void);
    QList<dtkComposerEdge *> outputEdges(void);

    QList<dtkComposerEdge *> inputGhostEdges(void);
    QList<dtkComposerEdge *> outputGhostEdges(void);

    QList<dtkComposerNode *> inputNodes(void);
    QList<dtkComposerNode *> outputNodes(void);

    dtkComposerEdge *edge(dtkComposerNodeProperty *property);

    dtkComposerNodeProperty *propertyAt(const QPointF& point) const;

    dtkComposerNodeProperty  *inputProperty(const QString& name) const;
    dtkComposerNodeProperty  *inputProperty(const QString& name, dtkComposerNode *from) const;
    dtkComposerNodeProperty *outputProperty(const QString& name) const;
    dtkComposerNodeProperty *outputProperty(const QString& name, dtkComposerNode *from) const;

    QString title(void);

    bool dirty(void);
    void setDirty(bool dirty);

    void layout(void);

    // -- Composite operations

    void    addChildNode(dtkComposerNode *node);
    void removeChildNode(dtkComposerNode *node);

    void setParentNode(dtkComposerNode *node);

    QList<dtkComposerNode *> childNodes(void);

    dtkComposerNode *parentNode(void);

    // --

    void setGhost(bool ghost);
    bool  isGhost(void);

    friend QDebug operator<<(QDebug dbg, dtkComposerNode& node);
    friend QDebug operator<<(QDebug dbg, dtkComposerNode *node);

signals:
    void elapsed(QString duration);
    void evaluated(dtkComposerNode *node);
    void progressed(QString message);
    void progressed(int progress);

public slots:
    void alter(void);
    void touch(void);
    void update(void);

public:
    QRectF boundingRect(void) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public:
    virtual QVariant value(dtkComposerNodeProperty *property) { return QVariant(); }

    virtual void chooseImplementation(void);
    virtual void  setupImplementation(QString implementation = QString());

protected:
    virtual void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    virtual void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    virtual void run(void);

private:
    friend class dtkComposerNodePrivate; dtkComposerNodePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

QDebug operator<<(QDebug dbg, dtkComposerNode  node);
QDebug operator<<(QDebug dbg, dtkComposerNode& node);
QDebug operator<<(QDebug dbg, dtkComposerNode *node);

#endif
