#pragma once

#include <QSize>
#include <QVector>

class QwtPlot;

namespace common
{
QVector<double> getPrices();

QVector<double> getDates();

QVariant getItemInfo(QwtPlot& plot, const QString& text);

QSize getPlotSize();
}  // namespace common
