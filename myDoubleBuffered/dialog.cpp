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
    pix = QPixmap(600, 500);
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

    isDrawing = false;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int x,y,w,h;
    x = lastPoint.x();
    y = lastPoint.y();
    w = endPoint.x() - x;
    h = endPoint.y() - y;
    if(isDrawing) //如果正在绘图，就在辅助画布上绘制
    {
       //将以前pix中的内容复制到tempPix中，保证以前的内容不消失
       tempPix = pix;
       QPainter pp(&tempPix);
       pp.drawRect(x, y, w, h);
       painter.drawPixmap(0, 0, tempPix);
    }
    else
    {
       QPainter pp(&pix);
       pp.drawRect(x, y, w, h);
       painter.drawPixmap(0, 0, pix);
    }
}

void Dialog::mousePressEvent(QMouseEvent *event){
        //鼠标左键按下
        if(event->button() == Qt::LeftButton)
        {
            lastPoint = event->pos();
            isDrawing = true;   //正在绘图
        }
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
                  isDrawing = false;    //结束绘图
                  update();
        }
}

void Dialog::zoomIn()
{
    scale *= 1.5;
    update();
}
