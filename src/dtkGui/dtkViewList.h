/* dtkViewList.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:38:55 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 16 09:38:58 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVIEWLIST_H
#define DTKVIEWLIST_H

#include <QtGui>

class dtkViewListPrivate;

class dtkViewList : public QListWidget
{
    Q_OBJECT

public:
     dtkViewList(QWidget *parent = 0);
    ~dtkViewList(void);
    
private:
    dtkViewListPrivate *d;
};

#endif // DTKVIEWLIST_H
