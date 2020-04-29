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
#include <QVariantMap>
#include <QMap>
#include <QApplication>
#include <QFileInfo>

DDash::DDash(QObject *parent) : QObject(parent)
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

    loadConfig();
}

DDash::~DDash()
{
    saveConfig();
}

void DDash::saveConfig()
{
    QDir act_dir("act");
    if (act_dir.exists())
    {
        QStringList json_list = act_dir.entryList(QStringList() << "*.json",QDir::Files);
        for(const QString json : json_list)
        {
            QFile file(json);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                const QJsonObject obj = QJsonDocument::fromJson(file.readAll()).object();
                const QVariantMap map = obj.toVariantMap();
                file.close();

                if (map.contains("application") &&
                    map["application"].toString() == QApplication::applicationName())
                {
                    file.remove();
                }
            }
        }
    }
    else
    {
        QDir::current().mkdir("act");
        for(Action* a : m_actions)
        {
            QJsonDocument doc(QJsonObject::fromVariantMap(a->getConfigMap()));
            QFileInfo file_info(act_dir,QString("%1.json").arg(doc.object()["name"].toString()));
            QFile file(file_info.absoluteFilePath());
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream out(&file);
                out << doc.toJson();
            }
        }
    }
}

void DDash::loadConfig()
{
    const QDir act_dir("act");
    const QStringList json_list = act_dir.entryList(QStringList() << "*.json",QDir::Files);
    for(const QString json : json_list)
    {
        const QFileInfo file_info(act_dir,json);
        QFile file(file_info.absoluteFilePath());
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            const QJsonObject obj = QJsonDocument::fromJson(file.readAll()).object();
            const QVariantMap map = obj.toVariantMap();
            file.close();
            
            if (map.contains("application") &&
                map["application"].toString().trimmed() == QApplication::applicationName())
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
