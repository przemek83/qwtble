#include "QuantilesPlot.h"

#include <qwt_scale_div.h>
#include <QDebug>
#include <QResizeEvent>

#include "NotchedMarker.h"
#include "QwtBleUtilities.h"
#include "StringsScaleDraw.h"
#include "YAxisNumberPicker.h"

QuantilesPlot::QuantilesPlot(QWidget* parent)
    : PlotBase(QObject::tr("Quantiles"), parent),
      marker_(new NotchedMarker({})),
      picker_(new YAxisNumberPicker(canvas()))
{
    marker_->attach(this);

    enableAxis(yLeft, false);

    QFont font = axisFont(xBottom);
    font.setStyleStrategy(QFont::PreferAntialias);
    setAxisFont(xBottom, font);
    setAxisMaxMinor(xBottom, 0);
    setAxisMaxMajor(xBottom, 3);

    setupLegend(width());
}

void QuantilesPlot::resizeEvent(QResizeEvent* event)
{
    PlotBase::resizeEvent(event);
    setupLegend(event->size().width());
    replot();
}

void QuantilesPlot::setupLegend(int plotWidth)
{
    const int minWidthForLegend{90};
    if (plotWidth >= minWidthForLegend)
    {
        const double min{-0.5};
        const double max{1.5};
        setAxisScale(xBottom, min, max, 0);
        marker_->setDrawLegend(true);
    }
    else
    {
        setAxisScale(xBottom, 0, 2, 0);
        marker_->setDrawLegend(false);
    }
}

void QuantilesPlot::setNewData(const Quantiles& quantiles)
{
    setToolTip(quantiles.getValuesAsToolTip());
    setAxisScale(QwtPlot::yLeft, quantiles.min_, quantiles.max_);
    setAxisScaleDraw(xBottom, new IntervalsScaleDraw(quantiles.count_));
    marker_->setQuantiles({quantiles});
    replot();
}

QSize QuantilesPlot::minimumSizeHint() const
{
    const int minimumWidth{30};
    const int minimumHeight{100};
    return {minimumWidth, minimumHeight};
}

QSize QuantilesPlot::sizeHint() const
{
    const int width{50};
    const int height{100};
    return {width, height};
}

QuantilesPlot::IntervalsScaleDraw::IntervalsScaleDraw(int count) : count_(count)
{
}

QwtText QuantilesPlot::IntervalsScaleDraw::label(double value) const
{
    if (QwtBleUtilities::doublesAreEqual(value, 1.) && count_ != 0)
        return {QString::number(count_)};
    return {};
}
