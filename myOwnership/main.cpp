#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //对于规范的Qt程序，我们要在main()函数中将主窗口部件创建在栈上，例如“Widget w;”，而不要在堆上进行创建（使用new操作符）
    //对于其他窗口部件，可以使用new操作符在堆上进行创建，不过一定要指定其父部件，这样就不需要再使用delete操作符来销毁该对象了
    Widget w;
    w.show();

    return a.exec();
}
