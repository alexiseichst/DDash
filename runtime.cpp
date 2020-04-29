#include "runtime.h"

Runtime::Runtime(QObject *parent) :
    QObject(parent),
    m_updateTimer(nullptr)
{

}

const QTimer* Runtime::createTimer(Runtime *parent)
{
    QTimer* timer = new QTimer(parent);
    connect(timer, &QTimer::timeout,this,&Runtime::updateTimeout);
    timer->start(1000);
    return timer;
}

void Runtime::updateTimeout()
{
    m_ddash.exec();
}

void Runtime::exec()
{
    m_updateTimer = createTimer();
    m_ddash.show();
    updateTimeout();
}
