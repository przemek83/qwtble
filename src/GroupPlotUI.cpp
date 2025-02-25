#include <qwtble/GroupPlotUI.h>

#include <QComboBox>
#include <QHBoxLayout>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QSplitter>

#include <qwtble/QwtBleUtilities.h>

#include "ui_GroupPlotUI.h"

GroupPlotUI::GroupPlotUI(const QVector<std::pair<QString, int> >& stringColumns,
                         QWidget* parent)
    : QWidget(parent), ui_{std::make_unique<Ui::GroupPlotUI>()}
{
    ui_->setupUi(this);

    connect(ui_->comboBox, ::qOverload<int>(&QComboBox::currentIndexChanged),
            this, &GroupPlotUI::comboBoxCurrentIndexChanged);

    QSplitter* splitter{setupSplitter()};
    ui_->verticalLayout->addWidget(splitter);

    for (const auto& [columnName, index] : stringColumns)
        ui_->comboBox->addItem(columnName, QVariant(index));

    connect(this, &GroupPlotUI::syncPlotSizes, this,
            &GroupPlotUI::updateQuantilesPlotExtent);
}

GroupPlotUI::GroupPlotUI(const QVector<std::pair<QString, int> >& stringColumns)
    : GroupPlotUI(stringColumns, nullptr)
{
}

GroupPlotUI::~GroupPlotUI() = default;

void GroupPlotUI::setNewData(const QVector<QString>& intervalsNames,
                             QVector<Quantiles> quantilesForIntervals,
                             const Quantiles& quantiles)
{
    const double minY{quantiles.min_};
    const double maxY{quantiles.max_};
    groupPlot_.setAxisScale(QwtPlot::yLeft, minY, maxY);
    groupPlot_.setAxisScale(QwtPlot::yRight, minY, maxY);
    groupPlot_.setAxisScale(QwtPlot::xBottom, 0,
                            static_cast<double>(intervalsNames.size()) + 1, 1);

    groupPlot_.setNewData(std::move(quantilesForIntervals), intervalsNames);

    quantilesPlot_.setNewData(quantiles);

    QApplication::processEvents();
    updateQuantilesPlotExtent();
}

void GroupPlotUI::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    // Match sizes using async call. Prevent recursive resize call.
    Q_EMIT syncPlotSizes();
}

QSplitter* GroupPlotUI::setupSplitter()
{
    QSplitter* splitter{new QSplitter(Qt::Horizontal, this)};
    connect(splitter, &QSplitter::splitterMoved, this,
            [this]([[maybe_unused]] int pos, [[maybe_unused]] int index)
            {
                QApplication::processEvents();
                updateQuantilesPlotExtent();
            });
    QScrollArea* scrollArea{new QScrollArea(this)};
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(&groupPlot_);
    splitter->addWidget(scrollArea);
    splitter->addWidget(&quantilesPlot_);
    constexpr int groupPlotStretchFactor{2};
    constexpr int quantilesPlotStretchFactor{1};
    splitter->setStretchFactor(0, groupPlotStretchFactor);
    splitter->setStretchFactor(1, quantilesPlotStretchFactor);
    return splitter;
}

void GroupPlotUI::updateQuantilesPlotExtent()
{
    const double expectedExtent{calculateExpectedExtent()};
    if (qwt_ble_utilities::doublesAreEqual(expectedExtent,
                                           getPlotBottomExtent(quantilesPlot_)))
        return;

    quantilesPlot_.axisScaleDraw(QwtPlot::xBottom)
        ->setMinimumExtent(expectedExtent);

    // Force resize to have both plots on same level.
    QSize oryginalSize{quantilesPlot_.size()};
    quantilesPlot_.resize({0, 0});
    quantilesPlot_.resize(oryginalSize);
}

double GroupPlotUI::calculateExpectedExtent() const
{
    const auto* scrollArea{
        ::qobject_cast<QScrollArea*>(groupPlot_.parent()->parent())};
    const QScrollBar* groupPlotScrollBar{scrollArea->horizontalScrollBar()};
    int scrollBarSize{0};
    if (groupPlotScrollBar->isVisible())
        scrollBarSize = groupPlotScrollBar->height();

    const double groupPlotExtent{getPlotBottomExtent(groupPlot_)};
    return groupPlotExtent + scrollBarSize;
}

double GroupPlotUI::getPlotBottomExtent(const QwtPlot& plot)
{
    const QwtScaleDraw* groupPlotScaleDraw{
        plot.axisScaleDraw(QwtPlot::xBottom)};
    const double plotExtent{
        groupPlotScaleDraw->extent(plot.axisFont(QwtPlot::xBottom))};
    return plotExtent;
}

void GroupPlotUI::comboBoxCurrentIndexChanged(int index)
{
    Q_EMIT traitIndexChanged(ui_->comboBox->itemData(index).toInt());
}
