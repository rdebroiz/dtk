/* dtkComposerTransmitter.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:14:29 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 17:07:20 2012 (+0100)
 *           By: tkloczko
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTER_TPP
#define DTKCOMPOSERTRANSMITTER_TPP

#include <QtCore/QString>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty transmitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitter<T>::dtkComposerTransmitter(dtkComposerNode *parent) : dtkComposerAbstractTransmitter(parent) 
{

};

//! Destroys the transmitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitter<T>::~dtkComposerTransmitter(void)
{

};

//! Returns description of the transmitter.
/*! 
 *  
 */
template <typename T> QString dtkComposerTransmitter<T>::identifier(void) const
{
    return "dtkComposerTransmitter";
};

#endif
