#include "QuantilesPlot.h"

#include <QDebug>
#include <QResizeEvent>
#include <qwt_scale_div.h>

#include "YAxisNumberPicker.h"
#include "NotchedMarker.h"
#include "StringsScaleDraw.h"
#include "QwtBleUtilities.h"

QuantilesPlot::QuantilesPlot(QWidget* parent) :
    PlotBase(QObject::tr("Quantiles"), parent),
    marker_(new NotchedMarker({})), picker_(new YAxisNumberPicker(canvas()))
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

QuantilesPlot::~QuantilesPlot() = default;

void QuantilesPlot::resizeEvent(QResizeEvent* event)
{
    PlotBase::resizeEvent(event);
    setupLegend(event->size().width());
    replot();
}

void QuantilesPlot::setupLegend(int plotWidth)
{
    const int minWidthForLegend {90};
    if (plotWidth >= minWidthForLegend)
    {
        setAxisScale(xBottom, -0.5, 1.5, 0);
        marker_->setDrawLegend(true);
    }
    else
    {
        setAxisScale(xBottom, 0, 2, 0);
        marker_->setDrawLegend(false);
    }
}

void QuantilesPlot::setNewData(Quantiles quantiles)
{
    setToolTip(quantiles.getValuesAsToolTip());
    setAxisScale(QwtPlot::yLeft, quantiles.min_, quantiles.max_);
    setAxisScaleDraw(xBottom, new IntervalsScaleDraw(quantiles.number_));
    marker_->setQuantiles({std::move(quantiles)});
    replot();
}

QSize QuantilesPlot::minimumSizeHint() const
{
    const int minimumWidth {30};
    const int minimumHeight {100};
    return QSize(minimumWidth, minimumHeight);
}

QSize QuantilesPlot::sizeHint() const
{
    const int width {50};
    const int height {100};
    return QSize(width, height);
}

QuantilesPlot::IntervalsScaleDraw::IntervalsScaleDraw(int count) :
    count_(count)
{

}

QwtText QuantilesPlot::IntervalsScaleDraw::label(double value) const
{
    if (QwtBleUtilities::doublesAreEqual(value, 1.) && count_ != 0)
        return QwtText(QString::number(count_));
    return QwtText();
}
