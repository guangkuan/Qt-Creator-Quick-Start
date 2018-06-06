#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ftp = new QFtp(this);
    ftp->connectToHost("ftp.iap.ac.cn"); //连接到服务器
    ftp->login();   //登录
    ftp->cd("/ftp/");   //跳转目录
    ftp->get("dir.txt");  //下载“dir.txt”文件
    ftp->close();   //关闭连接

    // 当每条命令开始执行时发出相应的信号
    connect(ftp, SIGNAL(commandStarted(int)), this, SLOT(ftpCommandStarted(int)));
    // 当每条命令执行结束时发出相应的信号
    connect(ftp, SIGNAL(commandFinished(int,bool)), this, SLOT(ftpCommandFinished(int, bool)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::ftpCommandStarted(int)
{
    if(ftp->currentCommand() == QFtp::ConnectToHost)
    {
       ui->label->setText(tr("正在连接到服务器..."));
    }
    if (ftp->currentCommand() == QFtp::Login)
    {
       ui->label->setText(tr("正在登录..."));
    }
    if (ftp->currentCommand() == QFtp::Get){
       ui->label->setText(tr("正在下载..."));
    }
    else if (ftp->currentCommand() == QFtp::Close)
    {
       ui->label->setText(tr("正在关闭连接..."));
    }
}

void Widget::ftpCommandFinished(int,bool error)
{
    if(ftp->currentCommand() == QFtp::ConnectToHost)
    {
       if(error)
           ui->label->setText(tr("连接服务器出现错误：%1").arg(ftp->errorString()));
       else
           ui->label->setText(tr("连接到服务器成功"));
    }
    if (ftp->currentCommand() == QFtp::Login)
    {
       if(error)
           ui->label->setText(tr("登录出现错误：%1").arg(ftp->errorString()));
       else
           ui->label->setText(tr("登录成功"));
    }
    if (ftp->currentCommand() == QFtp::Get)
    {
       if(error)
           ui->label->setText(tr("下载出现错误：%1").arg(ftp->errorString()));
       else
       {
           ui->label->setText(tr("已经完成下载"));
           ui->textBrowser->setText(ftp->readAll());
       }
    }
    else if (ftp->currentCommand() == QFtp::Close)
    {
       ui->label->setText(tr("已经关闭连接"));
    }
}
