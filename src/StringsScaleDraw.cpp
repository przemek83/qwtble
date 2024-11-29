#include "StringsScaleDraw.h"

#include <cmath>

#include <qwt_text.h>

#include <qwtble/QwtBleUtilities.h>

StringsScaleDraw::StringsScaleDraw(QVector<QString> intervalNames)
    : intervalNames_(std::move(intervalNames))
{
    setLabelRotation(QwtBleUtilities::DEFAULT_LABEL_ROTATION);
    setLabelAlignment(Qt::AlignLeft | Qt::AlignBottom);
}

QwtText StringsScaleDraw::label(double value) const
{
    using QwtBleUtilities::doublesAreEqual;
    const bool valueIsIntegral{doublesAreEqual(fmod(value, 1), 0.)};
    const int valueAsIntegral = static_cast<int>(value);
    if (valueIsIntegral && !intervalNames_.isEmpty() && valueAsIntegral > 0 &&
        valueAsIntegral <= intervalNames_.count())
        return {intervalNames_.at(valueAsIntegral - 1)};

    return {QStringLiteral("                     ")};
}
