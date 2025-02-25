#pragma once

#include <qwt_legend.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_histogram.h>

#include "PlotBase.h"
#include "Quantiles.h"
#include "qwtble_global.h"

class QMouseEvent;
class XYAxisNumberPicker;

/// @class HistogramPlot
/// @brief Histogram plot with distribution.
class QWTBLE_EXPORT HistogramPlot : public PlotBase
{
    Q_OBJECT
public:
    explicit HistogramPlot(QWidget* parent);
    HistogramPlot();

    ~HistogramPlot() override;

public Q_SLOTS:
    /// @brief Set new data for plot.
    /// @param data Series of values.
    /// @param quantiles Quantiles for given data.
    /// @param intervalsCount Number of histogram intervals.
    void setNewData(QVector<double> data, const Quantiles& quantiles,
                    int intervalsCount);

    /// @brief Recompute histogram with given intervals count.
    /// @param intervalsCount Intervals count.
    void recompute(int intervalsCount);

private:
    void initHistogramPlot();
    void initActualDensity();
    void initLegend();

    void setLegendItemChecked(const QVariant& itemInfo) const;

    static QVector<int> getFilledIntervals(const QVector<double>& data,
                                           const Quantiles& quantiles,
                                           int intervalsCount);

    void udpatePlotItems(int intervalsCount);

    QwtPlotHistogram histogram_;

    QwtPlotCurve distributionCurve_;

    std::unique_ptr<XYAxisNumberPicker> picker_;

    QVector<double> data_;

    Quantiles quantiles_;

    QwtLegend legend_;

    int penWidth_{2};

private Q_SLOTS:
    void legendItemChecked(const QVariant& itemInfo, bool on, int index);
};
