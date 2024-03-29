#include "YAxisNumberPicker.h"

#include <qwt_text.h>
#include <QBrush>

YAxisNumberPicker::YAxisNumberPicker(QWidget* parent) : Picker(parent) {}

QwtText YAxisNumberPicker::trackerTextF(const QPointF& pos) const
{
    QwtText positionAsText(QString::number(pos.y(), 'f', 2));
    positionAsText.setBackgroundBrush(QBrush(Qt::white));
    return positionAsText;
}
