#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsItem>

class Rectangle : public QGraphicsItem
{
public:
    Rectangle();
    ~Rectangle();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // RECTANGLE_H
