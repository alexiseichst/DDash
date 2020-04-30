#include "configuration.h"
#include "action.h"

#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QDir>
#include <QVariantMap>
#include <QMap>
#include <QApplication>
#include <QFileInfo>

Configuration::Configuration(QObject *parent) : QObject(parent)
{

}

void Configuration::saveActionList(QList<QVariantMap> list)
{
    QDir act_dir("act");
    if (!act_dir.exists()) QDir::current().mkdir("act");
    for(const QVariantMap map : list)
    {
        QJsonDocument doc(QJsonObject::fromVariantMap(map));
        QFileInfo file_info(act_dir,QString("%1.json").arg(doc.object()["uuid"].toString()));
        QFile file(file_info.absoluteFilePath());
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << doc.toJson();
        }
    }
}

QList<QVariantMap> Configuration::loadAllAction()
{
    QList<QVariantMap> rt;
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
                map["application"].toString() == QApplication::applicationName())
            {
                rt.append(map);
            }
        }
    }
    return rt;
}
