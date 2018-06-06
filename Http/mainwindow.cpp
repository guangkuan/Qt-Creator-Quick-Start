#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    //用QNetworkRequest 类来管理请求
    manager->get(QNetworkRequest(QUrl("http://www.qter.org")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//QNetworkReply类进行接收回复，并对数据进行处理
void MainWindow::replyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString all = codec->toUnicode(reply->readAll());
    //reply->readAll()函数就可以将下载的所有数据读出
    ui->textBrowser->setText(all);
    reply->deleteLater();
}
