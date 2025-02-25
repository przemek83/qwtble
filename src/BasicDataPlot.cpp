#include <qwtble/BasicDataPlot.h>

#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_symbol.h>

#include <qwtble/QwtBleUtilities.h>

#include "XDateYAxisNumberPicker.h"

BasicDataPlot::BasicDataPlot(QWidget* parent)
    : PlotBase(QObject::tr("Basic"), parent),
      picker_{std::make_unique<XDateYAxisNumberPicker>(canvas())}
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

BasicDataPlot::BasicDataPlot() : BasicDataPlot(nullptr) {}

BasicDataPlot::~BasicDataPlot() = default;

void BasicDataPlot::initPlotCurve()
{
    plotData_.setStyle(QwtPlotCurve::Dots);
    QwtSymbol* symbol{new QwtSymbol(QwtSymbol::Ellipse)};
    symbol->setSize(pointDiameter_, pointDiameter_);
    plotData_.setSymbol(symbol);
    QPen pen{plotData_.pen()};
    pen.setColor(QColor(Qt::blue));
    pen.setWidth(penWidth_);
    plotData_.setPen(pen);
    plotData_.setZ(qwt_ble_utilities::LOW_ORDER);
    plotData_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    plotData_.attach(this);
    plotData_.setTitle(QObject::tr("Data"));
}

void BasicDataPlot::initQ25()
{
    plotQ25_.setStyle(QwtPlotCurve::Lines);
    QPen pen{plotQ25_.pen()};
    pen.setColor(QColor(Qt::yellow));
    pen.setWidth(penWidth_);
    plotQ25_.setPen(pen);
    plotQ25_.setZ(qwt_ble_utilities::MEDIUM_ORDER);
    plotQ25_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    plotQ25_.attach(this);
    plotQ25_.setTitle(QStringLiteral("Q25"));
}

void BasicDataPlot::initQ50()
{
    plotQ50_.setStyle(QwtPlotCurve::Lines);
    QPen pen{plotQ50_.pen()};
    pen.setColor(QColor(Qt::magenta));
    pen.setWidth(penWidth_);
    plotQ50_.setPen(pen);
    plotQ50_.setZ(qwt_ble_utilities::MEDIUM_ORDER);
    plotQ50_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    plotQ50_.attach(this);
    plotQ50_.setTitle(QStringLiteral("Q50"));
}

void BasicDataPlot::initQ75()
{
    plotQ75_.setStyle(QwtPlotCurve::Lines);
    QPen pen{plotQ75_.pen()};
    pen.setColor(QColor(Qt::green));
    pen.setWidth(penWidth_);
    plotQ75_.setPen(pen);
    plotQ75_.setZ(qwt_ble_utilities::MEDIUM_ORDER);
    plotQ75_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    plotQ75_.attach(this);
    plotQ75_.setTitle(QStringLiteral("Q75"));
}

void BasicDataPlot::initLinearRegression()
{
    plotLinearRegression_.setStyle(QwtPlotCurve::Lines);
    QPen pen{plotQ75_.pen()};
    pen.setColor(QColor(Qt::cyan));
    pen.setWidth(penWidth_);
    plotLinearRegression_.setPen(pen);
    plotLinearRegression_.setZ(qwt_ble_utilities::HIGH_ORDER);
    plotLinearRegression_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    plotLinearRegression_.attach(this);
    plotLinearRegression_.setTitle(tr("Linear regression"));
}

void BasicDataPlot::initLegend()
{
    legend_.setDefaultItemMode(QwtLegendData::Checkable);
    legend_.setFrameStyle(QFrame::Box | QFrame::Sunken);

    connect(&legend_, &QwtLegend::checked, this,
            &BasicDataPlot::legendItemChecked);
    insertLegend(&legend_, QwtPlot::BottomLegend);
}

void BasicDataPlot::checkLegendItems()
{
    setLegendLabelChecked(QwtPlot::itemToInfo(&plotData_));
    setLegendLabelChecked(QwtPlot::itemToInfo(&plotQ25_));
    setLegendLabelChecked(QwtPlot::itemToInfo(&plotQ50_));
    setLegendLabelChecked(QwtPlot::itemToInfo(&plotQ75_));
    setLegendLabelChecked(QwtPlot::itemToInfo(&plotLinearRegression_));
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
        const double min{quantiles.minX_};
        const double max{quantiles.maxX_};
        plotQ50_.setSamples({{min, quantiles.q50_}, {max, quantiles.q50_}});
        plotQ25_.setSamples({{min, quantiles.q25_}, {max, quantiles.q25_}});
        plotQ75_.setSamples({{min, quantiles.q75_}, {max, quantiles.q75_}});
        plotLinearRegression_.setSamples(linearRegression);
    }
    setPlotData(data);
}

BasicDataPlot::TimeScaleDraw::TimeScaleDraw()
{
    setLabelRotation(qwt_ble_utilities::DEFAULT_LABEL_ROTATION);
    setLabelAlignment(Qt::AlignLeft | Qt::AlignBottom);
}

QwtText BasicDataPlot::TimeScaleDraw::label(double v) const
{
    return {qwt_ble_utilities::stringFromDays(static_cast<int>(::lround(v)))};
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

void BasicDataPlot::setLegendLabelChecked(const QVariant& itemInfo) const
{
    QWidget* legendWidget{legend_.legendWidget(itemInfo)};
    if (legendWidget == nullptr)
        return;

    auto* legendLabel{dynamic_cast<QwtLegendLabel*>(legendWidget)};
    if (legendLabel != nullptr)
        legendLabel->setChecked(true);
}
