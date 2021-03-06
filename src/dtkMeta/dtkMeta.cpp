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

#include "dtkMeta.h"
#include "dtkMetaContainerSequential.h"

// /////////////////////////////////////////////////////////////////
// dtkMetaType implementation
// /////////////////////////////////////////////////////////////////

QString dtkMetaType::description(const QVariant& v)
{
    QString str;
    QDebug dbg(&str);
    dbg.setAutoInsertSpaces(false);
    if (v.canConvert<dtkMetaContainerSequential>()) {
        dtkMetaContainerSequential mc = v.value<dtkMetaContainerSequential>();
        dbg << mc;
    } else {
        if (v.canConvert<QString>()) {
            dbg << qPrintable(v.value<QString>());
        } else {
            QMetaType::debugStream(dbg, v.constData(), v.userType());
        }
    }
    return str;
}

QVariant dtkMetaType::cloneContent(const QVariant& v)
{
    if (v.canConvert<dtkMetaContainerSequential>()) {

        QString type_name = v.typeName();
        if (type_name.endsWith("*")) {
            type_name.chop(1);
        }
        int c_id = QMetaType::type(qPrintable(type_name));
        if (c_id != QMetaType::UnknownType) {
            const void *c = *static_cast<const void * const *>(v.data());
            void *ptr = QMetaType::create(c_id, c);

            c_id = QMetaType::type(qPrintable(type_name + "*"));
            return QVariant(c_id, &ptr, 1);
        } else {
            qDebug() << Q_FUNC_INFO << "Type" << type_name << "has not be registered to QMetaType System.";
        }
        
    } else {

        int type_id = v.userType();
        QMetaType::TypeFlags flags = QMetaType(type_id).flags();

        if (int(flags & QMetaType::PointerToQObject)) {

            const QObject *o = *static_cast<const QObject * const *>(v.data());
            if (o) {
                const QMetaObject *mo = o->metaObject();
                QString class_name(mo->className());
                int class_type = QMetaType::type(qPrintable(class_name));
                
                while (class_type == QMetaType::UnknownType) {
                    mo = mo->superClass();
                    if (!mo)
                        break;
                    class_name = mo->className();
                    class_type = QMetaType::type(qPrintable(class_name));
                }
            
                if (class_type != QMetaType::UnknownType) {
                    void *ptr = QMetaType::create(class_type, o);

                    class_type = QMetaType::type(qPrintable(class_name + "*"));
                    return QVariant(class_type, &ptr, 1);
                } else {
                    qDebug() << class_name << class_type;
                    class_name = o->metaObject()->className();
                    qDebug() << Q_FUNC_INFO << "Type" << class_name << "has not be registered to QMetaType System. If they exist, parent classes are neither registered.";
                }
            }

        } else if (type_id < QMetaType::User) { // built-in type

            return v;

        } else {

            QString type_name = v.typeName();

            if (!type_name.endsWith("*")) { // Not a pointer
                return v;
            }
            type_name.chop(1);
            int type_id = QMetaType::type(qPrintable(type_name));
            if (type_id != QMetaType::UnknownType) {
                const void *data = *static_cast<const void * const *>(v.data());
                void *ptr = QMetaType::create(type_id, data);

                type_id = QMetaType::type(qPrintable(type_name + "*"));
                return QVariant(type_id, &ptr, 1);
            } else {
                qDebug() << Q_FUNC_INFO << ": Type" << type_name << "has not be registered to QMetaType System. Maybe it is not registered or maybe it is an abstract class.";
            }
        }
    }

    return QVariant();
}

QVariant dtkMetaType::createEmptyContainer(const QVariant& v)
{
    if (v.canConvert<dtkMetaContainerSequential>()) {

        QString type_name = v.typeName();
        if (type_name.endsWith("*")) {
            type_name.chop(1);
        }
        int c_id = QMetaType::type(qPrintable(type_name));
        if (c_id != QMetaType::UnknownType) {
            void *ptr = QMetaType::create(c_id);
            c_id = QMetaType::type(qPrintable(type_name + "*"));
            QVariant res = QVariant(c_id, &ptr, 1);

            if (res.canConvert<dtkMetaContainerSequential>()) {
                return res;
            } else {
                qDebug() << Q_FUNC_INFO << "Type" << res.typeName() << "is not compatible with dtkMetaContainer.";
            }

        } else {
            qDebug() << Q_FUNC_INFO << "Type" << type_name << "has not be registered to QMetaType System.";
        }
    }

    return QVariant();
}

bool dtkMetaType::destroyPointer(QVariant& v)
{
    QString type_name = QString(v.typeName());
    bool ok = false;

    if (type_name.endsWith("*")) {
        void *ptr = *static_cast<void **>(v.data());
        if (ptr) {
            type_name.chop(1);
            int type_id = QMetaType::type(qPrintable(type_name));
            QMetaType::destroy(type_id, ptr);
            v.clear();
            ok = true;
        }
    } else {
        qDebug() << Q_FUNC_INFO << "Type" << type_name << "is not of pointer type.";
    }

    return ok;
}

// 
// dtkMeta.cpp ends here
