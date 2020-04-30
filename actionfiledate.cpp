#include "actionfiledate.h"
#include "labeltext.h"

#include <QFileInfo>
#include <QDateTime>

ActionFileDate::ActionFileDate(const QString & name,
                               const QString & uuid,
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
    QFileInfo file(getFile().fileName());
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

QVariantMap ActionFileDate::getConfigMap() const
{
    QVariantMap rt = ActionFile::getConfigMap();
    return rt;
}
