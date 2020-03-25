#include "StringsScaleDraw.h"

#include <cmath>

#include "QwtBleUtilities.h"

StringsScaleDraw::StringsScaleDraw(QVector<QString> intervalNames) :
    intervalNames_(std::move(intervalNames))
{
    setLabelRotation(QwtBleUtilities::DEFAULT_LABEL_ROTATION);
    setLabelAlignment(Qt::AlignLeft | Qt::AlignBottom);
}

QwtText StringsScaleDraw::label(double v) const
{
    if (intervalNames_.isEmpty() || !QwtBleUtilities::doublesAreEqual(fmod(v, 1), 0.) ||
        QwtBleUtilities::doublesAreEqual(v, 0.) || v < 0 || v > intervalNames_.count())
        return QwtText(QStringLiteral("                     "));

    const int point = static_cast<int>(v);
    if (intervalNames_.count() >= point)
        return QwtText(intervalNames_.at(point - 1));

    return QwtText(QStringLiteral("                     "));
}
