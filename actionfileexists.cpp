#include "actionfileexists.h"
#include "labelstatus.h"

#include <QFileInfo>

ActionFileExists::ActionFileExists(const QString &name,
                                   const QString &uuid,
                                   QObject *parent) :
    ActionFile("ActionFileExists",
               name,
               uuid,
               parent),
    m_widget(nullptr)
{

}

void ActionFileExists::exec() const
{
    QFileInfo file(getFileName());
    if(m_widget)
    {
        m_widget->setStatus(file.exists());
        m_widget->setLabel(getName());
    }
}

QWidget* ActionFileExists::getWidget()
{
    if (!m_widget) m_widget = new LabelStatus(nullptr);
    return m_widget;
}

void ActionFileExists::setName(const QString & name)
{
    ActionFile::setName(name);
}

QMap<QString,std::function<QString(void)>> ActionFileExists::getConfigMap() const
{
    QMap<QString,std::function<QString(void)>> rt = ActionFile::getConfigMap();
    return rt;
}

QMap<QString,std::function<void(const QString &)>> ActionFileExists::setConfigMap()
{
    QMap<QString,std::function<void(const QString &)>> rt = ActionFile::setConfigMap();
    return rt;
}
