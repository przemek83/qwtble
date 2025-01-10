#pragma once

#include <qwt_scale_draw.h>

/// @brief Scale drawing used in grouping plot. Rotates labels.
class StringsScaleDraw : public QwtScaleDraw
{
public:
    explicit StringsScaleDraw(QVector<QString> intervalNames);

    QwtText label(double value) const override;

private:
    const QVector<QString> intervalNames_;
};
