#include "actionfilesize.h"
#include "labeltext.h"

#include <QFileInfo>

ActionFileSize::ActionFileSize(const QString &name,
                               const QString &uuid,
                               QObject *parent) :
    ActionFile("ActionFileSize",
               name,
               uuid,
               parent)
{

}

void ActionFileSize::exec() const
{
    LabelText* widget = getLabeltext();
    QFileInfo file(getFileName());
    QString  text = file.exists() ? QString("%1 bits").arg(QString::number(file.size())): "Error";
    QString  color = file.exists() ? "green" : "red";
    widget->setLabel(getName());
    widget->setText(text,color);
}

QWidget* ActionFileSize::getWidget()
{
    if (!m_widget) m_widget = new LabelText(nullptr);
    return m_widget;
}

void ActionFileSize::setName(const QString & name)
{
    ActionFile::setName(name);
}

LabelText* ActionFileSize::getLabeltext() const
{
    return dynamic_cast<LabelText*>(m_widget);
}

QMap<QString,std::function<QString(void)>> ActionFileSize::getConfigMap() const
{
    QMap<QString,std::function<QString(void)>> rt =  ActionFile::getConfigMap();
    return rt;
}

QMap<QString,std::function<void(const QString &)>> ActionFileSize::setConfigMap()
{
    QMap<QString,std::function<void(const QString &)>> rt = ActionFile::setConfigMap();;
    return rt;
}
