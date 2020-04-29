#pragma once

#include <QObject>
#include <QMap>
#include <QVariant>

class Action : public QObject
{
    Q_OBJECT
public:
    explicit Action(const QString & type,QObject *parent = nullptr);
    void setName(const QString & name);
    const QString getName() const;
    const QString & getType() const;
    virtual QWidget* getWidget() = 0;
    virtual QVariantMap getConfigMap() const;

private:
    const QString m_type;

public slots:
    virtual void exec() const = 0;


signals:

};
