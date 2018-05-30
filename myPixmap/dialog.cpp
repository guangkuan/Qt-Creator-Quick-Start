#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>

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
    QPixmap pix;
    pix.load("../mypixmap/logo.png");
    painter.drawPixmap(0, 0, 80, 100, pix);

    //移位
    painter.translate(100, 100);
    painter.drawPixmap(0, 0, 80, 100, pix);

    //获得以前图片的宽和高
    qreal width = pix.width();
    qreal height = pix.height();
    //将图片的宽和高都缩小，并且在给定的矩形内保持宽高的比值不变
    pix = pix.scaled(width*0.2, height*0.2, Qt::KeepAspectRatio);
    painter.drawPixmap(90, 90, pix);

    //让图片的中心作为旋转的中心
    painter.translate(40, 50);
    painter.rotate(90); //顺时针旋转90度
    painter.translate(-40,-50); //使原点复原
    painter.drawPixmap(100, 100, 80, 100, pix);

    painter.shear(0.5, 0); //横向扭曲
    painter.drawPixmap(100, 0, 80, 100, pix);//旋转了坐标系统以后再绘制图片都是纵向的，这就是因为旋转了坐标系统而没有进行恢复造成的
}
