#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBrush(Qt::red);
    painter.drawRect(0, 0, 100, 100);
    painter.setBrush(Qt::yellow);
    painter.drawRect(-50, -50, 100, 100);

    // 平移变换
    painter.setBrush(Qt::yellow);
    painter.drawRect(0, 100, 50, 50);
    //将点（100，100）设为原点
    painter.translate(100, 200);
    painter.setBrush(Qt::red);
    painter.drawRect(0, 0, 50, 50);
    painter.translate(-100, -100);
    painter.drawLine(0, 0, 20, 20);

    // 缩放
    painter.translate(0, 150);
    painter.setBrush(Qt::yellow);
    painter.drawRect(0, 0, 100, 100);
    painter.scale(2, 2); //坐标系放大两倍，与translate一样会对后面有影响
    painter.setBrush(Qt::red);
    painter.drawRect(50, 50, 50, 50);

    // 扭曲
    painter.translate(0, 100);
    painter.setBrush(Qt::yellow);
    painter.drawRect(0, 0, 25, 25);
    painter.shear(0, 1); //对纵向扭曲值为1，那么就是红色正方形左边的边下移一个单位，右边的边下移两个单位，值为1就表明右边的边比左边的边多下移一个单位
    painter.setBrush(Qt::red);
    painter.drawRect(25, 0, 25, 25);

    // 旋转
    painter.scale(0.5, 0.5);
    painter.shear(0, -1);
    painter.translate(200, -450);
    painter.drawLine(0, 0, 100, 0);
    painter.drawLine(0, 0, 0, 100);
    //以原点为中心，坐标系顺时针旋转30度
    painter.rotate(30);
    painter.drawLine(0, 0, 100, 0);
    painter.translate(100, 100);//坐标系已经旋转30度的基础上，平移
    painter.drawLine(0, 0, 100, 0);
    painter.drawLine(0, 0, 0, 100);
    painter.rotate(30);
    painter.drawLine(0, 0, 100, 0);
    painter.drawRect(25, 0, 25, 25);
    // 反向旋转
    painter.rotate(-60);
    painter.translate(100, 100);
    painter.drawLine(0, 0, 100, 0);
    painter.drawLine(0, 0, 0, 100);
    painter.rotate(30);
    painter.drawLine(0, 0, 100, 0);

    //前面讲到的这几个变换函数都是如此，他们改变了坐标系统以后，如果不进行逆向操作，坐标系统是无法自动复原的
    //针对这个问题，下面两个非常实用的函数来实现坐标系统的保存和还原
    painter.rotate(-30);
    painter.translate(-100, 100);
    painter.save(); //保存坐标系状态
    painter.translate(100,100);
    painter.setPen(Qt::yellow);
    painter.drawLine(0, 0, 50, 50);
    painter.restore(); //恢复以前的坐标系状态
    painter.setPen(Qt::red);
    painter.drawLine(0, 0, 50, 50);

    //画布
    painter.translate(200, -330);
    QPixmap pix1(200, 200);
    pix1.fill(Qt::yellow);   //背景填充为红色
    painter.drawPixmap(0, 0, pix1);

    QPixmap pix2(200, 200);
    pix2.fill(Qt::green);   //背景填充为红色
    painter.drawPixmap(100, 100, pix2);

    QPixmap pix3(200, 200);
    pix3.fill(Qt::red);
    //新建QPainter类对象，在pix上进行绘图
    //前面的代码QPainter painter(this) ，this就表明了是在本窗口实例上进行绘图，所以利用painter进行的绘图都是在窗口部件上的
    //painter进行的坐标变换，是变化的窗口的坐标系
    //而利用pp进行的绘图都是在画布上进行的，如果它进行坐标变换，就是变换的画布的坐标系。
    QPainter pp1(&pix3);
    //在pix上的（0，0）点和（50，50）点之间绘制直线
    pp1.drawLine(0, 0, 50, 50);
    painter.drawPixmap(0, 300, pix3);

    painter.translate(300,0);
    QPixmap pix4(200,200);
    //放大前输出画布的大小
    qDebug() << pix4.size();
    pix4.fill(Qt::red);
    QPainter pp2(&pix4);
    //画布的坐标扩大2倍
    pp2.scale(2, 2);
    //在画布上的（0，0）点和（50，50）点之间绘制直线
    pp2.drawLine(0, 0, 50, 50);
    //放大后输出画布的大小
    qDebug() << pix4.size();
    painter.drawPixmap(0, 0, pix4);

    QPixmap pix5(200,200);
    qDebug() << pix5.size();
    //窗口坐标扩大2倍
    painter.scale(2,2);
    pix5.fill(Qt::yellow);
    QPainter pp3(&pix5);
    pp3.drawLine(0, 0, 50, 50);
    qDebug() << pix5.size();
    painter.drawPixmap(0, 100, pix5);

}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->pos();
}
