#ifndef XYAXISNUMBERPICKER_H
#define XYAXISNUMBERPICKER_H

#include "Picker.h"

class XYAxisNumberPicker : public Picker
{
    Q_OBJECT
public:
    explicit XYAxisNumberPicker(QWidget* parent);

    ~XYAxisNumberPicker() override = default;

protected:
    [[nodiscard]] QwtText trackerTextF(const QPointF& pos) const override;
};

#endif  // XYAXISNUMBERPICKER_H
