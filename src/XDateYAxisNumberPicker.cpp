#include "XDateYAxisNumberPicker.h"

#include <cmath>

#include <qwt_text.h>
#include <QBrush>

#include <qwtble/QwtBleUtilities.h>

XDateYAxisNumberPicker::XDateYAxisNumberPicker(QWidget* parent) : Picker(parent)
{
}

QwtText XDateYAxisNumberPicker::trackerTextF(const QPointF& pos) const
{
    const QString dateOnY{
        qwt_ble_utilities::stringFromDays(static_cast<int>(::lround(pos.x())))};
    const QString valueOnX{QString::number(pos.y(), 'f', 2)};
    QwtText positionAsText(dateOnY + ", " + valueOnX);
    positionAsText.setBackgroundBrush(QBrush(Qt::white));
    return positionAsText;
}
