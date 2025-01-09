#pragma once

#include <qwt_plot_picker.h>

/// @brief Base class for pickers - display of coordinates on mouse action.
class Picker : public QwtPlotPicker
{
    Q_OBJECT
public:
    explicit Picker(QWidget* parent);

    int getAreaOfMouse();

    bool getMouseInWidget() const;

protected:
    QwtText trackerTextF(const QPointF& pos) const override = 0;

    void widgetEnterEvent(QEvent* event) override;

    void widgetLeaveEvent(QEvent* event) override;

private:
    bool mouseInWidget_{false};

    static constexpr double FONT_FACTOR{1.4};
};
