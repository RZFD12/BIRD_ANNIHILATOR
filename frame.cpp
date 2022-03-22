#include "frame.h"
FRAME::FRAME(QObject *parent)
{

}

FRAME::~FRAME()
{

}

QRectF FRAME::boundingRect() const
{
    return QRectF (0,0,55,55);
}
void FRAME::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QColor(155,44,200));
    painter->drawRoundedRect(0,0,55,55,10,10);
    painter->drawText(20,20,"10");

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
void FRAME::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{


    this->setPos(mapToScene(event->pos()));
    Q_UNUSED(event);

}
void FRAME::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if (event->button() & Qt::RightButton)
    {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        Q_UNUSED(event);
        this->deleteLater();
    }
}

void FRAME::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
