/* dtkComposerWriter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:02:49 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Mar 22 17:11:19 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 396
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeBooleanOperator.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeNumber.h"
#include "dtkComposerNodeNumberComparator.h"
#include "dtkComposerNodeNumberOperator.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeProcess.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerNodeStringComparator.h"
#include "dtkComposerNodeStringOperator.h"
#include "dtkComposerNote.h"
#include "dtkComposerScene.h"
#include "dtkComposerWriter.h"

#include <QtXml>

// /////////////////////////////////////////////////////////////////
// dtkComposerWriterPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerWriterPrivate
{
public:
    dtkComposerScene *scene;

    QHash<int, dtkComposerNode *> node_ids;

    int id;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerWriter
// /////////////////////////////////////////////////////////////////

dtkComposerWriter::dtkComposerWriter(dtkComposerScene *scene) : QObject(), d(new dtkComposerWriterPrivate)
{
    d->scene = scene;
}

dtkComposerWriter::~dtkComposerWriter(void)
{
    delete d;

    d = NULL;
}

void dtkComposerWriter::write(const QString& fileName)
{
    d->node_ids.clear();
    d->id = 0;

    // Building dom document

    QDomDocument document("dtk");

    QDomElement root = document.createElement("dtk");
    document.appendChild(root);

    // -- Writing nodes

    foreach(dtkComposerNode *node, d->scene->nodes())
        if(!node->parentNode() && !node->parentItem())
            this->writeNode(node, root, document);

    // -- Writing edges

    foreach(dtkComposerEdge *edge, d->scene->edges()) {

        QDomElement source = document.createElement("source");
        source.setAttribute("node", d->node_ids.key(edge->source()->node()));
        source.setAttribute("property", edge->source()->name());
        if(edge->source()->clonedFrom())
            source.setAttribute("id", d->node_ids.key(edge->source()->clonedFrom()));
        if(!edge->source()->blockedFrom().isEmpty())
            source.setAttribute("block", edge->source()->blockedFrom());

        QDomElement destin = document.createElement("destination");
        destin.setAttribute("node", d->node_ids.key(edge->destination()->node()));
        destin.setAttribute("property", edge->destination()->name());
        if(edge->destination()->clonedFrom())
            destin.setAttribute("id", d->node_ids.key(edge->destination()->clonedFrom()));
        if(!edge->destination()->blockedFrom().isEmpty())
            destin.setAttribute("block", edge->destination()->blockedFrom());

        QDomElement tag = document.createElement("edge");
        tag.appendChild(source);
        tag.appendChild(destin);

        root.appendChild(tag);
    }

    // Writing notes

    foreach(dtkComposerNote *note, d->scene->notes()) {

        QDomText text = document.createTextNode(note->text());

        QDomElement tag = document.createElement("note");
        tag.setAttribute("x", QString::number(note->pos().x()));
        tag.setAttribute("y", QString::number(note->pos().y()));
        tag.setAttribute("w", QString::number(note->boundingRect().width()));
        tag.setAttribute("h", QString::number(note->boundingRect().height()));
        tag.appendChild(text);

        root.appendChild(tag);
    }

    // Writing file

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
        return;

    QTextStream out(&file); out << document.toString();

    file.close();
}

QDomElement dtkComposerWriter::writeNode(dtkComposerNode *node, QDomElement& element, QDomDocument& document)
{
    int current_id = d->id++;

    QDomElement tag = document.createElement("node");
    tag.setAttribute("type", node->type());
    tag.setAttribute("x", QString::number(node->pos().x()));
    tag.setAttribute("y", QString::number(node->pos().y()));
    tag.setAttribute("id", QString::number(current_id));
     
    // -- Boolean node
    
    if(dtkComposerNodeBoolean *boolean_node = dynamic_cast<dtkComposerNodeBoolean *>(node)) {
        
        bool value = boolean_node->value(boolean_node->outputProperty("value")).toBool();
        
        QDomText text = document.createTextNode(value ? "true" : "false");
        
        QDomElement e_value = document.createElement("value");
        e_value.appendChild(text);
        
        tag.appendChild(e_value);
    }

    // -- Boolean operator node
    
    if(dtkComposerNodeBooleanOperator *boolean_operator_node = dynamic_cast<dtkComposerNodeBooleanOperator *>(node)) {
        
        dtkComposerNodeBooleanOperator::Operation operation = boolean_operator_node->operation();
        
        QDomText text;

        switch(operation) {
        case dtkComposerNodeBooleanOperator::And:
            text = document.createTextNode("and");
            break;
        case dtkComposerNodeBooleanOperator::Or:
            text = document.createTextNode("or");
            break;
        case dtkComposerNodeBooleanOperator::Xor:
            text = document.createTextNode("xor");
            break;
        case dtkComposerNodeBooleanOperator::Nand:
            text = document.createTextNode("nand");
            break;
        case dtkComposerNodeBooleanOperator::Nor:
            text = document.createTextNode("nor");
            break;
        case dtkComposerNodeBooleanOperator::Xnor:
            text = document.createTextNode("xnor");
            break;
        case dtkComposerNodeBooleanOperator::Imp:
            text = document.createTextNode("imp");
            break;
        case dtkComposerNodeBooleanOperator::Nimp:
            text = document.createTextNode("nimp");
            break;
        default:
            break;
        }
        
        QDomElement e_operation = document.createElement("operation");
        e_operation.appendChild(text);
        
        tag.appendChild(e_operation);
    }
     
    // -- Number node
    
    if(dtkComposerNodeNumber *number_node = dynamic_cast<dtkComposerNodeNumber *>(node)) {
                
        QDomText text;
        QString value;

        dtkComposerNodeNumber::Genre genre =  number_node->genre();

        switch (genre) {
        case (dtkComposerNodeNumber::Int):
            text = document.createTextNode("int");
            value = QString::number(number_node->number().toInt());
            break;        
        case (dtkComposerNodeNumber::UInt):
            text = document.createTextNode("uint");
            value = QString::number(number_node->number().toUInt());
            break;
        case (dtkComposerNodeNumber::Long):
            text = document.createTextNode("long");
            value = QString::number((long)number_node->number().toLongLong());
            break;
        case (dtkComposerNodeNumber::ULong):
            text = document.createTextNode("ulong");
            value = QString::number((ulong)number_node->number().toULongLong());
            break;
        case (dtkComposerNodeNumber::LongLong):
            text = document.createTextNode("longlong");
            value = QString::number(number_node->number().toLongLong());
            break;
        case (dtkComposerNodeNumber::ULongLong):
            text = document.createTextNode("ulonglong");
            value = QString::number(number_node->number().toULongLong());
            break;
        case (dtkComposerNodeNumber::Float):
            text = document.createTextNode("float");
            value = QString::number((float)number_node->number().toDouble());
            break;
        case (dtkComposerNodeNumber::Double):
            text = document.createTextNode("double");
            value = QString::number(number_node->number().toDouble());
            break;
        } 
       
        QDomElement e_genre = document.createElement("genre");
        e_genre.appendChild(text);        
        tag.appendChild(e_genre);

        text = document.createTextNode(value);        
        QDomElement e_value = document.createElement("value");
        e_value.appendChild(text);        
        tag.appendChild(e_value);
    }

    // -- Number comparator node
    
    if(dtkComposerNodeNumberComparator *number_comparator_node = dynamic_cast<dtkComposerNodeNumberComparator *>(node)) {
        
        dtkComposerNodeNumberComparator::Operation operation = number_comparator_node->operation();
        
        QDomText text;

        switch(operation) {
        case dtkComposerNodeNumberComparator::LesserThan:
            text = document.createTextNode("<");
            break;
        case dtkComposerNodeNumberComparator::LesserThanOrEqual:
            text = document.createTextNode("<=");
            break;
        case dtkComposerNodeNumberComparator::GreaterThan:
            text = document.createTextNode(">");
            break;
        case dtkComposerNodeNumberComparator::GreaterThanOrEqual:
            text = document.createTextNode(">=");
            break;
        case dtkComposerNodeNumberComparator::Equal:
            text = document.createTextNode("==");
            break;
        case dtkComposerNodeNumberComparator::Differ:
            text = document.createTextNode("!=");
            break;
        default:
            break;
        }
        
        QDomElement e_operation = document.createElement("operation");
        e_operation.appendChild(text);
        
        tag.appendChild(e_operation);
    }

    // -- Number operator node
    
    if(dtkComposerNodeNumberOperator *number_operator_node = dynamic_cast<dtkComposerNodeNumberOperator *>(node)) {
        
        dtkComposerNodeNumberOperator::Operation operation = number_operator_node->operation();
        
        QDomText text;

        switch(operation) {
        case dtkComposerNodeNumberOperator::Addition:
            text = document.createTextNode("+");
            break;
        case dtkComposerNodeNumberOperator::Substraction:
            text = document.createTextNode("-");
            break;
        case dtkComposerNodeNumberOperator::Multiplication:
            text = document.createTextNode("x");
            break;
        case dtkComposerNodeNumberOperator::Division:
            text = document.createTextNode("/");
            break;
        case dtkComposerNodeNumberOperator::Increment:
            text = document.createTextNode("++");
            break;
        case dtkComposerNodeNumberOperator::Decrement:
            text = document.createTextNode("--");
            break;
        case dtkComposerNodeNumberOperator::Modulo:
            text = document.createTextNode("%");
            break;
        case dtkComposerNodeNumberOperator::Min:
            text = document.createTextNode("MIN");
            break;
        case dtkComposerNodeNumberOperator::Max:
            text = document.createTextNode("MAX");
            break;
        default:
            break;
        }
        
        QDomElement e_operation = document.createElement("operation");
        e_operation.appendChild(text);
        
        tag.appendChild(e_operation);
    }

    // -- File node
    
    if(dtkComposerNodeFile *file_node = dynamic_cast<dtkComposerNodeFile *>(node)) {
        
        QString file_name = file_node->value(file_node->outputProperty("name")).toString();
        
        if(!file_name.isEmpty()) {
            
            QDomText text = document.createTextNode(file_name);
            
            QDomElement name = document.createElement("name");
            name.appendChild(text);
            
            tag.appendChild(name);
        }
    }

    // -- String node
    
    if(dtkComposerNodeString *string_node = dynamic_cast<dtkComposerNodeString *>(node)) {
        
        QString value = string_node->value(string_node->outputProperty("value")).toString();
        
        QDomText text = document.createTextNode(value);
        
        QDomElement e_value = document.createElement("value");
        e_value.appendChild(text);
        
        tag.appendChild(e_value);
    }

    // -- String comparator node
    
    if(dtkComposerNodeStringComparator *string_comparator_node = dynamic_cast<dtkComposerNodeStringComparator *>(node)) {
        
        dtkComposerNodeStringComparator::Operation operation = string_comparator_node->operation();
        
        QDomText text;

        switch(operation) {
        case dtkComposerNodeStringComparator::LesserThan:
            text = document.createTextNode("<");
            break;
        case dtkComposerNodeStringComparator::LesserThanOrEqual:
            text = document.createTextNode("<=");
            break;
        case dtkComposerNodeStringComparator::GreaterThan:
            text = document.createTextNode(">");
            break;
        case dtkComposerNodeStringComparator::GreaterThanOrEqual:
            text = document.createTextNode(">=");
            break;
        case dtkComposerNodeStringComparator::Equal:
            text = document.createTextNode("==");
            break;
        case dtkComposerNodeStringComparator::Differ:
            text = document.createTextNode("!=");
            break;
        default:
            break;
        }
        
        QDomElement e_operation = document.createElement("operation");
        e_operation.appendChild(text);
        
        tag.appendChild(e_operation);
    }

    // -- String operator node
    
    if(dtkComposerNodeStringOperator *string_operator_node = dynamic_cast<dtkComposerNodeStringOperator *>(node)) {
        
        dtkComposerNodeStringOperator::Operation operation = string_operator_node->operation();
        
        QDomText text;

        switch(operation) {
        case dtkComposerNodeStringOperator::Append:
            text = document.createTextNode("<<");
            break;
        case dtkComposerNodeStringOperator::Prepend:
            text = document.createTextNode(">>");
            break;
        default:
            break;
        }
        
        QDomElement e_operation = document.createElement("operation");
        e_operation.appendChild(text);
        
        tag.appendChild(e_operation);
    }
    
    // -- Process node
    
    if(dtkComposerNodeProcess *process_node = dynamic_cast<dtkComposerNodeProcess *>(node)) {
        
        QString implementation = process_node->implementation();
        
        if(!implementation.isEmpty()) {
            
            QDomText text = document.createTextNode(implementation);
            
            QDomElement implementation = document.createElement("implementation");
            implementation.appendChild(text);
            
            tag.appendChild(implementation);
        }
    }

    // -- Control node
    
    if(dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(node)) {
        
        tag.setAttribute("w", QString::number(control_node->boundingRect().width()));
        tag.setAttribute("h", QString::number(control_node->boundingRect().height()));

        foreach(dtkComposerNodeControlBlock *block, control_node->blocks()) {
            
            QDomElement block_element = document.createElement("block");
            block_element.setAttribute("title", block->title());

            foreach(dtkComposerNode *block_node, block->nodes())
                this->writeNode(block_node, block_element, document);

            tag.appendChild(block_element);
        }
    }
    
    // -- Composite node
    
    if(node->kind() == dtkComposerNode::Composite) {
        foreach(dtkComposerNode *child, node->childNodes())
            this->writeNode(child, tag, document);
    }
    
    { // -- Generic node
        
        { // -- title
            
            QString node_title = node->title();
            
            QDomText text = document.createTextNode(node_title);
            
            QDomElement title = document.createElement("title");
            title.appendChild(text);
            
            tag.appendChild(title);
        }

        { // -- properties

            foreach(dtkComposerNodeProperty *property, node->inputProperties()) {
                
                QDomElement property_element = document.createElement("property");
                property_element.setAttribute("name", property->name());
                switch (property->type()) {
                case dtkComposerNodeProperty::Input:
                    property_element.setAttribute("type", "input");
                    break;
                case dtkComposerNodeProperty::HybridInput:
                    property_element.setAttribute("type", "hybridinput");
                    break;
                }
                property_element.setAttribute("hidden", property->isDisplayed() ? "false" : "true");
                if(node->kind() == dtkComposerNode::Composite)
                    property_element.setAttribute("id", d->node_ids.key(property->clonedFrom()));
                if(node->kind() == dtkComposerNode::Control && !property->blockedFrom().isEmpty())
                    property_element.setAttribute("block", property->blockedFrom());
                tag.appendChild(property_element);
            }

            foreach(dtkComposerNodeProperty *property, node->outputProperties()) {
                
                QDomElement property_element = document.createElement("property");
                property_element.setAttribute("name", property->name());
                switch (property->type()) {
                case dtkComposerNodeProperty::Output:
                    property_element.setAttribute("type", "output");
                    break;
                case dtkComposerNodeProperty::HybridOutput:
                    property_element.setAttribute("type", "hybridoutput");
                    break;
                }
                property_element.setAttribute("hidden", property->isDisplayed() ? "false" : "true");
                if(node->kind() == dtkComposerNode::Composite)
                    property_element.setAttribute("id", d->node_ids.key(property->clonedFrom()));
                if(node->kind() == dtkComposerNode::Control && !property->blockedFrom().isEmpty())
                    property_element.setAttribute("block", property->blockedFrom());
                tag.appendChild(property_element);
            }
        }
    }

    // --
    
    element.appendChild(tag);
    
    d->node_ids.insert(current_id, node);

    this->extend(node, tag, document);

    return tag;
}

void dtkComposerWriter::extend(dtkComposerNode *node, QDomElement& element, QDomDocument& document)
{
    Q_UNUSED(node);
    Q_UNUSED(element);
    Q_UNUSED(document);
}
