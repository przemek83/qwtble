#include "Picker.h"

#include <cmath>

#include <qwt_plot_canvas.h>
#include <QDebug>
#include <QPen>

#include <qwtble/QwtBleUtilities.h>

Picker::Picker(QWidget* parent) : QwtPlotPicker(parent)
{
    setTrackerMode(AlwaysOn);

    QPen pen{trackerPen()};
    pen.setColor(Qt::blue);
    pen.setWidth(2);
    setTrackerPen(pen);

    QFont actualFont{trackerFont()};
    actualFont.setPointSize(
        static_cast<int>(::lround(actualFont.pointSize() * FONT_FACTOR)));
    actualFont.setWeight(QFont::Bold);
    setTrackerFont(actualFont);
}

int Picker::getAreaOfMouse() const
{
    const auto x{::lround(invTransform(trackerPosition()).x())};
    return static_cast<int>(x);
}

void Picker::widgetEnterEvent(QEvent* event)
{
    QwtPicker::widgetEnterEvent(event);
    mouseInWidget_ = true;
}

void Picker::widgetLeaveEvent(QEvent* event)
{
    QwtPicker::widgetLeaveEvent(event);
    mouseInWidget_ = false;
}

bool Picker::getMouseInWidget() const { return mouseInWidget_; }
