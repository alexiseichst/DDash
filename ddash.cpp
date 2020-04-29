#include "ddash.h"
#include "action.h"
#include "actionfilesize.h"
#include "actionfileexists.h"
#include "mainwindow.h"

#include <QSvgRenderer>
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QDir>

DDash::DDash(QObject *parent) : QObject(parent)
{
    m_strToAction.insert("ActionFileSize",[](QObject* parent){return new ActionFileSize(parent);});
    m_strToSetAction.insert("ActionFileSize",[](const QMap<QString,QString> & params,Action* action)
    {
        ActionFileSize* action_file_size = dynamic_cast<ActionFileSize*>(action);
        action_file_size->setFile(QFile(params["file"]));
    });

    m_strToAction.insert("ActionFileExists",[](QObject* parent){return new ActionFileExists(parent);});
    m_strToSetAction.insert("ActionFileExists",[](const QMap<QString,QString> & params,Action* action)
    {
        ActionFileExists* action_file_size = dynamic_cast<ActionFileExists*>(action);
        action_file_size->setFile(QFile(params["file"]));
    });

    testInit();
    saveConfig();
}

void DDash::saveConfig()
{
    for(Action* a : m_actions)
    {
        QJsonDocument doc(QJsonObject::fromVariantMap(a->getConfigMap()));
        QFile file(QString("act/%1.json").arg(doc.object()["name"].toString()));
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << doc.toJson();
        }
    }
}

void DDash::loadConfig()
{
    QStringList json_list = QDir::current().entryList(QStringList() << "act/*.json",QDir::Files);
    for(const QString json : json_list)
    {
        QFile file(json);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            const QVariantMap map = QJsonObject::fromJson(file.readAll()).toVariantMap()
            file.close();
            
            if (map.isValid() &&
                map.contains("application") && 
                map["application"])
            {
                addAction(createAction(map));
            }
        }
    }
}

void DDash::testInit()
{
    QVariantMap params;
    params.insert("type","ActionFileSize");
    params.insert("name","CMakeLists");
    params.insert("file","C:/workdir/dev/WinControler/CMakeLists.txt.user");
    addAction(createAction(params));

    params.clear();
    params.insert("type","ActionFileExists");
    params.insert("name","Image");
    params.insert("file","C:/Users/Alexis/Videos/Radeon ReLive/2020.03.25-17.04.png");
    addAction(createAction(params));
}

Action* DDash::createAction(const QVariantMap & params,QObject* parent) const
{
    Action* action = strToAction(params["type"],parent);

    action->setName(params["name"]);
    m_strToSetAction[params["type"]](params,action);

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
