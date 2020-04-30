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
    explicit ActionFile(const QString & type,
                        const QString & name,
                        const QString & uuid,
                        QObject *parent);
    void setFile(const QFile & file);
    const QFile & getFile() const;
    virtual QVariantMap getConfigMap() const;

public slots:
    virtual void exec() const = 0;
    virtual QWidget* getWidget() = 0;

private:
    QFile m_file;

signals:

};
