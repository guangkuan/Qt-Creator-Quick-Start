#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    ~MyDialog();

signals:
    //因为只有QObject类及其子类派生的类才能使用信号和槽机制
    //这里的MyDialog类继承自QDialog类，QDialog类又继承自QWidget类，QWidget类是QObject类的子类，所以这里可以使用信号和槽
    void dlgReturn(int);  // 自定义的信号

private slots:
    void on_pushButton_clicked();

private:
    Ui::MyDialog *ui;
};

#endif // MYDIALOG_H
