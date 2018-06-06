#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetWork>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void sendMessage();

private:
    Ui::Widget *ui;
    QTcpServer *tcpServer;
};

#endif // WIDGET_H
