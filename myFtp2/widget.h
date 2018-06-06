#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFtp>
#include <QtGui>
#include <QTreeWidgetItem>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_downloadButton_clicked();
    void on_cdToParentButton_clicked();
    void on_connectButton_clicked();
    void ftpCommandFinished(int,bool);
    void ftpCommandStarted(int);
    void updateDataTransferProgress(qint64,qint64 );//更新进度条
    //将服务器上的文件添加到Tree Widget中
    void addToList(const QUrlInfo &urlInfo);
    void processItem(QTreeWidgetItem*,int);//双击一个目录时显示其内容

private:
    Ui::Widget *ui;
    QFtp *ftp;
    QHash<QString, bool> isDirectory; //用来存储一个路径是否为目录的信息
    QString currentPath; //用来存储现在的路径
    QFile *file;
};

#endif // WIDGET_H
