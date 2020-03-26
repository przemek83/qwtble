#ifndef GROUPPLOTUI_H
#define GROUPPLOTUI_H

#include <QWidget>

#include "GroupPlot.h"
#include "Quantiles.h"
#include "QuantilesPlot.h"
#include "qwtble_global.h"

namespace Ui
{
class GroupPlotUI;
}

class QSplitter;
class QScrollArea;
class QScrollBar;

/**
 * @class GroupPlotUI
 * @brief Widget pairing quantiles and grouping plots with trait combo box.
 */
class QWTBLE_EXPORT GroupPlotUI : public QWidget
{
    Q_OBJECT
public:
    explicit GroupPlotUI(QVector<std::pair<QString, int>> stringColumns,
                         QWidget* parent = nullptr);
    ~GroupPlotUI() override;

    GroupPlotUI& operator=(const GroupPlotUI& other) = delete;
    GroupPlotUI(const GroupPlotUI& other) = delete;

    GroupPlotUI& operator=(GroupPlotUI&& other) = delete;
    GroupPlotUI(GroupPlotUI&& other) = delete;

public Q_SLOTS:
    /**
     * @brief Set new data for plots.
     * @param intervalsNames Names used on bottom axis of group plot.
     * @param quantilesForIntervals Quantiles for each trait type.
     * @param quantiles General quantiles.
     */
    void setNewData(QVector<QString> intervalsNames,
                    QVector<Quantiles> quantilesForIntervals,
                    Quantiles quantiles);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    /**
     * @brief Add splitter with group and quantiles plots.
     * @return Splitter.
     */
    QSplitter* setupSplitter();

    void updateQuantilesPlotExtent();

    void adjustQuantilesPlotExtent(QScrollBar* groupPlotScrollBar);

    Ui::GroupPlotUI* ui;

    GroupPlot groupPlot_;

    QuantilesPlot quantilesPlot_;

private Q_SLOTS:
    void comboBoxCurrentIndexChanged(int index);

Q_SIGNALS:
    /**
     * @brief Signal emitted when user changes trait in combo box.
     * @param Trait index.
     */
    void newGroupingColumn(int column);
};

#endif // GROUPPLOTUI_H
