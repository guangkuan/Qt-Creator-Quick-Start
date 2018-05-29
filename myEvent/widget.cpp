#include "widget.h"
#include "ui_widget.h"
#include <QMouseEvent>
#include <QKeyEvent>

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

void Widget::mousePressEvent(QMouseEvent *e)
{
    //这里arg()里的参数分别用来填充%1和%2处的内容
   ui->pushButton->setText(tr("(%1, %2)").arg(e->x()).arg(e->y()));
}

void Widget::keyPressEvent(QKeyEvent *e)
{
   int x = ui->pushButton->x();
   int y = ui->pushButton->y();
   switch (e->key())
   {
   case Qt::Key_W : ui->pushButton->move(x, y-10); break;
   case Qt::Key_S : ui->pushButton->move(x, y+10); break;
   case Qt::Key_A : ui->pushButton->move(x-10, y); break;
   case Qt::Key_D : ui->pushButton->move(x+10, y); break;
   }
}
