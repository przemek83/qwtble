#include "LinearPicker.h"

#include <cmath>

#include "Utilities.h"

LinearPicker::LinearPicker(QWidget* parent)
    : Picker(parent)
{

}

QwtText LinearPicker::trackerTextF(const QPointF& pos) const
{
    QwtText coords(Utilities::stringFromDays(lround(pos.x())) + ", " +
                   QString::number(pos.y(), 'f', 2));

    QColor bg(Qt::white);
    coords.setBackgroundBrush(QBrush(bg));
    return coords;
}
