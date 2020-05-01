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
               parent)
{

}

void ActionFileDate::exec() const
{
    LabelText* label = getLabeltext();
    QFileInfo file(getFileName());
    QString  text =  file.exists() ? file.lastModified().date().toString(Qt::SystemLocaleShortDate):"Error";
    QString  color = file.exists() ? "green":"red";
    label->setText(text,color);
    label->setLabel(getName());
}

LabelText* ActionFileDate::getLabeltext() const
{
    return dynamic_cast<LabelText*>(m_widget);
}

QWidget* ActionFileDate::getWidget()
{
    m_widget = new LabelText(nullptr);

    getLabeltext()->setLabel(getName());

    return m_widget;
}

void ActionFileDate::setName(const QString & name)
{
    ActionFile::setName(name);
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
