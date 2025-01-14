#include <qwtble/HistogramPlotUI.h>

#include <qwtble/HistogramPlot.h>

#include "ui_HistogramPlotUI.h"

HistogramPlotUI::HistogramPlotUI(QWidget* parent)
    : QWidget(parent), ui_{std::make_unique<Ui::HistogramPlotUI>()}
{
    ui_->setupUi(this);

    setWindowTitle(tr("Histogram"));

    ui_->verticalLayout->addWidget(&histogramPlot_);

    connect(ui_->spinBox, ::qOverload<int>(&QSpinBox::valueChanged),
            &histogramPlot_, &HistogramPlot::recompute);
}

HistogramPlotUI::HistogramPlotUI() : HistogramPlotUI(nullptr) {}

HistogramPlotUI::~HistogramPlotUI() = default;

void HistogramPlotUI::setNewData(QVector<double> data,
                                 const Quantiles& quantiles)
{
    const int intervalsCount{ui_->spinBox->value()};
    histogramPlot_.setNewData(std::move(data), quantiles, intervalsCount);
}
