#ifndef MYITEM_H
#define MYITEM_H
#include <QGraphicsItem>

class MyItem : public QGraphicsItem
{
public:
    MyItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QColor color;
};

class RectItem : public QGraphicsItem
{
public:
    RectItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
     void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
     void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
     void dropEvent(QGraphicsSceneDragDropEvent *event);

private:
     QColor color;
     bool dragOver;  //标志是否有拖动进入
};

#endif // MYITEM_H
