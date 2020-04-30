#pragma once

#include "actionfile.h"

#include <QFile>
#include <QObject>
#include <QMap>
#include <QVariant>
#include <QString>

class LabelText;

class ActionFileSize : public ActionFile
{
    Q_OBJECT
public:
    explicit ActionFileSize(const QString & name,
                            const QString & uuid,
                            QObject *parent);

public slots:
    virtual void exec() const;
    virtual QWidget* getWidget();
    virtual QVariantMap getConfigMap() const;

private:
    LabelText* m_widget;


signals:

};
