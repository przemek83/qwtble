#pragma once

#include <memory>

#include <QWidget>

#include "HistogramPlot.h"
#include "qwtble_global.h"

namespace Ui
{
class HistogramPlotUI;
}  // namespace Ui

struct Quantiles;

/// @class HistogramPlotUI
/// @brief Widget pairing histogram plot with intervals count spin box.
class QWTBLE_EXPORT HistogramPlotUI : public QWidget
{
    Q_OBJECT
public:
    explicit HistogramPlotUI(QWidget* parent);
    HistogramPlotUI();

    ~HistogramPlotUI() override;

public Q_SLOTS:
    /// @brief Set new data for plot.
    /// @param data Series of values.
    /// @param quantiles Quantiles for given data.
    void setNewData(QVector<double> data, const Quantiles& quantiles);

private:
    std::unique_ptr<Ui::HistogramPlotUI> ui_;

    HistogramPlot histogramPlot_;
};
