#include "YAxisNumberPicker.h"

YAxisNumberPicker::YAxisNumberPicker(QWidget* parent)
    : Picker(parent)
{

}

QwtText YAxisNumberPicker::trackerTextF(const QPointF& pos) const
{
    QwtText coords(QString::number(pos.y(), 'f', 2));
    const QColor bg(Qt::white);
    coords.setBackgroundBrush(QBrush(bg));
    return coords;
}
