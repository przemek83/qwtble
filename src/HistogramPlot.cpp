#include <qwtble/HistogramPlot.h>

#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <QPen>

#include <qwtble/QwtBleUtilities.h>

#include "XYAxisNumberPicker.h"

HistogramPlot::HistogramPlot(QWidget* parent)
    : PlotBase(QObject::tr("Histogram"), parent),
      picker_(std::make_unique<XYAxisNumberPicker>(canvas()))
{
    initHistogramPlot();
    initActualDensity();
    initLegend();
}

// Uncommon construction to allow forward declaration of XYAxisNumberPicker.
HistogramPlot::~HistogramPlot() = default;

void HistogramPlot::initHistogramPlot()
{
    histogram_.setStyle(QwtPlotHistogram::Columns);
    histogram_.setZ(qwt_ble_utilities::LOW_ORDER);
    histogram_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    histogram_.attach(this);
    histogram_.setTitle(QObject::tr("Histogram"));
}

void HistogramPlot::initActualDensity()
{
    distributionCurve_.setTitle(QObject::tr("Distribution"));
    distributionCurve_.setStyle(QwtPlotCurve::Lines);
    distributionCurve_.setCurveAttribute(QwtPlotCurve::Fitted);
    QPen pen{distributionCurve_.pen()};
    pen.setColor(QColor(Qt::blue));
    pen.setWidth(penWidth_);
    distributionCurve_.setPen(pen);
    distributionCurve_.setZ(qwt_ble_utilities::HIGH_ORDER);
    distributionCurve_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    distributionCurve_.attach(this);
}

void HistogramPlot::initLegend()
{
    legend_.setDefaultItemMode(QwtLegendData::Checkable);
    legend_.setFrameStyle(QFrame::Box | QFrame::Sunken);

    connect(&legend_, &QwtLegend::checked, this,
            &HistogramPlot::legendItemChecked);
    insertLegend(&legend_, QwtPlot::BottomLegend);

    setLegendItemChecked(QwtPlot::itemToInfo(&histogram_));
    setLegendItemChecked(QwtPlot::itemToInfo(&distributionCurve_));
}

void HistogramPlot::legendItemChecked(const QVariant& itemInfo, bool on,
                                      [[maybe_unused]] int index)
{
    QwtPlotItem* plotItem{infoToItem(itemInfo)};
    if (plotItem != nullptr)
    {
        plotItem->setVisible(on);
        replot();
    }
}

void HistogramPlot::setLegendItemChecked(const QVariant& itemInfo) const
{
    QWidget* legendWidget{legend_.legendWidget(itemInfo)};
    if (legendWidget == nullptr)
        return;

    auto* legendLabel{dynamic_cast<QwtLegendLabel*>(legendWidget)};
    if (legendLabel != nullptr)
        legendLabel->setChecked(true);
}

QVector<int> HistogramPlot::getFilledIntervals(const QVector<double>& data,
                                               const Quantiles& quantiles,
                                               int intervalsCount)
{
    const qsizetype dataCount{data.size()};
    const double min{quantiles.min_};
    const double max{quantiles.max_};
    const double stepSize = (max - min) / intervalsCount;

    QVector<int> intervals(
        std::max(static_cast<qsizetype>(intervalsCount), dataCount));
    for (int i = 0; i < dataCount; ++i)
    {
        qsizetype index{static_cast<qsizetype>((data[i] - min) / stepSize)};
        if (index > (dataCount - 1))
            index = dataCount - 1;
        if (index < 0)
            index = 0;
        ++intervals[index];
    }
    return intervals;
}

void HistogramPlot::udpatePlotItems(int intervalsCount)
{
    QVector<int> intervals{
        getFilledIntervals(data_, quantiles_, intervalsCount)};
    const double min{quantiles_.min_};
    const double max{quantiles_.max_};
    const double stepSize{(max - min) / intervalsCount};
    const double middleOfStep{stepSize / 2.};

    QVector<QwtIntervalSample> samples;
    QVector<QPointF> actualPoints;
    for (int i{0}; i < intervalsCount; ++i)
    {
        const double from{min + (stepSize * i)};
        samples.append(QwtIntervalSample(intervals[i], from, from + stepSize));
        actualPoints.append(QPointF(from + middleOfStep, intervals[i]));
    }

    histogram_.setSamples(samples);
    distributionCurve_.setSamples(actualPoints);
}

void HistogramPlot::recompute(int intervalsCount)
{
    setToolTip(quantiles_.getValuesAsToolTip());
    udpatePlotItems(intervalsCount);
    replot();
}

void HistogramPlot::setNewData(QVector<double> data, const Quantiles& quantiles,
                               int intervalsCount)
{
    data_ = std::move(data);
    quantiles_ = quantiles;
    recompute(intervalsCount);
}
