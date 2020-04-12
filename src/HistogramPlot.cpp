#include "HistogramPlot.h"

#include <qwt_legend.h>
#include <qwt_legend_label.h>

#include "QwtBleUtilities.h"
#include "XYAxisNumberPicker.h"

HistogramPlot::HistogramPlot(QWidget* parent)
    : PlotBase(QObject::tr("Histogram"), parent),
      picker_(new XYAxisNumberPicker(canvas()))
{
    initHistogramPlot();
    initActualDensity();
    initLegend();
}

HistogramPlot::~HistogramPlot() = default;

void HistogramPlot::initHistogramPlot()
{
    histogram_.setStyle(QwtPlotHistogram::Columns);
    histogram_.setZ(QwtBleUtilities::LOW_ORDER);
    histogram_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    histogram_.attach(this);
    histogram_.setTitle(QObject::tr("Histogram"));
}

void HistogramPlot::initActualDensity()
{
    distributionCurve_.setTitle(QObject::tr("Distribution"));
    distributionCurve_.setStyle(QwtPlotCurve::Lines);
    distributionCurve_.setCurveAttribute(QwtPlotCurve::Fitted);
    QPen pen = distributionCurve_.pen();
    pen.setColor(QColor(Qt::blue));
    pen.setWidth(2);
    distributionCurve_.setPen(pen);
    distributionCurve_.setZ(QwtBleUtilities::HIGH_ORDER);
    distributionCurve_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    distributionCurve_.attach(this);
}

void HistogramPlot::initLegend()
{
    auto legend = new QwtLegend();
    legend->setDefaultItemMode(QwtLegendData::Checkable);
    legend->setFrameStyle(QFrame::Box | QFrame::Sunken);

    // New connect mechanism not working as QwtLegend::checked is not detected.
    connect(legend, SIGNAL(checked(QVariant, bool, int)), this,
            SLOT(legendItemChecked(QVariant, bool, int)));
    insertLegend(legend, QwtPlot::BottomLegend);

    setLegendItemChecked(&histogram_);
    setLegendItemChecked(&distributionCurve_);
}

void HistogramPlot::legendItemChecked(const QVariant& itemInfo, bool on,
                                      [[maybe_unused]] int index)
{
    QwtPlotItem* plotItem = infoToItem(itemInfo);
    if (plotItem != nullptr)
    {
        plotItem->setVisible(on);
        replot();
    }
}

void HistogramPlot::setLegendItemChecked(QwtPlotItem* plot)
{
    QWidget* legendWidget =
        qobject_cast<QwtLegend*>(legend())->legendWidget(itemToInfo(plot));

    if (legendWidget != nullptr)
    {
        auto legendLabel = dynamic_cast<QwtLegendLabel*>(legendWidget);
        if (legendLabel != nullptr)
            legendLabel->setChecked(true);
    }
}

QVector<int> HistogramPlot::getFilledIntervals(const QVector<double>& data,
                                               const Quantiles& quantiles,
                                               int intervalsCount) const
{
    const int dataCount = data.size();
    const double min = quantiles.min_;
    const double max = quantiles.max_;
    const double stepSize = (max - min) / intervalsCount;

    QVector<int> intervals(std::max(intervalsCount, dataCount));
    for (int i = 0; i < dataCount; ++i)
    {
        int index = static_cast<int>((data[i] - min) / stepSize);
        if (index > dataCount - 1)
            index = dataCount - 1;
        if (index < 0)
            index = 0;
        intervals[index]++;
    }
    return intervals;
}

void HistogramPlot::udpatePlotItems(int intervalsCount)
{
    QVector<int> intervals{
        getFilledIntervals(data_, quantiles_, intervalsCount)};
    const double min = quantiles_.min_;
    const double max = quantiles_.max_;
    const double stepSize = (max - min) / intervalsCount;
    const double middleOfStep{stepSize / 2.};

    QVector<QwtIntervalSample> samples;
    QVector<QPointF> actualPoints;
    for (int i = 0; i < intervalsCount; ++i)
    {
        const double from = min + stepSize * i;
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
