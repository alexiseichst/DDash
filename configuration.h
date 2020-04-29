#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QVariantMap>

class Action;

class Configuration : public QObject
{
    Q_OBJECT
public:
    explicit Configuration(QObject *parent = nullptr);
    static void saveActionList(QList<QVariantMap> list);
    static QList<QVariantMap> loadAllAction();
};

#endif // CONFIGURATION_H
