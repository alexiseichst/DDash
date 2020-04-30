#pragma once

#include "actionfile.h"

#include <QFile>
#include <QObject>
#include <QMap>
#include <QVariant>


class LabelStatus;

class ActionFileExists : public ActionFile
{
    Q_OBJECT
public:
    explicit ActionFileExists(const QString &name,
                              const QString &uuid,
                              QObject *parent);

public slots:
    virtual void exec() const;
    virtual QWidget* getWidget();
    virtual QVariantMap getConfigMap() const;

private:
    LabelStatus* m_widget;


signals:

};
