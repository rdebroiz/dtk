/* dtkApplication.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/01/26 12:24:18
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkWidgetsExport.h"

#include <dtkCore/dtkAbstractApplication.h>
#include <dtkCore/dtkCoreApplication.h>

#include <QApplication>

class DTKWIDGETS_EXPORT dtkApplication: public QApplication, public dtkAbstractApplication
{
public:
             dtkApplication(int &argc, char **argv): QApplication(argc, argv), dtkAbstractApplication() {};
    virtual ~dtkApplication(void);

public:
    bool noGui(void) { return false; };
};

static dtkAbstractApplication* create(int &argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
        if(!qstrcmp(argv[i], "-nw") || !qstrcmp(argv[i], "-no-window"))
            return new dtkCoreApplication(argc, argv);

    return new dtkApplication(argc, argv);

}

