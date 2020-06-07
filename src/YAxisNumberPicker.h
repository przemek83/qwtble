#ifndef YAXISNUMBERPICKER_H
#define YAXISNUMBERPICKER_H

#include "Picker.h"

class YAxisNumberPicker : public Picker
{
    Q_OBJECT
public:
    explicit YAxisNumberPicker(QWidget* parent);

    ~YAxisNumberPicker() override = default;

protected:
    [[nodiscard]] QwtText trackerTextF(const QPointF& pos) const override;
};

#endif  // YAXISNUMBERPICKER_H
