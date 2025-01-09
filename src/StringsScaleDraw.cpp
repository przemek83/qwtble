#include "StringsScaleDraw.h"

#include <cmath>

#include <qwt_text.h>

#include <qwtble/QwtBleUtilities.h>

StringsScaleDraw::StringsScaleDraw(QVector<QString> intervalNames)
    : intervalNames_(std::move(intervalNames))
{
    setLabelRotation(qwt_ble_utilities::DEFAULT_LABEL_ROTATION);
    setLabelAlignment(Qt::AlignLeft | Qt::AlignBottom);
}

QwtText StringsScaleDraw::label(double value) const
{
    const QwtText emptyLabel{QStringLiteral("                     ")};
    if (const bool valueIsIntegral{
            qwt_ble_utilities::doublesAreEqual(fmod(value, 1), 0.)};
        (!valueIsIntegral) || intervalNames_.isEmpty())
        return emptyLabel;

    if (const int valueAsIntegral{static_cast<int>(value)};
        (valueAsIntegral > 0) && (valueAsIntegral <= intervalNames_.count()))
        return {intervalNames_.at(valueAsIntegral - 1)};

    return emptyLabel;
}
