#pragma once

#include <QWidget>

#include "qwtble_global.h"

namespace Ui
{
class HistogramPlotUI;
}  // namespace Ui

class HistogramPlot;
struct Quantiles;

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

public Q_SLOTS:
    /**
     * @brief Set new data for plot.
     * @param data Series of values.
     * @param quantiles Quantiles for given data.
     */
    void setNewData(QVector<double> data, const Quantiles& quantiles);

private:
    Ui::HistogramPlotUI* ui;

    HistogramPlot* histogramPlot_;
};
