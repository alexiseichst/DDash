#include "actionfilesize.h"
#include "labeltext.h"

#include <QFileInfo>

ActionFileSize::ActionFileSize(const QString &name,
                               const QString &uuid,
                               QObject *parent) :
    ActionFile("ActionFileSize",
               name,
               uuid,
               parent),
    m_widget(nullptr)
{

}

void ActionFileSize::exec() const
{
    QFileInfo file(getFile().fileName());
    QString  text = "Error";
    QString  color = "red";
    if(m_widget &&
            file.exists())
    {
        text = QString("%1 Ko").arg(QString::number(file.size()/1000));
        color = "green";
    }
    m_widget->setText(text,color);
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
