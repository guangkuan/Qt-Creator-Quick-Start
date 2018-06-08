#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "assistant.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAction *help = new QAction("help",this);
    ui->mainToolBar->addAction(help);
    connect(help, SIGNAL(triggered()), this, SLOT(startAssistant()));
    // 创建Assistant对象
    assistant = new Assistant;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete assistant;
}

void MainWindow::startAssistant()
{
   // 按下“help”按钮，运行Qt Assistant，显示index.html页面
   assistant->showDocumentation("index.html");
}
