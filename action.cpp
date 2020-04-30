#include "action.h"

#include <QApplication>
#include <QUuid>

Action::Action(const QString &type,
               const QString &name,
               const QString &uuid,
               QObject *parent) :
    QObject(parent),
    m_type(type),
    m_uuid(uuid.isEmpty()?QUuid::createUuid().toString(QUuid::Id128):uuid)
{
    setObjectName(name);
}

const QString Action::getName() const
{
    return objectName();
}

const QString &Action::getType() const
{
    return m_type;
}

const QString &Action::getUuid() const
{
    return m_uuid;
}

QVariantMap Action::getConfigMap() const
{
    QVariantMap rt;
    rt.insert("application",QApplication::applicationName());
    rt.insert("type",getType());
    rt.insert("name",objectName());
    rt.insert("uuid",getUuid());
    return rt;
}
