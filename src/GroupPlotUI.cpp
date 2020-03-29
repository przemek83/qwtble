#include "GroupPlotUI.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QSplitter>

#include "ui_GroupPlotUI.h"

GroupPlotUI::GroupPlotUI(const QVector<std::pair<QString, int> >& stringColumns,
                         QWidget* parent) :
    QWidget(parent),
    ui(new Ui::GroupPlotUI)
{
    ui->setupUi(this);

    connect(ui->comboBox, qOverload<int>(&QComboBox::currentIndexChanged),
            this, &GroupPlotUI::comboBoxCurrentIndexChanged);

    QSplitter* splitter = setupSplitter();
    ui->verticalLayout->insertWidget(2, splitter, 0);

    for (const auto& [columnName, index] : stringColumns)
        ui->comboBox->addItem(columnName, QVariant(index));
}

GroupPlotUI::~GroupPlotUI()
{
    delete ui;
}

void GroupPlotUI::setNewData(const QVector<QString>& intervalsNames,
                             QVector<Quantiles> quantilesForIntervals,
                             const Quantiles& quantiles)
{
    const double minY = quantiles.min_;
    const double maxY = quantiles.max_;
    groupPlot_.setAxisScale(QwtPlot::yLeft, minY, maxY);
    groupPlot_.setAxisScale(QwtPlot::yRight, minY, maxY);
    groupPlot_.setAxisScale(QwtPlot::xBottom, 0, intervalsNames.size() + 1, 1);

    groupPlot_.setNewData(std::move(quantilesForIntervals),
                          intervalsNames);

    quantilesPlot_.setNewData(quantiles);

    // Workaround: update twice as after first one extent might be incorrect.
    updateQuantilesPlotExtent();
    updateQuantilesPlotExtent();
}

void GroupPlotUI::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    updateQuantilesPlotExtent();
}

QSplitter* GroupPlotUI::setupSplitter()
{
    auto splitter = new QSplitter(Qt::Horizontal, this);
    connect(splitter,
            &QSplitter::splitterMoved,
            this,
            [ = ]([[maybe_unused]] int pos, [[maybe_unused]] int index)
    {
        updateQuantilesPlotExtent();
    });
    auto scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(&groupPlot_);
    splitter->addWidget(scrollArea);
    splitter->addWidget(&quantilesPlot_);
    splitter->setStretchFactor(0, 2);
    splitter->setStretchFactor(1, 1);
    return splitter;
}

void GroupPlotUI::updateQuantilesPlotExtent()
{
    // Adjust quantiles plot extent size to match group plot one.
    auto scrollArea = qobject_cast<QScrollArea*>(groupPlot_.parent()->parent());
    adjustQuantilesPlotExtent(scrollArea->horizontalScrollBar());

    // Enforce size update of quantiles plot.
    auto resizeEvent =
        new QResizeEvent(quantilesPlot_.size(), quantilesPlot_.size());
    QCoreApplication::postEvent(&quantilesPlot_, resizeEvent);
    QApplication::processEvents();
}

void GroupPlotUI::adjustQuantilesPlotExtent(QScrollBar* groupPlotScrollBar)
{
    int scrollBarSize {0};
    if (groupPlotScrollBar->isVisible())
        scrollBarSize = groupPlotScrollBar->height();

    const auto groupPlotScaleDraw = groupPlot_.axisScaleDraw(QwtPlot::xBottom);
    const double plotExtent =
        groupPlotScaleDraw->extent(groupPlot_.axisFont(QwtPlot::xBottom));
    const double newExtent {plotExtent + scrollBarSize};
    quantilesPlot_.axisScaleDraw(QwtPlot::xBottom)->setMinimumExtent(newExtent);
}

void GroupPlotUI::comboBoxCurrentIndexChanged(int index)
{
    Q_EMIT traitIndexChanged(ui->comboBox->itemData(index).toInt());
}
