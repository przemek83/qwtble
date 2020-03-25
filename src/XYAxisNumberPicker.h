#ifndef XYAXISNUMBERPICKER_H
#define XYAXISNUMBERPICKER_H

#include "Picker.h"

class XYAxisNumberPicker : public Picker
{
    Q_OBJECT
public:
    explicit XYAxisNumberPicker(QWidget* parent);

    ~XYAxisNumberPicker() override = default;

    XYAxisNumberPicker& operator=(const XYAxisNumberPicker& other) = delete;
    XYAxisNumberPicker(const XYAxisNumberPicker& other) = delete;

    XYAxisNumberPicker& operator=(XYAxisNumberPicker&& other) = delete;
    XYAxisNumberPicker(XYAxisNumberPicker&& other) = delete;

protected:
    [[nodiscard]] QwtText trackerTextF(const QPointF& pos) const override;
};

#endif // XYAXISNUMBERPICKER_H
