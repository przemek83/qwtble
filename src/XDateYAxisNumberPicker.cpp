#include "XDateYAxisNumberPicker.h"

#include <cmath>

#include "QwtBleUtilities.h"

XDateYAxisNumberPicker::XDateYAxisNumberPicker(QWidget* parent)
    : Picker(parent)
{

}

QwtText XDateYAxisNumberPicker::trackerTextF(const QPointF& pos) const
{
    const QString dateOnY {QwtBleUtilities::stringFromDays(lround(pos.x()))};
    const QString valueOnX {QString::number(pos.y(), 'f', 2)};
    QwtText positionAsText(dateOnY + ", " + valueOnX);
    positionAsText.setBackgroundBrush(QBrush(Qt::white));
    return positionAsText;
}
