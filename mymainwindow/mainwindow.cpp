#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //创建新的动作
    QAction *openAction = new QAction(tr("&Open"), this);
    //添加图标
    QIcon icon(":/myimages/images/fileopen.png");
    openAction->setIcon(icon);
    //设置快捷键
    openAction->setShortcut(QKeySequence(tr("ctrl+O")));
    //在文件菜单中设置新的打开动作
    ui->menu->addAction(openAction);

    //创建新的菜单
    QMenu *menu_E = ui->menuBar->addMenu(tr("编辑(&E)"));
    QAction *findAction = new QAction(tr("&Find"), this);
    QIcon icon2(":/myimages/images/find.png");
    findAction->setIcon(icon2);
    findAction->setShortcut(QKeySequence(tr("ctrl+F")));
    menu_E->addAction(findAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}
