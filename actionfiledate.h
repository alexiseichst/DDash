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

public slots:
    virtual void exec() const;
    virtual QWidget* getWidget();
    virtual QVariantMap getConfigMap() const;

private:
    LabelText* m_widget;


signals:

};
