#include "actionfiledate.h"
#include "labeltext.h"

#include <QFileInfo>
#include <QDateTime>

ActionFileDate::ActionFileDate(const QString &name,
                               const QString &uuid,
                               QObject *parent) :
    ActionFile("ActionFileDate",
               name,
               uuid,
               parent),
    m_widget(nullptr)
{

}

void ActionFileDate::exec() const
{
    QFileInfo file(getFileName());
    QString  text = "Error";
    QString  color = "red";
    if(m_widget &&
            file.exists())
    {
        text = file.lastModified().date().toString(Qt::SystemLocaleShortDate);
        color = "green";
    }
    m_widget->setText(text,color);
}

QWidget* ActionFileDate::getWidget()
{
    m_widget = new LabelText(nullptr);

    m_widget->setLabel(getName());

    return m_widget;
}

QMap<QString,std::function<QString(void)>> ActionFileDate::getConfigMap() const
{
    QMap<QString,std::function<QString(void)>> rt = ActionFile::getConfigMap();;
    return rt;
}

QMap<QString,std::function<void(const QString &)>> ActionFileDate::setConfigMap()
{
    QMap<QString,std::function<void(const QString &)>> rt = ActionFile::setConfigMap();
    return rt;
}
