#include <QtWidgets>
#include "myview.h"

int main(int argc,char* argv[ ])

{
    QApplication app(argc,argv);

    MyView *view = new MyView;
    view->show();

    return app.exec();

}
