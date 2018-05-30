#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // 窗口大小设置为600*500
    resize(600, 500);
    // 画布大小为200*200，背景为白色
    pix = QPixmap(200, 200);
    pix.fill(Qt::white);

    //设置初始放大倍数为1，即不放大
    scale =1;
    //新建按钮对象
    button = new QPushButton(this);
    //设置按钮显示文本
    button->setText(tr("放大"));
    //设置按钮放置位置
    button->move(500, 450);
    //对按钮的单击事件和其槽函数进行关联
    connect(button, &QPushButton::clicked, this, &Dialog::zoomIn);
}

Dialog::~Dialog()
{
    delete ui;
}

//这种用改变窗口坐标大小来改变画布面积的方法，实际上是有损图片质量的
//就像将一张位图放大一样，越放大越不清晰
//原因就是，它的像素的个数没有变，如果将可视面积放大，那么单位面积里的像素个数就变少了，所以画质就差了
//void Dialog::paintEvent(QPaintEvent *)
//{
//    QPainter pp(&pix);
//    // 根据鼠标指针前后两个位置绘制直线
//    pp.drawLine(lastPoint/scale, endPoint/scale);
//    // 让前一个坐标值等于后一个坐标值，
//    // 这样就能实现画出连续的线
//    lastPoint = endPoint;
//    QPainter painter(this);
//    //进行放大操作
//    painter.scale(scale, scale);
//    painter.drawPixmap(0, 0, pix);
//}

//能放大曲线不能放大画布
//void Dialog::paintEvent(QPaintEvent *)
//{
//    QPainter pp(&pix);
//    pp.scale(scale, scale);
//    pp.drawLine(lastPoint,endPoint);
//    lastPoint = endPoint;
//    QPainter painter(this);
//    painter.drawPixmap(0, 0, pix);
//}

void Dialog::paintEvent(QPaintEvent *)
{
    if(scale != 1) //如果进行放大操作
    {
       //临时画布，大小变化了scale倍
       QPixmap copyPix(pix.size() * scale);
       copyPix.fill(Qt::white);
       QPainter pter(&copyPix);
       //将以前画布上的内容复制到现在的画布上
       QPoint p(0, 0);
       QRect rectangle(p, (pix.size() * scale));
       pter.drawPixmap(rectangle, pix);
       //将放大后的内容再复制回原来的画布上
       pix = copyPix;
       //让scale重新置1
       scale =1;
    }
    QPainter pp(&pix);
    pp.scale(scale, scale);
    pp.drawLine(lastPoint/scale, endPoint/scale);
    lastPoint = endPoint;
    QPainter painter(this);
    painter.drawPixmap(0, 0, pix);
}

void Dialog::mousePressEvent(QMouseEvent *event){
        //鼠标左键按下
        if(event->button() == Qt::LeftButton)
                    lastPoint = event->pos();
         endPoint = lastPoint;
}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    // 鼠标左键按下的同时移动鼠标
    if(event->buttons() & Qt::LeftButton)
    {
       endPoint = event->pos();
       update();//进行绘制
    }
}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
        if(event->button() == Qt::LeftButton) //鼠标左键释放
        {
                  endPoint = event->pos();
                  update();
        }
}

void Dialog::zoomIn()
{
    scale *= 1.5;
    update();
}
