#include "StringsScaleDraw.h"

#include <cmath>

#include "Utilities.h"

StringsScaleDraw::StringsScaleDraw(QVector<QString>* intervals) :
    intervals_(intervals)
{
    setLabelRotation(Utilities::DEFAULT_LABEL_ROTATION);
    setLabelAlignment(Qt::AlignLeft | Qt::AlignBottom);
}

QwtText StringsScaleDraw::label(double v) const
{
    if (intervals_->isEmpty() || !Utilities::doublesAreEqual(fmod(v, 1), 0.) ||
        Utilities::doublesAreEqual(v, 0.) || v < 0 || v > intervals_->count())
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
