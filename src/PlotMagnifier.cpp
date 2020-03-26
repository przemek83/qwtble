#include "PlotMagnifier.h"

PlotMagnifier::PlotMagnifier(QWidget* canvas)
    : QwtPlotMagnifier(canvas)
{
    currentFactor_ = 1.;
}

void PlotMagnifier::rescale(double factor)
{
    currentFactor_ *= factor;
    QwtPlotMagnifier::rescale(factor);
}

void PlotMagnifier::reset()
{
    rescale(1. / currentFactor_);
    currentFactor_ = 1.;
}
