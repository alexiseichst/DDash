#include "ddash.h"
#include "action.h"
#include "actionfilesize.h"
#include "actionfileexists.h"
#include "actionfiledate.h"
#include "mainwindow.h"
#include "configuration.h"
#include "adddialog.h"

#include <QSvgRenderer>
#include <QVBoxLayout>
#include <qDebug>

DDash::DDash(QObject *parent) :
    QObject(parent)
{
    // ActionFileSize
    m_strToAction.insert("ActionFileSize",[](const QString &name,const QString &uuid,QObject* parent)
    {
        return new ActionFileSize(name,uuid,parent);
    });

    // ActionFileExists
    m_strToAction.insert("ActionFileExists",[](const QString &name,const QString &uuid,QObject* parent)
    {
        return new ActionFileExists(name,uuid,parent);
    });


    // ActionFileDate
    m_strToAction.insert("ActionFileDate",[](const QString &name,const QString &uuid,QObject* parent)
    {
        return new ActionFileDate(name,uuid,parent);
    });

    // Read json config
    loadConfig();
}

DDash::~DDash()
{
    saveConfig();
}

void DDash::loadConfig()
{
    QList<QVariantMap> list = Configuration::loadAllAction();
    for (const QVariantMap map: list)
        addAction(createAction(map));
}

void DDash::saveConfig()
{
    QList<QVariantMap> list;
    for(Action* a : m_actions)
    {
        QVariantMap str_map;
        auto config_map = a->getConfigMap();
        for (auto arg : config_map.keys())
            str_map.insert(arg,config_map[arg]());
        list.append(str_map);
    }
    Configuration::saveActionList(list);
}

Action* DDash::createAction(const QVariantMap &params,QObject* parent) const
{
    const QString uuid = params.contains("uuid") ? params["uuid"].toString() : QString();
    Action* action = strToAction(params["type"].toString(),
            params["name"].toString(),
            uuid,
            parent);

    QVariantMap others(params);
    auto config_map = action->setConfigMap();
    for (QString k : others.keys())
    {
        if (config_map.contains(k))
            config_map[k](others[k].toString());
    }
    return action;
}

Action* DDash::strToAction(const QString &type,const QString &name,const QString &uuid,QObject* parent) const
{
    Action* action = nullptr;
    if(m_strToAction.contains(type))
        action = m_strToAction[type](name,uuid,parent);
    return action;
}

void DDash::addAction(Action* action)
{
    m_actions << action;
}

void DDash::addClicked()
{
    AddDialog dialog(m_mainWindow,m_strToAction);
    if (dialog.exec() == QDialog::Accepted)
    {
        Action* a = createAction(dialog.getActionMap());
        addAction(a);
        m_mainWindow->addActionWidget(a->getWidget());
    }
}

void DDash::exec()
{
    for(Action* a : m_actions)
    {
        if (a->canExec())
            a->exec();
    }
}

void DDash::show()
{
    m_mainWindow = new MainWindow(nullptr);
    connect(m_mainWindow,&MainWindow::addClicked,this,&DDash::addClicked);
    for(Action* a : m_actions)
        m_mainWindow->addActionWidget(a->getWidget());
    m_mainWindow->show();

    if (m_actions.isEmpty())
        addClicked();
}
