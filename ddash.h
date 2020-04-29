#pragma once

#include <QObject>
#include <QList>
#include <functional>
#include <QMap>

class Action;
class MainWindow;
class ActionFileSize;

class DDash : public QObject
{
    Q_OBJECT
public:
    explicit DDash(QObject *parent = nullptr);
    ~DDash();

public slots:
    void exec();
    void show();

private slots:
    void saveConfig();
    void loadConfig();

private:
    MainWindow* m_mainWindow;
    QList<Action*> m_actions;
    QMap<QString,std::function<Action*(QObject* parent)>> m_strToAction;
    QMap<QString,std::function<void(const QVariantMap & params,Action* action)>> m_strToSetAction;

    Action* createAction(const QVariantMap & params,QObject* parent = nullptr) const;
    void addAction(Action* action);
    Action* strToAction(const QString & name,QObject* parent = nullptr) const;
    void testInit();


signals:

};
