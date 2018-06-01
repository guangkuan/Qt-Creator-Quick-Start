#include "myview.h"
#include <QGLWidget>

MyView::MyView(QWidget *parent) : QGraphicsView(parent)
{
    resize(400, 400);
    setBackgroundBrush(QPixmap("../graphicsview03/back.jpg"));

    QGraphicsScene *scene = new QGraphicsScene(this);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setDragMode(QGraphicsView::ScrollHandDrag); //手型拖动
    //图形项可以放到场景的任何位置，场景的大小默认是没有限制的
    //而场景的边界矩形仅用于场景内部进行索引的维护。因为如果没有边界矩形，场景就要搜索所有的图形项，然后确定出其边界，这是十分费时的
    //所以如果要操作一个较大的场景，我们应该给出它的边界矩形。设置边界矩形，可以使用setSceneRect()函数

    scene->setSceneRect(0, 0, 800, 800);

    QGraphicsRectItem *item1 = new QGraphicsRectItem(0, 0, 20, 20);
    item1->setBrush(Qt::red);
    item1->setPos(10,0);
    scene->addItem(item1);

    QGraphicsRectItem *item2 = new QGraphicsRectItem(0,0,20,20);
    item2->setBrush(Qt::green);
    item2->setPos(40,0);
    scene->addItem(item2);

    //新建图形项组
    //图形项组也是一个图形项，它有图形项所拥有的所有特性
    //其作用就是，将加入它的所有图形项作为一个整体，对这个图形项组进行操作，就相当于对齐中所有图形项进行操作
    QGraphicsItemGroup *group = new QGraphicsItemGroup;
    group->addToGroup(item1);
    group->addToGroup(item2);
    scene->addItem(group);
    setScene(scene);

    QGLWidget *widget =new QGLWidget(this);
    setViewport(widget);

    //输出(10, 0)点的图形项
    qDebug() << "itemAt(10,0) : " <<itemAt(10, 0);
    qDebug() << "itemAt(40,0) : " <<itemAt(40, 0);
    qDebug() << "#################################";

}

//滚轮事件
void MyView::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
        scale(0.5, 0.5);  //视图缩放
    else scale(2, 2);
}

void MyView::mousePressEvent(QMouseEvent *event)
{
    rotate(90);  //视图旋转顺时针90度
    QPixmap pixmap(400, 400);  //必须指定大小
    QPainter painter(&pixmap);
//    render(&painter,QRectF(0, 0, 400, 400), QRect(0, 0, 400, 400));  //打印视图指定区域内容
    scene()->render(&painter,QRectF(0,0,400,400), QRect(0,0,400,400)); //打印场景内容
    pixmap.save("../graphicsview03/save.png");
    //在图形视图框架中，鼠标键盘等事件是从视图进入的，视图将它们传递给场景，场景再将事件传递给该点的图形项
    //如果该点有多个图形项，那么就传给最上面的图形项
    QGraphicsView::mousePressEvent(event);
}

void MyView::keyPressEvent(QKeyEvent *event)
{
    //输出场景中所有的图形项
    qDebug() << items();
//    items().at(0)->setPos(100,0);
//    items().at(1)->setPos(0,100);
    items().at(2)->setPos(100,100);
    //执行默认的事件处理
    QGraphicsView::keyPressEvent(event);
}
