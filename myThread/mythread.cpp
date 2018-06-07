#include "mythread.h"
#include <QDebug>

//需要手动改构造函数
MyThread::MyThread(QObject *parent) : QThread(parent)
{
    stopped = false;
}

void MyThread::run()
{
    long int i = 0;
    while (!stopped) {
       QString str = QString("in MyThread: %1").arg(i);
       emit stringChanged(str);
       msleep(1000);
       i++;
    }
    stopped = false;
}

void MyThread::stop()
{
    stopped = true;
}
