#include "GroupPlotUI.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QResizeEvent>
#include <QScrollBar>
#include <QSplitter>
#include <QtAlgorithms>

#include "ScrollArea.h"
#include "ui_GroupPlotUI.h"

GroupPlotUI::GroupPlotUI(QVector<std::pair<QString, int> > stringColumns, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::GroupPlotUI)
{
    ui->setupUi(this);

    connect(ui->comboBox, qOverload<int>(&QComboBox::currentIndexChanged),
            this, &GroupPlotUI::comboBoxCurrentIndexChanged);

    //Add splitter with group and quantiles plots.
    auto splitter = new QSplitter(Qt::Horizontal, this);
    scrollArea_ = new ScrollArea(this);
    scrollArea_->setWidgetResizable(true);
    scrollArea_->setWidget(&groupPlot_);
    splitter->addWidget(scrollArea_);
    splitter->addWidget(&quantilesPlot_);
    splitter->setStretchFactor(0, 2);
    splitter->setStretchFactor(1, 1);
    ui->verticalLayout->insertWidget(2, splitter, 0);

    ui->comboBox->clear();

    for (const auto& [columnName, index] : stringColumns)
        ui->comboBox->addItem(columnName, QVariant(index));
}

GroupPlotUI::~GroupPlotUI()
{
    delete ui;
}

void GroupPlotUI::setNewData(QVector<QString> intervalsNames,
                             QVector<Quantiles> quantilesForIntervals,
                             Quantiles quantiles)
{
    const double minY = quantiles.min_;
    const double maxY = quantiles.max_;
    groupPlot_.setAxisScale(QwtPlot::yLeft, minY, maxY);
    groupPlot_.setAxisScale(QwtPlot::yRight, minY, maxY);
    groupPlot_.setAxisScale(QwtPlot::xBottom, 0, intervalsNames.size() + 1, 1);

    groupPlot_.setNewData(std::move(quantilesForIntervals),
                          std::move(intervalsNames));

    quantilesPlot_.setNewData(std::move(quantiles));

    scrollArea_->forceResize();

    int scrollBarSize = 0;

    if (scrollArea_->horizontalScrollBar()->minimum() !=
        scrollArea_->horizontalScrollBar()->maximum())
    {
        scrollBarSize = scrollArea_->horizontalScrollBar()->height();
    }

    // Fix for problem when scrollbar after resize is not visible.
    // Quantiles plot not resized.
    double minExtentForQuantiles =
        groupPlot_.axisScaleDraw(QwtPlot::xBottom)->extent(groupPlot_.axisFont(QwtPlot::xBottom));
    groupPlot_.axisScaleDraw(QwtPlot::xBottom)->setMinimumExtent(minExtentForQuantiles);

    quantilesPlot_.axisScaleDraw(QwtPlot::xBottom)->setMinimumExtent(minExtentForQuantiles + scrollBarSize);
    quantilesPlot_.forceResize();
}

void GroupPlotUI::comboBoxCurrentIndexChanged(int index)
{
    Q_EMIT newGroupingColumn(ui->comboBox->itemData(index).toInt());
}
