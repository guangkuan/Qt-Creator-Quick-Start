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
    QPainter painter(this);

//    QPen pen; //画笔
//    pen.setColor(QColor(255, 0, 0));
//    //最后一个参数alpha是设置透明度的
//    QBrush brush(QColor(0, 255, 0, 125)); //画刷
//    painter.setPen(pen); //添加画笔
//    painter.setBrush(brush); //添加画刷
//    painter.drawRect(50, 50, 200, 100); //绘制矩形

    QPen pen(Qt::DotLine);
    QBrush brush(Qt::darkCyan);
    brush.setStyle(Qt::Dense1Pattern);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(100.0, 100.0, 200.0, 200.0);

    painter.drawLine(QPointF(0, 0), QPointF(100, 100));

//    QRectF rectangle(10.0, 20.0, 80.0, 60.0);
//    painter.drawEllipse(rectangle);

    QRectF rectangle(100.0, 47.0, 200.0, 200.0); //矩形
    int startAngle = 30 * 16;     //起始角度
    int spanAngle = 120 * 16;   //跨越度数
    painter.drawArc(rectangle, startAngle, spanAngle);
}
