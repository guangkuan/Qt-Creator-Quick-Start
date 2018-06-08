#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    QPushButton *button = new QPushButton(this); // 创建按钮
    button->setObjectName("myButton");           // 指定按钮的对象名
    //因为在setupUi()函数中调用了connectSlotsByName()函数，所以要使用自动关联的部件的定义都要放在setupUi()函数之前
    //而且还必须使用setObjectName()函数指定它们的objectName，只有这样才能正常使用自动关联
    ui->setupUi(this);                      //要在定义了部件以后再调用这个函数
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_myButton_clicked()          // 使用自动关联
{
   close();
}
