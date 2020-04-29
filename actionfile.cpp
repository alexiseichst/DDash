#include "actionfile.h"

ActionFile::ActionFile(const QString & type,QObject *parent) :
    Action(type,parent)
{

}

void ActionFile::setFile(const QFile & file)
{
    m_file.setFileName(file.fileName());
}

const QFile & ActionFile::getFile() const
{
    return m_file;
}

QMap<QString,QVariant> ActionFile::getConfigMap() const
{
    QMap<QString,QVariant> rt = Action::getConfigMap();
    rt.insert("file",m_file.fileName());
    return rt;
}
