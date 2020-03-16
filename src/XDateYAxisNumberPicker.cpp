#include "XDateYAxisNumberPicker.h"

#include <cmath>

#include "QwtBleUtilities.h"

XDateYAxisNumberPicker::XDateYAxisNumberPicker(QWidget* parent)
    : Picker(parent)
{

}

QwtText XDateYAxisNumberPicker::trackerTextF(const QPointF& pos) const
{
    QwtText coords(QwtBleUtilities::stringFromDays(lround(pos.x())) + ", " +
                   QString::number(pos.y(), 'f', 2));

    const QColor bg(Qt::white);
    coords.setBackgroundBrush(QBrush(bg));
    return coords;
}
