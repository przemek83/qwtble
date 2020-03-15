#include "StringsScaleDraw.h"

#include <cmath>

#include "QwtBleUtilities.h"

StringsScaleDraw::StringsScaleDraw(QVector<QString>* intervals) :
    intervals_(intervals)
{
    setLabelRotation(QwtBleUtilities::DEFAULT_LABEL_ROTATION);
    setLabelAlignment(Qt::AlignLeft | Qt::AlignBottom);
}

QwtText StringsScaleDraw::label(double v) const
{
    if (intervals_->isEmpty() || !QwtBleUtilities::doublesAreEqual(fmod(v, 1), 0.) ||
        QwtBleUtilities::doublesAreEqual(v, 0.) || v < 0 || v > intervals_->count())
    {
        return QwtText(QStringLiteral("                     "));
    }

    int point = static_cast<int>(v);
    if (intervals_->count() >= point)
    {
        return QwtText(intervals_->at(point - 1));
    }

    return QwtText(QStringLiteral("                     "));
}
