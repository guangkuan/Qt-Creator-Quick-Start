#include <QtWidgets>
#include "myitem.h"

int main(int argc,char* argv[ ])
{
    QApplication app(argc,argv);

    //设置随机数初值
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    // 场景
    QGraphicsScene *scene = new QGraphicsScene;
    for(int i = 0; i < 5; i++) //在不同位置新建5个圆形
    {
        // 矩形项
        MyItem *item = new MyItem;
        item->setPos(i * 50 + 20, 100);
        scene->addItem(item);
    }
    RectItem *rect = new RectItem; //新建矩形
    rect->setPos(100, 200);
    // 项添加到场景
    scene->addItem(rect);
    // 视图
    QGraphicsView *view = new QGraphicsView;
    // 视图关联场景
    view->setScene(scene);
    view->resize(400, 300); //设置视图大小
    view->show();

    return app.exec();
}
