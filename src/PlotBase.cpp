#include <qwtble/PlotBase.h>

#include <cmath>

#include <qwt_text.h>
#include <QMouseEvent>

#include <qwtble/QwtBleUtilities.h>

#include "PlotMagnifier.h"

PlotBase::PlotBase(const QString& title, QWidget* parent)
    : QwtPlot(parent),
      panner_(canvas()),
      magnifier_{std::make_unique<PlotMagnifier>(canvas())}
{
    // Used in export of images.
    setWindowTitle(title);

    panner_.setAxisEnabled(QwtPlot::yLeft, true);
    panner_.setAxisEnabled(QwtPlot::xBottom, true);

    setStdScaleDraw(xBottom);
    setStdScaleDraw(yLeft);

    setAxisLabelRotation(QwtPlot::xBottom,
                         qwt_ble_utilities::DEFAULT_LABEL_ROTATION);
    setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);
}

PlotBase::PlotBase(const QString& title) : PlotBase(title, nullptr) {}

// Uncommon construction to allow forward declaration of PlotMagnifier class.
PlotBase::~PlotBase() = default;

void PlotBase::mouseDoubleClickEvent(QMouseEvent* event)
{
    QwtPlot::mouseDoubleClickEvent(event);
    if (Qt::LeftButton == event->button())
        resetPlot();
}

void PlotBase::resetPlot()
{
    magnifier_->reset();
    for (int i{0}; i < QwtPlot::axisCnt; ++i)
    {
        if (initialScaleMap_.contains(i))
            setAxisScale(i, initialScaleMap_[i].rx(), initialScaleMap_[i].ry());
        else
            setAxisAutoScale(i);
    }
    replot();
}

void PlotBase::setStdScaleDraw(QwtPlot::Axis axis)
{
    setAxisScaleDraw(axis, new IntervalsScaleDraw());
}

void PlotBase::setAxisScale(int axisId, double min, double max, double step)
{
    initialScaleMap_.insert(axisId, QPointF(min, max));
    QwtPlot::setAxisScale(axisId, min, max, step);
}

QwtText PlotBase::IntervalsScaleDraw::label(double v) const
{
    using qwt_ble_utilities::doublesAreEqual;
    using qwt_ble_utilities::doubleToStringUsingLocale;

    if (!doublesAreEqual(::fmod(v, 1), 0.))
        return {doubleToStringUsingLocale(v, 1)};
    return {doubleToStringUsingLocale(v, 0)};
}

QSize PlotBase::minimumSizeHint() const
{
    const int minimumWidth{100};
    const int minimumHeight{100};
    return {minimumWidth, minimumHeight};
}
