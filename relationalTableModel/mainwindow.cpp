#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlRelationalDelegate>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QSqlRelationalTableModel(this);
    //字段变化时写入数据库
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setTable("student");
    //将student表的第三个字段设为course表的id字段的外键，
    //并将其显示为course表的name字段的值
    model->setRelation(2,QSqlRelation("course","id","name"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Course"));
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
}

MainWindow::~MainWindow()
{
    delete ui;
}
