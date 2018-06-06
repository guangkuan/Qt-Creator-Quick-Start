#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>

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
    void processPendingDatagram();

private:
    Ui::Widget *ui;
    QUdpSocket *receiver;
};

#endif // WIDGET_H
