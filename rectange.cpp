#include <rectangle.h>

Rectangle::Rectangle() :
    QGraphicsItem() {}

Rectangle::~Rectangle() {}

QRectF Rectangle::boundingRect() const
{
    return QRectF(-25,-40,50,80); // limits the area of the rect
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon; // uses polygon class to paint rectangle
    /* puts points coordinates in the polygon madel */
    polygon << QPoint(-130,-185) << QPoint(-150,-185) << QPoint(-150,-175) << QPoint(-130,-175);
    painter->setBrush(Qt::red);    // sets brush
    painter->drawPolygon(polygon); // draws rectangle
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
