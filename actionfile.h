#pragma once

#include "action.h"

#include <QFile>
#include <QObject>
#include <QMap>
#include <QVariant>


class ActionFile : public Action
{
    Q_OBJECT
public:
    explicit ActionFile(const QString &type,
                        const QString &name,
                        const QString &uuid,
                        QObject *parent);
    void setFileName(const QString &name);
    const QString &getFileName() const;
    virtual void setName(const QString &);
    virtual QMap<QString,std::function<QString(void)>> getConfigMap() const;
    virtual QMap<QString,std::function<void(const QString &)>> setConfigMap();

public slots:
    virtual void exec() const = 0;

private:
    QString m_file;
};
