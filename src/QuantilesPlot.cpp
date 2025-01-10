#include <qwtble/QuantilesPlot.h>

#include <qwt_scale_div.h>
#include <qwt_text.h>
#include <QDebug>
#include <QResizeEvent>

#include <qwtble/NotchedMarker.h>
#include <qwtble/QwtBleUtilities.h>
#include "YAxisNumberPicker.h"

QuantilesPlot::QuantilesPlot(QWidget* parent)
    : PlotBase(QObject::tr("Quantiles"), parent),
      marker_{std::make_unique<NotchedMarker>(QVector<Quantiles>{})},
      picker_{std::make_unique<YAxisNumberPicker>(canvas())}
{
    marker_->attach(this);

    enableAxis(yLeft, false);

    QFont font = axisFont(xBottom);
    font.setStyleStrategy(QFont::PreferAntialias);
    setAxisFont(xBottom, font);
    setAxisMaxMinor(xBottom, 0);
    const int maxNumberOjMajorSteps{3};
    setAxisMaxMajor(xBottom, maxNumberOjMajorSteps);

    setupLegend(width());
}

// Uncommon construction to allow forward declaration of YAxisNumberPicker.
QuantilesPlot::~QuantilesPlot() = default;

void QuantilesPlot::resizeEvent(QResizeEvent* event)
{
    PlotBase::resizeEvent(event);
    setupLegend(event->size().width());
    replot();
}

void QuantilesPlot::setupLegend(int plotWidth)
{
    const int minWidthForLegend{90};
    const double defaultMaxScale{2.0};
    if (plotWidth >= minWidthForLegend)
    {
        const double min{-0.5};
        const double max{1.5};
        setAxisScale(xBottom, min, max, 0);
        marker_->setDrawLegend(true);
    }
    else
    {
        setAxisScale(xBottom, 0, defaultMaxScale, 0);
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
    if (qwt_ble_utilities::doublesAreEqual(value, 1.) && (count_ != 0))
        return {QString::number(count_)};
    return {};
}
