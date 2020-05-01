#pragma once

#include <QObject>
#include <QMap>
#include <QVariant>
#include <QUuid>

class Action : public QObject
{
    Q_OBJECT
public:
    explicit Action(const QString &type,
                    const QString &name,
                    const QString &uuid,
                    QObject *parent);
    QString getName() const;
    const QString &getType() const;
    const QString &getUuid() const;
    virtual QWidget* getWidget() = 0;
    virtual void setName(const QString &);
    virtual QMap<QString,std::function<QString(void)>> getConfigMap() const;
    virtual QMap<QString,std::function<void(const QString &)>> setConfigMap();

private:
    const QString m_type;
    const QString m_uuid;
    const QString m_application;

public slots:
    virtual void exec() const = 0;


signals:

};
