#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    void stop();

protected:
    void run();

private:
    volatile bool stopped;

signals:
    void stringChanged(const QString &);
public slots:
};

#endif // MYTHREAD_H
