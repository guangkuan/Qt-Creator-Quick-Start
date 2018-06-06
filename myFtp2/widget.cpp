#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->progressBar->setValue(0);
    //鼠标双击列表中的目录时，我们进入该目录
    connect(ui->fileList, SIGNAL(itemActivated(QTreeWidgetItem*,int)), this, SLOT(processItem(QTreeWidgetItem*,int)));
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

    if (ftp->currentCommand() == QFtp::Get)
    {
       ui->label->setText(tr("正在下载..."));
    }
    else if (ftp->currentCommand() == QFtp::Close)
    {
       ui->label->setText(tr("正在关闭连接..."));
    }
}

void Widget::ftpCommandFinished(int, bool error)
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
       {
           ui->label->setText(tr("登录成功"));
           ftp->list();   //发射listInfo()信号，显示文件列表
       }
    }
    if (ftp->currentCommand() == QFtp::List)
    {
       if (isDirectory.isEmpty())
       { //如果目录为空,显示“empty”
           ui->fileList->addTopLevelItem(new QTreeWidgetItem(QStringList()<< tr("<empty>")));
           ui->fileList->setEnabled(false);
           ui->label->setText(tr("该目录为空"));
       }
    }
    if (ftp->currentCommand() == QFtp::Get)
    {
       if(error)
           ui->label->setText(tr("下载出现错误：%1").arg(ftp->errorString()));
       else
       {
           ui->label->setText(tr("已经完成下载"));
           ui->downloadButton->setEnabled(true);
           file->close();
           delete file;
       }
    }
    else if (ftp->currentCommand() == QFtp::Close){
       ui->label->setText(tr("已经关闭连接"));
    }
}


void Widget::on_connectButton_clicked()   //连接按钮
{
    ui->fileList->clear();
    currentPath.clear();
    isDirectory.clear();
    qDebug() << "连接";

    ftp = new QFtp(this);
    connect(ftp, SIGNAL(commandStarted(int)), this, SLOT(ftpCommandStarted(int)));
    connect(ftp, SIGNAL(commandFinished(int,bool)), this, SLOT(ftpCommandFinished(int, bool)));
    connect(ftp, SIGNAL(listInfo(QUrlInfo)), this, SLOT(addToList(QUrlInfo)));
    connect(ftp, SIGNAL(dataTransferProgress(qint64, qint64)), this, SLOT(updateDataTransferProgress(qint64, qint64)));

    QString ftpServer = ui->ftpServerLineEdit->text();
    QString userName = ui->userNameLineEdit->text();
    QString passWord = ui->passWordLineEdit->text();
    ftp->connectToHost(ftpServer, 21); //连接到服务器,默认端口号是21
    ftp->login(userName,passWord);   //登录
}

void Widget::addToList(const QUrlInfo &urlInfo)  //添加文件列表
{
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, urlInfo.name());
    item->setText(1, QString::number(urlInfo.size()));
    item->setText(2, urlInfo.owner());
    item->setText(3, urlInfo.group());
    item->setText(4, urlInfo.lastModified().toString("MMM dd yyyy"));

    QPixmap pixmap(urlInfo.isDir() ? "../myFtp2/dir.png" : "../myFtp2/file.png");
    item->setIcon(0, pixmap);

    isDirectory[urlInfo.name()] = urlInfo.isDir();
    //存储该路径是否为目录的信息
    ui->fileList->addTopLevelItem(item);
    if (!ui->fileList->currentItem()) {
       ui->fileList->setCurrentItem(ui->fileList->topLevelItem(0));
       ui->fileList->setEnabled(true);
    }
}

void Widget::processItem(QTreeWidgetItem* item,int)  //打开一个目录
{
    QString name = item->text(0);
    if (isDirectory.value(name))
    {  //如果这个文件是个目录，则打开
       ui->fileList->clear();
       isDirectory.clear();
       currentPath += '/';
       currentPath += name;
       ftp->cd(name);
       ftp->list();
       ui->cdToParentButton->setEnabled(true);
    }
}

void Widget::on_cdToParentButton_clicked()  //返回上级目录按钮
{
    ui->fileList->clear();
    isDirectory.clear();
    currentPath = currentPath.left(currentPath.lastIndexOf('/'));
    if (currentPath.isEmpty())
    {
       ui->cdToParentButton->setEnabled(false);
       ftp->cd("/");
    }
    else
    {
       ftp->cd(currentPath);
    }
    ftp->list();
}

void Widget::on_downloadButton_clicked()  //下载按钮
{
    QString fileName = ui->fileList->currentItem()->text(0);
    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly))
    {
       delete file;
       return;
    }
//下载按钮不可用，等下载完成后才可用
    ui->downloadButton->setEnabled(false);
    ftp->get(ui->fileList->currentItem()->text(0), file);
}

//进度条
void Widget::updateDataTransferProgress(qint64 readBytes,qint64 totalBytes)
{
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(readBytes);
}
