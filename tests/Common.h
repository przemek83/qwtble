#pragma once

#include <QSize>
#include <QVector>

class QwtPlot;

namespace common
{
QVector<double> getPrices();

QVector<double> getDates();

QVector<QVector<double>> getValues();

QVector<QString> getNames();

QVariant getItemInfo(QwtPlot& plot, const QString& text);

QSize getPlotSize();
}  // namespace common
