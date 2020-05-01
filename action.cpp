#include "action.h"

#include <QApplication>
#include <QUuid>

Action::Action(const QString &type,
               const QString &name,
               const QString &uuid,
               QObject *parent) :
    QObject(parent),
    m_type(type),
    m_uuid(uuid.isEmpty()?QUuid::createUuid().toString(QUuid::Id128):uuid),
    m_widget(nullptr)
{
    setObjectName(name);
}

QString Action::getName() const
{
    return objectName();
}

void Action::setName(const QString & name)
{
    setObjectName(name);
}

const QString &Action::getType() const
{
    return m_type;
}

const QString &Action::getUuid() const
{
    return m_uuid;
}

bool Action::canExec() const
{
    return (m_widget != nullptr);
}

QMap<QString,std::function<QString(void)>> Action::getConfigMap() const
{
    QMap<QString,std::function<QString(void)>> rt;
    rt.insert("type",std::bind(&Action::getType,this));
    rt.insert("name",std::bind(&Action::getName,this));
    rt.insert("uuid",std::bind(&Action::getUuid,this));
    return rt;
}

QMap<QString,std::function<void(const QString &)>> Action::setConfigMap()
{
    QMap<QString,std::function<void(const QString &)>> rt;
    rt.insert("name",std::bind(&Action::setName,this,std::placeholders::_1));
    return rt;
}
