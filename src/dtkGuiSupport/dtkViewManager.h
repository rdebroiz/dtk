// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include "dtkGuiSupportExport.h"

#include <QtWidgets/QFrame>

class dtkAbstractView;
class dtkViewManagerPrivate;

class DTKGUISUPPORT_EXPORT dtkViewManager : public QFrame
{
    Q_OBJECT

public:
     dtkViewManager(QWidget *parent = 0);
    ~dtkViewManager(void);

public:
    void addWidget(QWidget *widget);
    void setCurrentWidget(QWidget *widget);

signals:
    void focused(dtkAbstractView *view);

public slots:
    void clear(void);
    void hideCurrentWidget(void);

private:
    dtkViewManagerPrivate *d;
};

//
// dtkViewManager.h ends here
