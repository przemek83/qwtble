#pragma once

#include <qwt_plot_picker.h>

/// @brief Base class for pickers - display of coordinates on mouse action.
class Picker : public QwtPlotPicker
{
    Q_OBJECT
public:
    explicit Picker(QWidget* parent);

    int getAreaOfMouse() const;

    bool getMouseInWidget() const;

protected:
    void widgetEnterEvent(QEvent* event) override;

    void widgetLeaveEvent(QEvent* event) override;

private:
    bool mouseInWidget_{false};

    static constexpr double FONT_FACTOR{1.4};
};
