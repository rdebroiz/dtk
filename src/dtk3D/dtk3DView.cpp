/* dtk3DView.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Sat Mar 30 13:41:55 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Apr  3 11:08:42 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 46
 */

/* Change Log:
 * 
 */

#include "dtk3DItem.h"
#include "dtk3DScene.h"
#include "dtk3DView.h"

#include <Qt3D/QGLBuilder>
#include <Qt3D/QGLSceneNode>
#include <Qt3D/QGLSphere>
#include <Qt3D/QGLView>

#include <QtGui>

class dtk3DViewPrivate
{
public:
    dtk3DScene *scene;
};

dtk3DView::dtk3DView(QWindow *parent) : QGLView(parent), d(new dtk3DViewPrivate)
{
    d->scene = NULL;

    this->setOption(QGLView::ObjectPicking, true);
}

dtk3DView::~dtk3DView(void)
{
    delete d;
}

void dtk3DView::setScene(dtk3DScene *scene)
{
    d->scene = scene;
}

void dtk3DView::initializeGL(QGLPainter *painter)
{
    if (d->scene)
        d->scene->initialize(painter, this);

    QGLView::initializeGL(painter);
}

void dtk3DView::paintGL(QGLPainter *painter)
{
    if (d->scene)
        d->scene->paint(painter, this);

    QGLView::paintGL(painter);
}

void dtk3DView::resizeGL(int width, int height)
{
    QGLView::resizeGL(width, height);
}

const QPoint dtk3DView::mapToScreen(const QVector3D& point)
{
    QMatrix4x4 modl = this->camera()->modelViewMatrix();
    QMatrix4x4 proj = this->camera()->projectionMatrix(qreal(this->width())/qreal(this->height()));

    QVector4D pos = QVector4D(point, 1.0);
    pos = modl.map(pos);
    pos = proj.map(pos);
    pos /= pos.w();
    pos *= 0.5;
    pos += QVector4D(0.5, 0.5, 0.5, 0.5);
    
    QPoint position;
    position.setX(                pos.x()*qreal(this->width()));
    position.setY(this->height()-(pos.y()*qreal(this->height())));
    return position;
}

void dtk3DView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Tab) {
        this->setOption(QGLView::ShowPicking, ((options() & QGLView::ShowPicking) == 0));
        this->update();
    }

    QGLView::keyPressEvent(event);
}

void dtk3DView::mouseMoveEvent(QMouseEvent *event)
{
    QGLView::mouseMoveEvent(event);
}

void dtk3DView::mousePressEvent(QMouseEvent *event)
{
    QGLView::mousePressEvent(event);
}

void dtk3DView::mouseReleaseEvent(QMouseEvent *event)
{
    QGLView::mouseReleaseEvent(event);
}
