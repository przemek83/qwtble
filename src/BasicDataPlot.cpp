#include "BasicDataPlot.h"

#include <cmath>

#include <QDate>
#include <QMouseEvent>
#include <QToolTip>
#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_plot_panner.h>
#include <qwt_symbol.h>

#include "XDateYAxisNumberPicker.h"
#include "QwtBleUtilities.h"

BasicDataPlot::BasicDataPlot(QWidget* parent) :
    PlotBase(QObject::tr("Basic"), parent),
    picker_(new XDateYAxisNumberPicker(canvas()))
{
    setAxisScaleDraw(xBottom, new TimeScaleDraw());

    initPlotCurve();

    initQ25();

    initQ50();

    initQ75();

    initLinearRegression();

    initLegend();

    //All items checked as all plots visible on start.
    setLegendItemChecked(&plotCurve_);
    setLegendItemChecked(&plotQ25_);
    setLegendItemChecked(&plotQ50_);
    setLegendItemChecked(&plotQ75_);
    setLegendItemChecked(&plotLinearRegression_);
}

BasicDataPlot::~BasicDataPlot() = default;

void BasicDataPlot::initPlotCurve()
{
    plotCurve_.setStyle(QwtPlotCurve::Dots);
    auto symbol = new QwtSymbol(QwtSymbol::Ellipse);
    symbol->setSize(3, 3);
    plotCurve_.setSymbol(symbol);
    QPen pen0 = plotCurve_.pen();
    pen0.setColor(QColor(Qt::blue));
    pen0.setWidth(3);
    plotCurve_.setPen(pen0);
    plotCurve_.setZ(QwtBleUtilities::LOW_ORDER);
    plotCurve_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    plotCurve_.attach(this);
    plotCurve_.setTitle(QObject::tr("Data"));
}

void BasicDataPlot::initQ25()
{
    plotQ25_.setStyle(QwtPlotCurve::Lines);
    QPen pen2 = plotQ25_.pen();
    pen2.setColor(QColor(Qt::yellow));
    pen2.setWidth(3);
    plotQ25_.setPen(pen2);
    plotQ25_.setZ(QwtBleUtilities::MEDIUM_ORDER);
    plotQ25_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    plotQ25_.attach(this);
    plotQ25_.setTitle(QStringLiteral("Q25"));
}

void BasicDataPlot::initQ50()
{
    plotQ50_.setStyle(QwtPlotCurve::Lines);
    QPen pen1 = plotQ50_.pen();
    pen1.setColor(QColor(Qt::magenta));
    pen1.setWidth(4);
    plotQ50_.setPen(pen1);
    plotQ50_.setZ(QwtBleUtilities::MEDIUM_ORDER);
    plotQ50_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    plotQ50_.attach(this);
    plotQ50_.setTitle(QStringLiteral("Q50"));
}

void BasicDataPlot::initQ75()
{
    plotQ75_.setStyle(QwtPlotCurve::Lines);
    QPen pen3 = plotQ75_.pen();
    pen3.setColor(QColor(Qt::green));
    pen3.setWidth(3);
    plotQ75_.setPen(pen3);
    plotQ75_.setZ(QwtBleUtilities::MEDIUM_ORDER);
    plotQ75_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    plotQ75_.attach(this);
    plotQ75_.setTitle(QStringLiteral("Q75"));
}

void BasicDataPlot::initLinearRegression()
{
    plotLinearRegression_.setStyle(QwtPlotCurve::Lines);
    QPen pen4 = plotQ75_.pen();
    pen4.setColor(QColor(Qt::cyan));
    pen4.setWidth(4);
    plotLinearRegression_.setPen(pen4);
    plotLinearRegression_.setZ(QwtBleUtilities::HIGH_ORDER);
    plotLinearRegression_.setRenderHint(QwtPlotItem::RenderAntialiased, true);
    plotLinearRegression_.attach(this);
    plotLinearRegression_.setTitle(tr("Linear regression"));
}

void BasicDataPlot::initLegend()
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

void BasicDataPlot::setPlotData(QVector<QPointF> data)
{
    plotCurve_.setSamples(data);
    replot();
}

void BasicDataPlot::setNewData(QVector<QPointF> data,
                               const Quantiles& quantiles,
                               const QVector<QPointF>& linearRegression)
{
    setToolTip(quantiles.getValuesAsToolTip());

    QVector<QPointF> qVector;

    if (data.size() > 0)
    {
        double min = quantiles.minX_;
        double max = quantiles.maxX_;

        qVector.append(QPointF(min, quantiles.q50_));
        qVector.append(QPointF(max, quantiles.q50_));
        plotQ50_.setSamples(qVector);
        qVector.clear();
        qVector.append(QPointF(min, quantiles.q25_));
        qVector.append(QPointF(max, quantiles.q25_));
        plotQ25_.setSamples(qVector);
        qVector.clear();
        qVector.append(QPointF(min, quantiles.q75_));
        qVector.append(QPointF(max, quantiles.q75_));
        plotQ75_.setSamples(qVector);

        plotLinearRegression_.setSamples(linearRegression);
    }
    else
    {
        plotQ50_.setSamples(qVector);
        plotQ25_.setSamples(qVector);
        plotQ75_.setSamples(qVector);
        plotLinearRegression_.setSamples(qVector);
    }

    setPlotData(std::move(data));
}


BasicDataPlot::TimeScaleDraw::TimeScaleDraw()
{
    setLabelRotation(QwtBleUtilities::DEFAULT_LABEL_ROTATION);
    setLabelAlignment(Qt::AlignLeft | Qt::AlignBottom);
}

QwtText BasicDataPlot::TimeScaleDraw::label(double v) const
{
    return QwtText(QwtBleUtilities::stringFromDays(lround(v)));
}

void BasicDataPlot::legendItemChecked(const QVariant& itemInfo, bool on, int /*index*/)
{
    QwtPlotItem* plotItem = infoToItem(itemInfo);
    if (plotItem != nullptr)
    {
        plotItem->setVisible(on);
        replot();
    }
}

void BasicDataPlot::setLegendItemChecked(QwtPlotCurve* plot)
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
