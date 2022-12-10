#pragma once

#include "Picker.h"

class XYAxisNumberPicker : public Picker
{
    Q_OBJECT
public:
    explicit XYAxisNumberPicker(QWidget* parent);

protected:
    [[nodiscard]] QwtText trackerTextF(const QPointF& pos) const override;
};
