#include "widget.h"
#include "ui_widget.h"
#include "mybutton.h"
#include <QDebug>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    MyButton *button = new MyButton(this);    // 创建按钮部件，指定widget为父部件
    button->setText(tr("myButton"));
    MyButton *myButton2 = new MyButton;
    MyButton *myButton3 = new MyButton;
    //当使用布局管理器来管理这两个按钮，并且在窗口中使用这个布局管理器后
    //这两个按钮和水平布局管理器都将重定义父部件而成为窗口Widget的子部件
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(myButton2);
    layout->addWidget(myButton3);
    setLayout(layout);      // 在该窗口中使用布局管理器

    qDebug() << "后加入的子组件：" << children();    // 输出所有子部件的列表
}

Widget::~Widget()
{
    delete ui;
    qDebug() << "delete widget";
}
