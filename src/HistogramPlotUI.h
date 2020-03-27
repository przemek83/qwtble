#ifndef HISTOGRAMPLOTUI_H
#define HISTOGRAMPLOTUI_H

#include <QWidget>

#include "HistogramPlot.h"
#include "qwtble_global.h"

namespace Ui
{
class HistogramPlotUI;
}

/**
 * @class HistogramPlotUI
 * @brief Widget pairing histogram plot with intervals count spin box.
 */
class QWTBLE_EXPORT HistogramPlotUI : public QWidget
{
    Q_OBJECT
public:
    explicit HistogramPlotUI(QWidget* parent = nullptr);
    ~HistogramPlotUI() override;

    HistogramPlotUI& operator=(const HistogramPlotUI& other) = delete;
    HistogramPlotUI(const HistogramPlotUI& other) = delete;

    HistogramPlotUI& operator=(HistogramPlotUI&& other) = delete;
    HistogramPlotUI(HistogramPlotUI&& other) = delete;

public Q_SLOTS:
    /**
     * @brief Set new data for plot.
     * @param data Series of values.
     * @param quantiles Quantiles for given data.
     */
    void setNewData(QVector<double> data, Quantiles quantiles);

private:
    Ui::HistogramPlotUI* ui;

    HistogramPlot histogramPlot_;
};

#endif // HISTOGRAMPLOTUI_H
