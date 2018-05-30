#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(Qt::blue);
    p.drawRect(0, 0, 100, 100);

    p.setWindow(-50, -50, 100, 100);
    p.setPen(Qt::red);
    p.drawRect(0, 0, 100, 100);

    int side = qMin(width(), height());
    p.setViewport((width() - side)/2, (height() - side) /2, side, side);
    p.setPen(Qt::green);
    p.drawRect(10, 10, 20, 20);
}
