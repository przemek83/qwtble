#ifndef HISTOGRAMPLOT_H
#define HISTOGRAMPLOT_H

#include <qwt_plot.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_histogram.h>

#include "PlotBase.h"
#include "PlotData.h"
#include "Quantiles.h"
#include "qwtble_global.h"

class HistPicker;
class QMouseEvent;

/**
 * @brief Histogram plot with actual density/distriburtion.
 */
class QWTBLE_EXPORT HistogramPlot : public PlotBase
{
    Q_OBJECT
public:
    explicit HistogramPlot(QWidget* parent = nullptr);

    ~HistogramPlot() override;

    HistogramPlot& operator=(const HistogramPlot& other) = delete;
    HistogramPlot(const HistogramPlot& other) = delete;

    HistogramPlot& operator=(HistogramPlot&& other) = delete;
    HistogramPlot(HistogramPlot&& other) = delete;

    void setNewData(const PlotData& plotData,
                    const Quantiles& quantiles,
                    int intervalsCount);

public Q_SLOT:
    void recompute(int intervalsCount);

private:
    void initHistogramPlot();

    void initActualDensity();

    void initLegend();

    ///Histogram plot.
    QwtPlotHistogram histPlot_;

    ///Actual density plot (blue line).
    QwtPlotCurve actualDensity_;

    std::unique_ptr<HistPicker> picker_;

    void setLegendItemChecked(QwtPlotItem* plot);

    PlotData plotData_;

    Quantiles quantiles_;

private Q_SLOTS:
    void legendItemChecked(const QVariant& itemInfo, bool on, int index);
};

#endif // HISTOGRAMPLOT_H
