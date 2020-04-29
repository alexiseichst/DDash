#include "action.h"
#include <QApplication>

Action::Action(const QString & type,QObject *parent) :
    QObject(parent),
    m_type(type)
{

}

void Action::setName(const QString & name)
{
    setObjectName(name);
}

const QString Action::getName() const
{
    return objectName();
}

const QString & Action::getType() const
{
    return m_type;
}

QMap<QString,QVariant> Action::getConfigMap() const
{
    QMap<QString,QVariant> rt;
    rt.insert("application",QApplication::applicationName());
    rt.insert("type",m_type);
    rt.insert("name",objectName());
    return rt;
}
