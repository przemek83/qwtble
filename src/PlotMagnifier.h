#pragma once

#include <qwt_plot_magnifier.h>

class PlotMagnifier : public QwtPlotMagnifier
{
    Q_OBJECT
public:
    using QwtPlotMagnifier::QwtPlotMagnifier;

    void reset();

protected:
    void rescale(double factor) override;

private:
    double currentFactor_{1.};
};
