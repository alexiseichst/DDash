#pragma once

#include "actionfile.h"

#include <QFile>
#include <QObject>
#include <QMap>
#include <QVariant>

class LabelText;

class ActionFileSize : public ActionFile
{
    Q_OBJECT
public:
    explicit ActionFileSize(QObject *parent = nullptr);

public slots:
    virtual void exec() const;
    virtual QWidget* getWidget();
    virtual QVariantMap getConfigMap() const;

private:
    LabelText* m_widget;


signals:

};
