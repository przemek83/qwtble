#ifndef XDATEYAXISNUMBERPICKER_H
#define XDATEYAXISNUMBERPICKER_H

#include "Picker.h"

class XDateYAxisNumberPicker : public Picker
{
    Q_OBJECT
public:
    explicit XDateYAxisNumberPicker(QWidget* parent);

    virtual ~XDateYAxisNumberPicker() override = default;

    XDateYAxisNumberPicker& operator=(const XDateYAxisNumberPicker& other) = delete;
    XDateYAxisNumberPicker(const XDateYAxisNumberPicker& other) = delete;

    XDateYAxisNumberPicker& operator=(XDateYAxisNumberPicker&& other) = delete;
    XDateYAxisNumberPicker(XDateYAxisNumberPicker&& other) = delete;

protected:
    [[nodiscard]] QwtText trackerTextF(const QPointF& pos) const override;
};

#endif // XDATEYAXISNUMBERPICKER_H
