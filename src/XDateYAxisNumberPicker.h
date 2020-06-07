#ifndef XDATEYAXISNUMBERPICKER_H
#define XDATEYAXISNUMBERPICKER_H

#include "Picker.h"

class XDateYAxisNumberPicker : public Picker
{
    Q_OBJECT
public:
    explicit XDateYAxisNumberPicker(QWidget* parent);

    ~XDateYAxisNumberPicker() override = default;

protected:
    [[nodiscard]] QwtText trackerTextF(const QPointF& pos) const override;
};

#endif  // XDATEYAXISNUMBERPICKER_H
