/* dtkComposerSceneNodeEditor_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 10:28:04 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 13:37:48 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 57
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENENODEEDITOR_P_H
#define DTKCOMPOSERSCENENODEEDITOR_P_H

#include <QtGui>

class dtkComposerScene;
class dtkComposerSceneNode;
class dtkComposerScenePort;
class dtkComposerStack;
class dtkComposerGraph;

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeEditorList
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodeEditorList : public QListWidget
{
    Q_OBJECT

public:
     dtkComposerSceneNodeEditorList(QWidget *parent = 0);
    ~dtkComposerSceneNodeEditorList(void);

public:
    QSize sizeHint(void) const;

public:
    void  addInputPort(dtkComposerScenePort *port);
    void addOutputPort(dtkComposerScenePort *port);

protected slots:
    void onItemChanged(QListWidgetItem *item);
    void onItemClicked(QListWidgetItem *item);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeEditorListItem
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodeEditorListItem : public QListWidgetItem
{
public:
     dtkComposerSceneNodeEditorListItem(dtkComposerScenePort *port, dtkComposerSceneNodeEditorList *parent);
    ~dtkComposerSceneNodeEditorListItem(void);

    int type(void) const;

    dtkComposerScenePort *port(void);

private:
    dtkComposerScenePort *m_port;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeEditor
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodeEditorPrivate
{
public:
    dtkComposerSceneNodeEditorList *loop_ports;
    dtkComposerSceneNodeEditorList *input_ports;
    dtkComposerSceneNodeEditorList *output_ports;

public:
    dtkComposerScene *scene;
    dtkComposerSceneNode *node;
    dtkComposerStack *stack;
    dtkComposerGraph *graph;

public:
    QPushButton *add_loop_port;
    QPushButton *rem_loop_port;

    QPushButton *add_input_port;
    QPushButton *rem_input_port;
    QPushButton *add_output_port;
    QPushButton *rem_output_port;

public:
    QLineEdit *edit;

public:
    QSpinBox *spin_d;

public:
    QDoubleSpinBox *spin_f;

public:
    QLineEdit *edit_s;

public:
    QComboBox *combo_b;

public:
    QComboBox *selector;
};

#endif
