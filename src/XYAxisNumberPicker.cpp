#include "XYAxisNumberPicker.h"

XYAxisNumberPicker::XYAxisNumberPicker(QWidget* parent)
    : Picker(parent)
{

}

QwtText XYAxisNumberPicker::trackerTextF(const QPointF& pos)const
{
    QwtText coords(QString::number(pos.x(), 'f', 0) +
                   ", " + QString::number(pos.y(), 'f', 0));
    const QColor bg(Qt::white);
    coords.setBackgroundBrush(QBrush(bg));
    return coords;
}
