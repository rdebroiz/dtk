/* dtkComposerStackCommand.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 18:15:13 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include <QtCore>
#include <QtWidgets>

class dtkComposerNodeFactory;
class dtkComposerGraph;
class dtkComposerScene;
class dtkComposerSceneEdge;
class dtkComposerSceneEdgeList;
class dtkComposerSceneNode;
class dtkComposerSceneNodeComposite;
class dtkComposerSceneNodeControl;
class dtkComposerSceneNodeList;
class dtkComposerSceneNote;
class dtkComposerSceneNoteList;
class dtkComposerScenePort;
class dtkComposerStackCommandPrivate;

// /////////////////////////////////////////////////////////////////
// Command Interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerStackCommand : public QUndoCommand
{
public:
             dtkComposerStackCommand(dtkComposerStackCommand *parent = 0);
    virtual ~dtkComposerStackCommand(void);

public:
    void setFactory(dtkComposerNodeFactory *factory);
    void setScene(dtkComposerScene *scene);
    void setGraph(dtkComposerGraph *graph);

protected:
    dtkComposerStackCommandPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Create Node Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateNodePrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandCreateNode : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandCreateNode(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandCreateNode(void);

public:
    dtkComposerSceneNode *node(void);

public:
    void setParent(dtkComposerSceneNodeComposite *parent);
    void setPosition(const QPointF& position);
    void setName(const QString& name);
    void setType(const QString& type);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandCreateNodePrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Destroy Node Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyNodePrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandDestroyNode : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandDestroyNode(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandDestroyNode(void);

public:
    void setNode(dtkComposerSceneNode *node);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandDestroyNodePrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Create Edge Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateEdgePrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandCreateEdge : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandCreateEdge(void);
    ~dtkComposerStackCommandCreateEdge(void);

public:
    void setSource(dtkComposerScenePort *source);
    void setDestination(dtkComposerScenePort *destination);

public:
    void redo(void);
    void undo(void);

public:
    void setParent(void);
    void setParent(dtkComposerSceneNodeComposite *parent);

private:
    dtkComposerStackCommandCreateEdgePrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Destroy Edge Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyEdgePrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandDestroyEdge : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandDestroyEdge(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandDestroyEdge(void);

public:
    void setEdge(dtkComposerSceneEdge *edge);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandDestroyEdgePrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Create Note Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateNotePrivate;

class dtkComposerStackCommandCreateNote : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandCreateNote(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandCreateNote(void);

public:
    void setParent(dtkComposerSceneNodeComposite *parent);
    void setPosition(const QPointF& position);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandCreateNotePrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Destroy Note Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyNotePrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandDestroyNote : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandDestroyNote(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandDestroyNote(void);

public:
    void setNote(dtkComposerSceneNote *note);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandDestroyNotePrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Create Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateGroupPrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandCreateGroup : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandCreateGroup(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandCreateGroup(void);

public:
    void setNodes(dtkComposerSceneNodeList nodes);
    void setNotes(dtkComposerSceneNoteList notes);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandCreateGroupPrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Destroy Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyGroupPrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandDestroyGroup : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandDestroyGroup(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandDestroyGroup(void);

public:
    void setNode(dtkComposerSceneNodeComposite *node);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandDestroyGroupPrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Enter Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandEnterGroupPrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandEnterGroup : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandEnterGroup(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandEnterGroup(void);

public:
    void setNode(dtkComposerSceneNodeComposite *node);
    void setFormer(dtkComposerSceneNodeComposite *former);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandEnterGroupPrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Leave Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandLeaveGroupPrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandLeaveGroup : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandLeaveGroup(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandLeaveGroup(void);

public:
    void setNode(dtkComposerSceneNodeComposite *node);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandLeaveGroupPrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Flatten Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandFlattenGroupPrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandFlattenGroup : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandFlattenGroup(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandFlattenGroup(void);

public:
    void setNode(dtkComposerSceneNodeComposite *node);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandFlattenGroupPrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Unflatten Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandUnflattenGroupPrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandUnflattenGroup : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandUnflattenGroup(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandUnflattenGroup(void);

public:
    void setNode(dtkComposerSceneNodeComposite *node);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandUnflattenGroupPrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Create Port Command
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitter.h"

class dtkComposerStackCommandCreatePortPrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandCreatePort : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandCreatePort(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandCreatePort(void);

public:
    dtkComposerScenePort *port(void);

public:
    void setKind(dtkComposerTransmitter::Kind kind);
    void setNode(dtkComposerSceneNodeComposite *node);
    void setType(int type);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandCreatePortPrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Destroy Port Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyPortPrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandDestroyPort : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandDestroyPort(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandDestroyPort(void);

public:
    void setNode(dtkComposerSceneNodeComposite *node);
    void setPort(dtkComposerScenePort *port);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandDestroyPortPrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Reparent Node Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandReparentNodePrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandReparentNode : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandReparentNode(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandReparentNode(void);

public:
    void setOriginNode(dtkComposerSceneNode *node);
    void setTargetNode(dtkComposerSceneNode *node);

    void setOriginPosition(QPointF position);
    void setTargetPosition(QPointF position);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandReparentNodePrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Create Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateBlockPrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandCreateBlock: public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandCreateBlock(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandCreateBlock(void);

public:
    void setNode(dtkComposerSceneNodeControl *node);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandCreateBlockPrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Delete Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyBlockPrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandDestroyBlock: public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandDestroyBlock(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandDestroyBlock(void);

public:
    void setNode(dtkComposerSceneNodeComposite *node);
    void setId(int i);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandDestroyBlockPrivate *e;
};



// /////////////////////////////////////////////////////////////////
// Copy Nodes Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCopyNodesPrivate;

class DTKCOMPOSER_EXPORT dtkComposerStackCommandCopyNodes: public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandCopyNodes(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandCopyNodes(void);

public:
    void setNodes(dtkComposerSceneNodeList nodes);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandCopyNodesPrivate *e;
};
