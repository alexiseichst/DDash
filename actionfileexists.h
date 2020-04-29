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
    explicit ActionFileExists(QObject *parent = nullptr);

public slots:
    virtual void exec() const;
    virtual QWidget* getWidget();
    virtual QMap<QString,QVariant> getConfigMap() const;

private:
    LabelStatus* m_widget;


signals:

};
