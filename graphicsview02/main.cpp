#include <QtWidgets>
#include "myitem.h"


int main(int argc,char* argv[ ])
{
    QApplication app(argc,argv);

    // 场景
    QGraphicsScene *scene = new QGraphicsScene;
    // 矩形项
    MyItem *item = new MyItem;
    // 项添加到场景
    scene->addItem(item);
    QGraphicsLineItem *line = new QGraphicsLineItem(0, 50, 300, 50);
    scene->addItem(line);

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer.start(1000);
    // 视图
    QGraphicsView *view = new QGraphicsView;
    // 视图关联场景
    view->setScene(scene);
    // 显示视图
    view->show();

    qDebug() << item->shape();   //输出item的shape信息
    qDebug() << item->boundingRect();  //输出item的boundingRect信息

    return app.exec();
}
