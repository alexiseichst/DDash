#include <QApplication>
#include <QTimer>

#include "runtime.h"

Runtime* createRunTime(QObject *parent = nullptr)
{
    Runtime* rt = new Runtime(parent);
    QTimer::singleShot(0,rt,&Runtime::exec);
    return rt;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("DDash");
    Runtime rt(nullptr);
    QTimer::singleShot(0,&rt,&Runtime::exec);
    return a.exec();
}
