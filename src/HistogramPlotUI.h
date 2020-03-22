#ifndef HISTOGRAMPLOTUI_H
#define HISTOGRAMPLOTUI_H

#include <QWidget>

#include "HistogramPlot.h"
#include "qwtble_global.h"

namespace Ui
{
class HistogramPlotUI;
}

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
    void dataChanged(QVector<double> data, Quantiles quantiles);

private:
    Ui::HistogramPlotUI* ui;

    HistogramPlot histogramPlot_;
};

#endif // HISTOGRAMPLOTUI_H
