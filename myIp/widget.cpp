#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QString localHostName = QHostInfo::localHostName();
    qDebug() <<"localHostName: "<<localHostName;

    QHostInfo info = QHostInfo::fromName(localHostName);
    qDebug() <<"IP Address: "<<info.addresses();
    foreach(QHostAddress address,info.addresses())
    {
         if(address.protocol() == QAbstractSocket::IPv4Protocol)
            qDebug() << "IPv4 Address: " << address.toString();
    }

    //以主机名获取IP地址
    QHostInfo::lookupHost("www.qter.org", this, SLOT(lookedUp(QHostInfo)));

    //获取所有网络接口的列表
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface interface, list) //遍历每一个网络接口
    {
        qDebug() << "Device: " << interface.name(); //设备名
        //硬件地址
        qDebug() << "HardwareAddress: " << interface.hardwareAddress();

        //获取IP地址条目列表，每个条目中包含一个IP地址，
        //一个子网掩码和一个广播地址
        QList<QNetworkAddressEntry> entryList = interface.addressEntries();
        foreach(QNetworkAddressEntry entry, entryList)//遍历每个IP地址条目
        {
           qDebug()<<"IP Address: " << entry.ip().toString(); //IP地址
           qDebug()<<"Netmask: " << entry.netmask().toString(); //子网掩码
           qDebug()<<"Broadcast: " << entry.broadcast().toString();//广播地址
        }
    }

    //只想利用QNetworkInterface类来获取IP地址
    QString first_address = QNetworkInterface::allAddresses().first().toString();
    qDebug() << "first_IP Address: " << first_address;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::lookedUp(const QHostInfo &host)
{
    qDebug() << "Net Address: " << host.addresses().first().toString();
}
