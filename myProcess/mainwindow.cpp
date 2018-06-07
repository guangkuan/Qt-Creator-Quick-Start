#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&myProcess, SIGNAL(readyRead()), this, SLOT(showResult()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
//    myProcess.start("notepad.exe");
    //cmd /c dir 是执行完dir命令后关闭命令窗口
    QString program = "cmd.exe";
    QStringList arguments;
    arguments << "/c dir&pause";
    myProcess.start(program, arguments);
}

void MainWindow::showResult()
{
    QString sResult = QString::fromLocal8Bit(myProcess.readAll());
    qDebug() << "showResult: " << endl;
    qDebug() << sResult.toStdString().data();
}
