#include <qwtble/BasicDataPlot.h>

#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_symbol.h>

#include <qwtble/QwtBleUtilities.h>

#include "XDateYAxisNumberPicker.h"

BasicDataPlot::BasicDataPlot(QWidget* parent)
    : PlotBase(QObject::tr("Basic"), parent),
      picker_(new XDateYAxisNumberPicker(canvas()))
{
    setAxisScaleDraw(xBottom, new TimeScaleDraw());

    initPlotCurve();
    initQ25();
    initQ50();
    initQ75();
    initLinearRegression();
    initLegend();

    checkLegendItems();
}

BasicDataPlot::~BasicDataPlot() = default;

void BasicDataPlot::initPlotCurve()
{
    plotData_.setStyle(QwtPlotCurve::Dots);
    auto* symbol = new QwtSymbol(QwtSymbol::Ellipse);
    symbol->setSize(3, 3);
    plotData_.setSymbol(symbol);
    QPen pen = plotData_.pen();
    pen.setColor(QColor(Qt::blue));
    pen.setWidth(3);
    plotData_.setPen(pen);
    plotData_.setZ(QwtBleUtilities::LOW_ORDER);
    plotData_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    plotData_.attach(this);
    plotData_.setTitle(QObject::tr("Data"));
}

void BasicDataPlot::initQ25()
{
    plotQ25_.setStyle(QwtPlotCurve::Lines);
    QPen pen = plotQ25_.pen();
    pen.setColor(QColor(Qt::yellow));
    pen.setWidth(3);
    plotQ25_.setPen(pen);
    plotQ25_.setZ(QwtBleUtilities::MEDIUM_ORDER);
    plotQ25_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    plotQ25_.attach(this);
    plotQ25_.setTitle(QStringLiteral("Q25"));
}

void BasicDataPlot::initQ50()
{
    plotQ50_.setStyle(QwtPlotCurve::Lines);
    QPen pen = plotQ50_.pen();
    pen.setColor(QColor(Qt::magenta));
    pen.setWidth(4);
    plotQ50_.setPen(pen);
    plotQ50_.setZ(QwtBleUtilities::MEDIUM_ORDER);
    plotQ50_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    plotQ50_.attach(this);
    plotQ50_.setTitle(QStringLiteral("Q50"));
}

void BasicDataPlot::initQ75()
{
    plotQ75_.setStyle(QwtPlotCurve::Lines);
    QPen pen = plotQ75_.pen();
    pen.setColor(QColor(Qt::green));
    pen.setWidth(3);
    plotQ75_.setPen(pen);
    plotQ75_.setZ(QwtBleUtilities::MEDIUM_ORDER);
    plotQ75_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    plotQ75_.attach(this);
    plotQ75_.setTitle(QStringLiteral("Q75"));
}

void BasicDataPlot::initLinearRegression()
{
    plotLinearRegression_.setStyle(QwtPlotCurve::Lines);
    QPen pen = plotQ75_.pen();
    pen.setColor(QColor(Qt::cyan));
    pen.setWidth(4);
    plotLinearRegression_.setPen(pen);
    plotLinearRegression_.setZ(QwtBleUtilities::HIGH_ORDER);
    plotLinearRegression_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    plotLinearRegression_.attach(this);
    plotLinearRegression_.setTitle(tr("Linear regression"));
}

void BasicDataPlot::initLegend()
{
    auto* legend = new QwtLegend();
    legend->setDefaultItemMode(QwtLegendData::Checkable);
    legend->setFrameStyle(QFrame::Box | QFrame::Sunken);

    // New connect mechanism not working as QwtLegend::checked is not detected.
    connect(legend, SIGNAL(checked(QVariant, bool, int)), this,
            SLOT(legendItemChecked(QVariant, bool, int)));
    insertLegend(legend, QwtPlot::BottomLegend);
}

void BasicDataPlot::checkLegendItems()
{
    setLegendLabelChecked(itemToInfo(&plotData_));
    setLegendLabelChecked(itemToInfo(&plotQ25_));
    setLegendLabelChecked(itemToInfo(&plotQ50_));
    setLegendLabelChecked(itemToInfo(&plotQ75_));
    setLegendLabelChecked(itemToInfo(&plotLinearRegression_));
}

void BasicDataPlot::setPlotData(const QVector<QPointF>& data)
{
    plotData_.setSamples(data);
    replot();
}

void BasicDataPlot::setNewData(const QVector<QPointF>& data,
                               const Quantiles& quantiles,
                               const QVector<QPointF>& linearRegression)
{
    setToolTip(quantiles.getValuesAsToolTip());

    if (data.isEmpty())
    {
        plotQ50_.setSamples({});
        plotQ25_.setSamples({});
        plotQ75_.setSamples({});
        plotLinearRegression_.setSamples({});
    }
    else
    {
        const double min = quantiles.minX_;
        const double max = quantiles.maxX_;
        plotQ50_.setSamples({{min, quantiles.q50_}, {max, quantiles.q50_}});
        plotQ25_.setSamples({{min, quantiles.q25_}, {max, quantiles.q25_}});
        plotQ75_.setSamples({{min, quantiles.q75_}, {max, quantiles.q75_}});
        plotLinearRegression_.setSamples(linearRegression);
    }
    setPlotData(data);
}

BasicDataPlot::TimeScaleDraw::TimeScaleDraw()
{
    setLabelRotation(QwtBleUtilities::DEFAULT_LABEL_ROTATION);
    setLabelAlignment(Qt::AlignLeft | Qt::AlignBottom);
}

QwtText BasicDataPlot::TimeScaleDraw::label(double v) const
{
    return {QwtBleUtilities::stringFromDays(lround(v))};
}

void BasicDataPlot::legendItemChecked(const QVariant& itemInfo, bool on,
                                      [[maybe_unused]] int index)
{
    QwtPlotItem* plotItem{infoToItem(itemInfo)};
    if (plotItem != nullptr)
    {
        plotItem->setVisible(on);
        replot();
    }
}

void BasicDataPlot::setLegendLabelChecked(const QVariant& itemInfo)
{
    const auto* currentLegend{::qobject_cast<QwtLegend*>(legend())};
    QWidget* legendWidget{currentLegend->legendWidget(itemInfo)};
    if (legendWidget == nullptr)
        return;

    auto* legendLabel{dynamic_cast<QwtLegendLabel*>(legendWidget)};
    if (legendLabel != nullptr)
        legendLabel->setChecked(true);
}
