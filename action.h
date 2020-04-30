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
    const QString getName() const;
    const QString &getType() const;
    const QString &getUuid() const;
    virtual QWidget* getWidget() = 0;
    virtual QVariantMap getConfigMap() const;

private:
    const QString m_type;
    const QString m_uuid;

public slots:
    virtual void exec() const = 0;


signals:

};
