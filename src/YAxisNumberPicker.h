#ifndef YAXISNUMBERPICKER_H
#define YAXISNUMBERPICKER_H

#include "Picker.h"

class YAxisNumberPicker : public Picker
{
    Q_OBJECT
public:
    explicit YAxisNumberPicker(QWidget* parent);

    virtual ~YAxisNumberPicker() override = default;

    YAxisNumberPicker& operator=(const YAxisNumberPicker& other) = delete;
    YAxisNumberPicker(const YAxisNumberPicker& other) = delete;

    YAxisNumberPicker& operator=(YAxisNumberPicker&& other) = delete;
    YAxisNumberPicker(YAxisNumberPicker&& other) = delete;

protected:
    QwtText trackerTextF(const QPointF& pos) const override;
};

#endif // YAXISNUMBERPICKER_H
