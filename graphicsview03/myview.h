#ifndef MYVIEW_H
#define MYVIEW_H

#include <QtWidgets>

class MyView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MyView(QWidget *parent = 0);

protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // MYVIEW_H
