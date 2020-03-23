#include "HistogramPlot.h"

#include <QDate>
#include <QMouseEvent>
#include <QToolTip>
#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_plot_panner.h>
#include <qwt_samples.h>
#include <qwt_symbol.h>

#include "XYAxisNumberPicker.h"
#include "QwtBleUtilities.h"

HistogramPlot::HistogramPlot(QWidget* parent) :
    PlotBase(QObject::tr("Histogram"), parent),
    picker_(new XYAxisNumberPicker(canvas()))
{
    initHistogramPlot();

    initActualDensity();

    //Legend.
    initLegend();

    setLegendItemChecked(&histPlot_);
    setLegendItemChecked(&actualDensity_);
}

HistogramPlot::~HistogramPlot() = default;

void HistogramPlot::initHistogramPlot()
{
    histPlot_.setStyle(QwtPlotHistogram::Columns);
    histPlot_.setZ(QwtBleUtilities::LOW_ORDER);
    histPlot_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    histPlot_.attach(this);
    histPlot_.setTitle(QObject::tr("Histogram"));
}

void HistogramPlot::initActualDensity()
{
    actualDensity_.setTitle(QObject::tr("Distribution"));
    actualDensity_.setStyle(QwtPlotCurve::Lines);
    actualDensity_.setCurveAttribute(QwtPlotCurve::Fitted);
    QPen pen = actualDensity_.pen();
    pen.setColor(QColor(Qt::blue));
    pen.setWidth(2);
    actualDensity_.setPen(pen);
    actualDensity_.setZ(QwtBleUtilities::HIGH_ORDER);
    actualDensity_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    actualDensity_.attach(this);
}

void HistogramPlot::initLegend()
{
    auto legend = new QwtLegend();
    legend->setDefaultItemMode(QwtLegendData::Checkable);
    legend->setFrameStyle(QFrame::Box | QFrame::Sunken);

    // New connect mechanism not working as QwtLegend::checked is not detected.
    connect(legend,
            SIGNAL(checked(QVariant, bool, int)),
            this,
            SLOT(legendItemChecked(QVariant, bool, int)));
    insertLegend(legend, QwtPlot::BottomLegend);
}

void HistogramPlot::legendItemChecked(const QVariant& itemInfo, bool on, int /*index*/)
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
        if (nullptr != legendLabel)
        {
            legendLabel->setChecked(true);
        }
    }
}

void HistogramPlot::recompute(int intervalsCount)
{
    setToolTip(quantiles_.getValuesAsToolTip());
    const int count = data_.size();

    /* To normalize use formula:
       Z = (X - Mean) / stdDev */

    const double min = quantiles_.min_;
    const double max = quantiles_.max_;

    double step = (max - min) / static_cast<double>(intervalsCount);

    QVector<int> intervals(std::max(intervalsCount, count));
    for (int i = 0; i < count; ++i)
    {
        int index = static_cast<int>((data_[i] - min) / step);
        if (index > count - 1)
        {
            index = count - 1;
        }
        if (index < 0)
        {
            index = 0;
        }
        intervals[index]++;
    }

    QVector< QwtIntervalSample > samples;
    QVector< QPointF > actualPoints;
    const double middleOfStep {step / 2.};
    for (int i = 0; i < intervalsCount; ++i)
    {
        double x = min + step * static_cast<double>(i);
        samples.append(QwtIntervalSample(intervals[i], x, x + step));
        actualPoints.append(QPointF(x + middleOfStep, intervals[i]));
    }

    histPlot_.setSamples(samples);
    actualDensity_.setSamples(actualPoints);

    replot();
}

void HistogramPlot::setNewData(QVector<double> data,
                               Quantiles quantiles,
                               int intervalsCount)
{
    data_ = std::move(data);
    quantiles_ = std::move(quantiles);
    recompute(intervalsCount);
}
