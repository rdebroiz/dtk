/* dtkComposerNodeString.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 27 15:12:01 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Oct 27 14:30:37 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 270
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringButton
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringButton : public QGraphicsItem
{
public:
     dtkComposerNodeStringButton(dtkComposerNodeString *parent);
    ~dtkComposerNodeStringButton(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeString *parent_node;
    QPainterPath path;
    QString text;
    bool expanded;
};

dtkComposerNodeStringButton::dtkComposerNodeStringButton(dtkComposerNodeString *parent) : QGraphicsItem(parent)
{
    int margin = 10;
    int length = 30;
    int height = 10;
    int radius =  5;
    int origin_x = -(length + margin) / 2;
    int origin_y = parent->boundingRect().height() / 2;

    QPainterPath b; b.addRoundedRect(origin_x,              origin_y, margin,          -height,     radius, radius);
    QPainterPath c; c.addRoundedRect(origin_x + margin,     origin_y, length - margin, -height,     radius, radius);
    QPainterPath d; d.addRoundedRect(origin_x + length,     origin_y, margin,          -height,     radius, radius);
    QPainterPath e; e.addRoundedRect(origin_x + margin / 2, origin_y, length,          -height / 2,      0,      0);

    path = c.united(e.subtracted(b.united(c.united(d))));

    parent_node = parent;
    
    text = "+";

    expanded = false;
}

dtkComposerNodeStringButton::~dtkComposerNodeStringButton(void)
{

}

QRectF dtkComposerNodeStringButton::boundingRect(void) const
{
    return path.boundingRect();
}

void dtkComposerNodeStringButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QLinearGradient gradient(option->rect.left(), option->rect.top(), option->rect.left(), option->rect.bottom());
    gradient.setColorAt(0.0, QColor("#bbbbbb"));
    gradient.setColorAt(0.3, QColor("#333333"));
    gradient.setColorAt(1.0, QColor("#222222"));

    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(gradient);
    painter->drawPath(path);
    
#if defined(Q_WS_MAC)
    QFont font("Lucida Grande", 8);
#else
    QFont font("Lucida Grande", 6);
#endif
    font.setBold(true);

    QFontMetrics metrics(font);
    
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, text);
}

void dtkComposerNodeStringButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if(!this->expanded) {
        parent_node->expand();
        text = "-";
    } else {
        parent_node->collapse();
        text = "+";
    }

    this->expanded = !this->expanded;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringEditor
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringEditor : public QGraphicsTextItem
{
public:
    dtkComposerNodeStringEditor(dtkComposerNodeString *parent);

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    dtkComposerNodeString *parent_node;
};

dtkComposerNodeStringEditor::dtkComposerNodeStringEditor(dtkComposerNodeString *parent) : QGraphicsTextItem(parent)
{
#if defined(Q_WS_MAC)
    QFont font("Lucida Grande", 10);
#else
    QFont font("Lucida Grande", 8);
#endif

    this->setDefaultTextColor(Qt::lightGray);
    this->setFont(font);
    this->setTextInteractionFlags(Qt::TextEditorInteraction);
    this->setFlag(QGraphicsItem::ItemStacksBehindParent, true);

    this->parent_node = parent;
}

void dtkComposerNodeStringEditor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath s_rect; s_rect.addRect(QRectF(option->rect.topLeft(), QSizeF(option->rect.width(), option->rect.height() / 2)));
    QPainterPath r_rect; r_rect.addRoundedRect(option->rect, 5, 5);
    QPainterPath path = s_rect.united(r_rect);

    painter->save();
    painter->setPen(Qt::darkGray);
    painter->setBrush(Qt::black);
    painter->drawPath(path);
    painter->restore();

    QStyleOptionGraphicsItem *o = const_cast<QStyleOptionGraphicsItem*>(option);
    o->state &= ~QStyle::State_Selected;
    o->state &= ~QStyle::State_HasFocus;

    QGraphicsTextItem::paint(painter, option, widget);
}

void dtkComposerNodeStringEditor::keyPressEvent(QKeyEvent *event)
{
    QGraphicsTextItem::keyPressEvent(event);

    this->parent_node->setValue(this->toPlainText());
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringPrivate
{
public:
    dtkComposerNodeProperty *property_input_value;
    dtkComposerNodeProperty *property_output_value;

public:
    dtkComposerNodeStringButton *button;
    dtkComposerNodeStringEditor *editor;

public:
    QPropertyAnimation *animation;

public:
    QString value;

    bool source_node;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeString
// /////////////////////////////////////////////////////////////////

dtkComposerNodeString::dtkComposerNodeString(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeStringPrivate)
{
    d->property_input_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    d->property_output_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, this);

    d->button = new dtkComposerNodeStringButton(this);
    d->button->setPos(0,0);
    
    d->value = QString();
    d->source_node = true;

    this->setTitle("String");
    this->setKind(dtkComposerNode::Atomic);
    this->setType("dtkComposerString");

    this->g->appendLeftProperty(d->property_input_value);
    this->g->appendRightProperty(d->property_output_value);

    // --
    
    d->editor = new dtkComposerNodeStringEditor(this);
    d->editor->setPos(-d->editor->boundingRect().width() / 2, 0);
    d->editor->setTextWidth(0.8 * this->boundingRect().width());
    d->editor->hide();

    // --

    d->animation = new QPropertyAnimation(d->editor, "pos");
    d->animation->setDuration(500);
    d->animation->setStartValue(QPointF(-d->editor->boundingRect().width()/2, 0));
    d->animation->setEndValue(QPointF(-d->editor->boundingRect().width()/2, 0.85 * d->editor->boundingRect().height()));
    d->animation->setEasingCurve(QEasingCurve::OutBounce);
}

dtkComposerNodeString::~dtkComposerNodeString(void)
{
    delete d;

    d = NULL;
}

QVariant dtkComposerNodeString::value(dtkComposerNodeProperty *property)
{
    if(property == d->property_output_value)
        return QVariant(d->value);

	return QVariant();
}

QString dtkComposerNodeString::value(void)
{
    return d->value;
}

void dtkComposerNodeString::setValue(QString value)
{
    d->value = value;
}

void dtkComposerNodeString::expand(void)
{
    d->editor->show();
    d->animation->setDirection(QAbstractAnimation::Forward);
    d->animation->start();
}

void dtkComposerNodeString::collapse(void)
{
    d->animation->setDirection(QAbstractAnimation::Backward);
    d->animation->start();

    connect(d->animation, SIGNAL(finished()), this, SLOT(onCollapseFinised()));
}

void dtkComposerNodeString::touch(void)
{
    d->editor->setPlainText(d->value); 
    d->editor->update();

    dtkComposerNode::touch();
}

void dtkComposerNodeString::onCollapseFinised(void)
{
    d->editor->hide();

    disconnect(d->animation, SIGNAL(finished()), this, SLOT(onCollapseFinised()));    
}

void dtkComposerNodeString::pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if (property == d->property_input_value) {

        QVariant value = edge->source()->node()->value(edge->source());
        
        if(value.canConvert(QVariant::String)) {
            this->setValue(value.toString());
        } else {
            qDebug() << DTK_PRETTY_FUNCTION << "Input value expected to be a string. Assuming empty string.";
            this->setValue(QString());
        }

        d->source_node = false;

        // d->editor->setPlainText(d->value); 
        // d->editor->update();
    }
}

void dtkComposerNodeString::run(void)
{
    if (d->source_node)
        this->setValue(d->editor->toPlainText());    
        
    d->source_node = true;
}

void dtkComposerNodeString::push(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);
}
