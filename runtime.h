#pragma once

#include <QObject>
#include <QTimer>

#include "ddash.h"

class Runtime : public QObject
{
    Q_OBJECT
private:
    DDash m_ddash;
    const QTimer* m_updateTimer;

    const QTimer* createTimer(Runtime *parent = nullptr);

public:
    explicit Runtime(QObject *parent = nullptr);


public slots:
    void exec();
    void updateTimeout();


signals:

};
