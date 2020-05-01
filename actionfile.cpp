#include "actionfile.h"

ActionFile::ActionFile(const QString &type,
                       const QString &name,
                       const QString &uuid,
                       QObject *parent) :
    Action(type,
           name,
           uuid,
           parent)
{

}

void ActionFile::setFileName(const QString &name)
{
    m_file = name;
}

void ActionFile::setName(const QString & name)
{
    Action::setName(name);
}

const QString &ActionFile::getFileName() const
{
    return m_file;
}

QMap<QString,std::function<QString(void)>> ActionFile::getConfigMap() const
{
    QMap<QString,std::function<QString(void)>> rt = Action::getConfigMap();
    rt.insert("file",std::bind(&ActionFile::getFileName,this));
    return rt;
}

QMap<QString,std::function<void(const QString &)>> ActionFile::setConfigMap()
{
    QMap<QString,std::function<void(const QString &)>> rt = Action::setConfigMap();
    rt.insert("file",std::bind(&ActionFile::setFileName,this,std::placeholders::_1));
    return rt;
}
