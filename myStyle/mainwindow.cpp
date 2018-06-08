#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //The Style Sheet Syntax中介绍了Qt样式表的语法，就是一些使用规则
    //Qt Designer Integration中介绍了如何在设计器中使用Qt样式表
    //Customizing Qt Widgets Using Style Sheets中介绍了如何使用Qt样式表来定制部件样式
    //QtStyle Sheets Reference中罗列了Qt中所有可以使用样式表的部件
    //QtStyle Sheets Examples中列出了常用部件使用样式表的例子
    setStyleSheet("QPushButton { color: white }");
    //一个部件只能单独设置一个样式表，我们在代码中为pushButton设置了样式表就会屏蔽设计器中设置的
    ui->pushButton->setStyleSheet("background-color: red; color: blue");
}

MainWindow::~MainWindow()
{
    delete ui;
}
