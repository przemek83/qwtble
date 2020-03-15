#include "QuantilesPlot.h"

#include <QDebug>
#include <QResizeEvent>
#include <qwt_scale_div.h>

#include "BoxPicker.h"
#include "NotchedMarker.h"
#include "StringsScaleDraw.h"
#include "QwtBleUtilities.h"

QuantilesPlot::QuantilesPlot(QWidget* parent) :
    PlotBase(QObject::tr("Quantiles"), parent),
    marker_(new NotchedMarker(&quantiles_)),
    picker_(new BoxPicker(canvas()))
{
    quantiles_.clear();

    enableAxis(yLeft, false);

    marker_->attach(this);

    QFont font = axisFont(xBottom);
    font.setStyleStrategy(QFont::PreferAntialias);
    setAxisFont(xBottom, font);

    setAxisScale(xBottom, 0, 2, 0);

    setAxisMaxMinor(xBottom, 0);
    setAxisMaxMajor(xBottom, 3);
}

QuantilesPlot::~QuantilesPlot() = default;

void QuantilesPlot::forceResize()
{
    resizeEvent(new QResizeEvent(size(), size()));
}

void QuantilesPlot::setNewData(const Quantiles& quantiles)
{
    quantiles_.clear();
    quantiles_.append(quantiles);
    setAxisScale(QwtPlot::yLeft, static_cast<double>(quantiles.min_), static_cast<double>(quantiles.max_));

    setToolTip(quantiles.getValuesAsToolTip());

    setAxisScaleDraw(xBottom, new IntervalsScaleDraw(quantiles.number_));

    replot();
}

QSize QuantilesPlot::minimumSizeHint() const
{
    const int minimumWidth {50};
    const int minimumHeight {100};
    return QSize(minimumWidth, minimumHeight);
}

QuantilesPlot::IntervalsScaleDraw::IntervalsScaleDraw(int count) :
    count_(count)
{

}

QwtText QuantilesPlot::IntervalsScaleDraw::label(double v) const
{
    if (QwtBleUtilities::doublesAreEqual(v, 1.) && count_ != 0)
    {
        return QwtText(QString::number(count_));
    }

    return QwtText();
}
