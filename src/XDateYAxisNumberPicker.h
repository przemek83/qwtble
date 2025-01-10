#pragma once

#include "Picker.h"

class XDateYAxisNumberPicker : public Picker
{
    Q_OBJECT
public:
    explicit XDateYAxisNumberPicker(QWidget* parent);

protected:
    [[nodiscard]] QwtText trackerTextF(const QPointF& pos) const override;
};
