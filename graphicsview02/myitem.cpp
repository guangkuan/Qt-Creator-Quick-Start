#include "myitem.h"
#include <QPainter>
#include <QGraphicsItemAnimation>
#include <QTimeLine>

MyItem::MyItem()
{
    //图形项可获得焦点
    setFlag(QGraphicsItem::ItemIsFocusable);

    //新建动画类对象
    QGraphicsItemAnimation *anim = new QGraphicsItemAnimation;
    //将该图形项加入动画类对象中
    anim->setItem(this);
    //新建长为1秒的时间线
    QTimeLine *timeLine = new QTimeLine(1000);
    //动画循环次数为0，表示无限循环
    timeLine->setLoopCount(0);
    //将时间线加入动画类对象中
    anim->setTimeLine(timeLine);
    //在动画时间的一半时图形项旋转180度
    anim->setRotationAt(0.5,180);
    //在动画执行完时图形项旋转360度
    anim->setRotationAt(1,360);
    //开始动画
    timeLine->start();
}

QRectF MyItem::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(0 - penWidth / 2, 0 - penWidth / 2, 50 + penWidth, 50 + penWidth);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);  //标明该参数没有使用
    Q_UNUSED(widget);
    //如果与其他图形项碰撞则显示红色，否则显示绿色
    painter->setBrush(!collidingItems().isEmpty()? Qt::red : Qt::green);
    painter->drawRect(0, 0, 20, 20);
}

void MyItem::keyPressEvent(QKeyEvent *event)
{
    moveBy(0, 10);  //相对现在的位置移动
}

void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    moveBy(10, 0);
}

//默认shape和boundingRect的大小是一样的
QPainterPath MyItem::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 20, 20);  //图形项的真实大小
    return path;
}

void MyItem::advance(int phase)
{
    if(!phase) return;  //如果phase为0，则返回
    moveBy(10,10);
}
