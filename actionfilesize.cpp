#include "actionfilesize.h"
#include "labeltext.h"

#include <QFileInfo>

ActionFileSize::ActionFileSize(QObject *parent) :
    ActionFile("ActionFileSize",parent),
    m_widget(nullptr)
{

}

void ActionFileSize::exec() const
{
    QFileInfo file(getFile().fileName());
    QString  text = "Error";
    if(m_widget &&
            file.exists())
    {
        text = QString("%1 Ko").arg(QString::number(file.size()/1000));
    }
    m_widget->setText(text);
}

QWidget* ActionFileSize::getWidget()
{
    m_widget = new LabelText(nullptr);

    m_widget->setLabel(getName());

    return m_widget;
}

QVariantMap ActionFileSize::getConfigMap() const
{
    QVariantMap rt = ActionFile::getConfigMap();
    return rt;
}
