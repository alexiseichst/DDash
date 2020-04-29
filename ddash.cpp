#include "ddash.h"
#include "action.h"
#include "actionfilesize.h"
#include "actionfileexists.h"
#include "mainwindow.h"
#include "configuration.h"

#include <QSvgRenderer>
#include <QVBoxLayout>

DDash::DDash(QObject *parent) :
    QObject(parent)
{
    m_strToAction.insert("ActionFileSize",[](QObject* parent){return new ActionFileSize(parent);});
    m_strToSetAction.insert("ActionFileSize",[](const QVariantMap & params,Action* action)
    {
        ActionFileSize* action_file_size = dynamic_cast<ActionFileSize*>(action);
        action_file_size->setFile(QFile(params["file"].toString()));
    });

    m_strToAction.insert("ActionFileExists",[](QObject* parent){return new ActionFileExists(parent);});
    m_strToSetAction.insert("ActionFileExists",[](const QVariantMap & params,Action* action)
    {
        ActionFileExists* action_file_size = dynamic_cast<ActionFileExists*>(action);
        action_file_size->setFile(QFile(params["file"].toString()));
    });

    QList<QVariantMap> list = Configuration::loadAllAction();
    for (const QVariantMap map: list)
    {
        addAction(createAction(map));
    }
}

DDash::~DDash()
{
    QList<QVariantMap> list;
    for(Action* a : m_actions)
    {
        list.append(a->getConfigMap());
    }
    Configuration::saveActionList(list);
}

Action* DDash::createAction(const QVariantMap & params,QObject* parent) const
{
    Action* action = strToAction(params["type"].toString(),parent);

    action->setName(params["name"].toString());
    m_strToSetAction[params["type"].toString()](params,action);

    return action;
}

Action* DDash::strToAction(const QString & name,QObject* parent) const
{
    Action* action = nullptr;
    if(m_strToAction.contains(name))
    {
        action = m_strToAction[name](parent);
    }
    return action;
}

void DDash::addAction(Action* action)
{
    m_actions << action;
}

void DDash::exec()
{
    for(Action* a : m_actions)
    {
        a->exec();
    }
}

void DDash::show()
{
    m_mainWindow = new MainWindow(nullptr);

    for(Action* a : m_actions)
    {
        m_mainWindow->addActionWidget(a->getWidget());
    }
    m_mainWindow->show();
}
