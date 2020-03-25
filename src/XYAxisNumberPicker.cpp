#include "XYAxisNumberPicker.h"

XYAxisNumberPicker::XYAxisNumberPicker(QWidget* parent)
    : Picker(parent)
{

}

QwtText XYAxisNumberPicker::trackerTextF(const QPointF& pos) const
{
    QwtText positionAsText(QString::number(pos.x(), 'f', 0) +
                           ", " + QString::number(pos.y(), 'f', 0));
    positionAsText.setBackgroundBrush(QBrush(Qt::white));
    return positionAsText;
}
