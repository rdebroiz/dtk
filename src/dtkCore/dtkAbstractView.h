/* dtkAbstractView.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 16:00:26 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Sep  9 13:09:00 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 268
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABSTRACTVIEW_H
#define DTKABSTRACTVIEW_H

#include <dtkCore/dtkAbstractObject.h>
#include <dtkCore/dtkVec3.h>
#include <dtkCore/dtkQuat.h>

#include <QtGui/QWidget>

class dtkAbstractViewPrivate;
class dtkAbstractViewAnimator;
class dtkAbstractViewNavigator;
class dtkAbstractViewInteractor;
class dtkAbstractData;

class DTKCORE_EXPORT dtkAbstractView : public dtkAbstractObject
{
    Q_OBJECT

public:
             dtkAbstractView(      dtkAbstractView *parent = 0);
	     dtkAbstractView(const dtkAbstractView& view);
    virtual ~dtkAbstractView(void);

    virtual QString description(void) const { return ""; }

    friend QDebug operator<<(QDebug debug, const dtkAbstractView& viewer);
    friend QDebug operator<<(QDebug debug,       dtkAbstractView *viewer);

signals:
    void closed(void);

public slots:
    virtual void   link(dtkAbstractView *other);
    virtual void unlink(dtkAbstractView *other);

    virtual void   select(dtkAbstractData *data);
    virtual void unselect(dtkAbstractData *data);

    virtual void setStereo(bool on);

    virtual void setView(void *view);

    virtual void setData(dtkAbstractData *data);
    virtual void setData(dtkAbstractData *data, int inputId);

    virtual void setBackgroundColor(int red, int green, int blue);
    virtual void setBackgroundColor(double red, double green, double blue);

    virtual void *view(void);
    virtual void *data(void);
    virtual void *data(int channel);

    virtual bool stereo(void);

    virtual void  clear(void);
    virtual void  reset(void);
    virtual void update(void);

    virtual QWidget *widget(void);

    void showFullScreen(void);
    void showMinimized(void);
    void showMaximized(void);
    void showNormal(void);
    void show(void);

    void resize(int width, int height);

    void addAnimator  (dtkAbstractViewAnimator   *animator);
    void addNavigator (dtkAbstractViewNavigator  *navigator);
    void addInteractor(dtkAbstractViewInteractor *interactor);

    void  enableAnimator(QString animator);
    void disableAnimator(QString animator);

    void  enableNavigator(QString navigator);
    void disableNavigator(QString navigator);

    void  enableInteractor(QString interactor);
    void disableInteractor(QString interactor);

    dtkAbstractViewAnimator   *animator  (QString type);
    dtkAbstractViewNavigator  *navigator (QString type);
    dtkAbstractViewInteractor *interactor(QString type);

    QList<dtkAbstractViewAnimator   *> animators(void);
    QList<dtkAbstractViewNavigator  *> navigators(void);
    QList<dtkAbstractViewInteractor *> interactors(void);

    virtual void   initialize(void);
    virtual void uninitialize(void);

    // -- The following methods are needed to get tracking

    virtual void bounds(float& xmin, float& xmax, float& ymin, float& ymax, float &zmin, float& zmax);

    virtual void cameraUp(double *coordinates);
    virtual void cameraPosition(double *coordinates);
    virtual void cameraFocalPoint(double *coordinates);

    virtual void setCameraPosition(double x, double y, double z);

    // --

    virtual dtkVec3 scenePosition(void) const;
    virtual dtkQuat sceneOrientation(void) const;

    virtual void setupWandPosition(const dtkVec3& position);
    virtual void setupWandOrientation(const dtkQuat& orientation);

    virtual void setupScenePosition(const dtkVec3& position);
    virtual void setupSceneOrientation(const dtkQuat& orientation);

    virtual void         setupCameraLookAt(const dtkVec3& eye, const dtkVec3& center, const dtkVec3& up);
    virtual void  setupLeftEyeCameraLookAt(const dtkVec3& eye, const dtkVec3& center, const dtkVec3& up);
    virtual void setupRightEyeCameraLookAt(const dtkVec3& eye, const dtkVec3& center, const dtkVec3& up);

    virtual void        setupCameraFrustum(double left, double right, double bottom, double top, double near, double far);
    virtual void  setupLeftEyeCameraFrustum(double left, double right, double bottom, double top, double near, double far);
    virtual void setupRightEyeCameraFrustum(double left, double right, double bottom, double top, double near, double far);

private:
    dtkAbstractViewPrivate *d;
};

QDebug operator<<(QDebug debug, const dtkAbstractView& viewer);
QDebug operator<<(QDebug debug,       dtkAbstractView *viewer);

#endif
