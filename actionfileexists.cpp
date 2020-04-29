#include "actionfileexists.h"
#include "labelstatus.h"

#include <QFileInfo>

ActionFileExists::ActionFileExists(QObject *parent) :
    ActionFile("ActionFileExists",parent),
    m_widget(nullptr)
{

}

void ActionFileExists::exec() const
{
    QFileInfo file(getFile().fileName());
    if(m_widget) m_widget->setStatus(file.exists());
}

QWidget* ActionFileExists::getWidget()
{
    m_widget = new LabelStatus(nullptr);

    m_widget->setLabel(getName());

    return m_widget;
}

QVariantMap ActionFileExists::getConfigMap() const
{
    QVariantMap rt = ActionFile::getConfigMap();
    return rt;
}
