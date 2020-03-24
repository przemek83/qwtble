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
    marker_(new NotchedMarker(&quantiles_)),
    picker_(new YAxisNumberPicker(canvas()))
{
    quantiles_.clear();

    enableAxis(yLeft, false);

    marker_->attach(this);

    QFont font = axisFont(xBottom);
    font.setStyleStrategy(QFont::PreferAntialias);
    setAxisFont(xBottom, font);

    setAxisScale(xBottom, -0.5, 1.5, 0);

    setAxisMaxMinor(xBottom, 0);
    setAxisMaxMajor(xBottom, 3);
}

QuantilesPlot::~QuantilesPlot() = default;

void QuantilesPlot::forceResize()
{
    resizeEvent(new QResizeEvent(size(), size()));
}

void QuantilesPlot::resizeEvent(QResizeEvent* event)
{
    PlotBase::resizeEvent(event);
    const int minWidthForLegend {90};
    if (event->size().width() >= minWidthForLegend)
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
    quantiles_.clear();
    quantiles_.push_back(std::move(quantiles));
    setAxisScale(QwtPlot::yLeft, quantiles.min_, quantiles.max_);

    setToolTip(quantiles.getValuesAsToolTip());

    setAxisScaleDraw(xBottom, new IntervalsScaleDraw(quantiles.number_));

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

QwtText QuantilesPlot::IntervalsScaleDraw::label(double v) const
{
    if (QwtBleUtilities::doublesAreEqual(v, 1.) && count_ != 0)
        return QwtText(QString::number(count_));
    return QwtText();
}
