#pragma once

#include <qwt_plot_magnifier.h>

class PlotMagnifier : public QwtPlotMagnifier
{
    Q_OBJECT
public:
    explicit PlotMagnifier(QWidget* canvas);

    ~PlotMagnifier() override = default;

    void reset();

protected:
    void rescale(double factor) override;

private:
    double currentFactor_;
};
