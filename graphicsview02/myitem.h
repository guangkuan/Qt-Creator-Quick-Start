#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsItem>

class MyItem : public QGraphicsItem
{
public:
    MyItem();
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MYITEM_H
