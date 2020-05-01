#pragma once

#include "actionfile.h"

#include <QFile>
#include <QObject>
#include <QMap>
#include <QVariant>
#include <QString>

class LabelText;

class ActionFileDate : public ActionFile
{
    Q_OBJECT
public:
    explicit ActionFileDate(const QString &name,
                            const QString &uuid,
                            QObject *parent);
    virtual void setName(const QString &);
    virtual QMap<QString,std::function<QString(void)>> getConfigMap() const;
    virtual QMap<QString,std::function<void(const QString &)>> setConfigMap();

public slots:
    virtual void exec() const;
    virtual QWidget* getWidget();

private:
    LabelText* getLabeltext() const;
};
