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

QVariantMap ActionFile::getConfigMap() const
{
    QVariantMap rt = Action::getConfigMap();
    rt.insert("file",m_file.fileName());
    return rt;
}
