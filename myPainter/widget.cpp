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
    painter.setPen(pen);
    painter.drawLine(QPointF(0, 0), QPointF(100, 100));

    //线性渐变
    QLinearGradient linearGradient(QPointF(100, 100), QPointF(150, 200));
    //插入颜色
    linearGradient.setColorAt(0, Qt::yellow);
    linearGradient.setColorAt(0.5, Qt::red);
    linearGradient.setColorAt(1, Qt::green);
    //指定渐变区域以外的区域的扩散方式
    linearGradient.setSpread(QGradient::RepeatSpread);
    //使用渐变作为画刷
    QBrush brush_l(linearGradient);
    painter.setBrush(brush_l);
    QRectF rect(100.0, 100.0, 200.0, 200.0);
    painter.drawRect(rect);

    //辐射渐变
    QRadialGradient radialGradient(QPointF(350.0, 50.0), 50.0, QPointF(380.0, 80.0));
    radialGradient.setColorAt(0, Qt::black);
    radialGradient.setColorAt(1, Qt::white);
    QBrush brush_r(radialGradient);
    painter.setBrush(brush_r);
    painter.drawEllipse(QPointF(350.0, 50.0), 50.0, 50.0);

    //锥形渐变
    QConicalGradient conicalGradient(QPointF(360, 190), 15);
    conicalGradient.setColorAt(0.2, Qt::yellow);
    conicalGradient.setColorAt(0.9, Qt::cyan);
    QBrush brush_c(conicalGradient);
    painter.setBrush(brush_c);
    painter.drawEllipse(QPointF(350.0, 200.0), 50.0, 50.0);

//    QRectF rectangle(10.0, 20.0, 80.0, 60.0);
//    painter.drawEllipse(rectangle);

    QRectF rectangle(100.0, 47.0, 200.0, 200.0); //矩形
    int startAngle = 30 * 16;     //起始角度
    int spanAngle = 120 * 16;   //跨越度数
    painter.drawArc(rectangle, startAngle, spanAngle);

    //如果要绘制一个复杂的图形，尤其是要重复绘制这样的图形，那么可以使用QPainterPath类
    QPainterPath path1;
    path1.addEllipse(500, 100, 50, 50);
    path1.lineTo(600, 200);
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::darkGray);
    painter.drawPath(path1);
    QPainterPath path2;
    path2.addPath(path1);
    //path2竟然继承了path的位置
    path2.translate(100,0);
    painter.drawPath(path2);
    QPainterPath path3;
    path3.moveTo(500, 0);
    path3.lineTo(600, 100);
    path3.lineTo(700, 100);
    painter.drawPath(path3);
    QPainterPath path4;
    path4.addRect(550, 250, 50, 50);
    path4.lineTo(500, 200);
    painter.drawPath(path4);
    QPainterPath path5;
    path5.addRect(650, 200, 50, 50);
    //移动到(100, 100)点
    path5.moveTo(700, 250);
    path5.lineTo(750, 300);
    painter.drawPath(path5);

    //文字
    painter.drawText(175, 75,  "油条豆浆");
    painter.drawText(rect, Qt::AlignHCenter, "土豆沙拉");

    QFont font("宋体", 15, QFont::Bold, true);
    //设置下划线
    font.setUnderline(true);
    //设置上划线
    font.setOverline(true);
    //设置字母大小写
    font.setCapitalization(QFont::SmallCaps);
    //设置字符间的间距
    font.setLetterSpacing(QFont::AbsoluteSpacing, 10);
    //使用字体
    painter.setFont(font);
    painter.setPen(Qt::yellow);
    painter.drawText(110, 20, tr("西红柿炒鸡蛋"));
    //将坐标原点变为(50, 50)
    painter.translate(50, 50);
    //旋转90度
    painter.rotate(90);
    painter.drawText(60, 40, tr("..拍黄瓜.."));

}
