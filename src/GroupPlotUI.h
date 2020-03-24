#ifndef GROUPPLOTUI_H
#define GROUPPLOTUI_H

#include <QMap>
#include <QRegExpValidator>
#include <QWidget>

#include "GroupPlot.h"
#include "Quantiles.h"
#include "QuantilesPlot.h"
#include "qwtble_global.h"

namespace Ui
{
class GroupPlotUI;
}

class ScrollArea;

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
    void setNewData(QVector<QString> intervalsNames,
                    QVector<Quantiles> quantilesForIntervals,
                    Quantiles quantiles);

private:
    Ui::GroupPlotUI* ui;

    GroupPlot groupPlot_;

    QuantilesPlot quantilesPlot_;

    ScrollArea* scrollArea_;

private Q_SLOTS:
    void comboBoxCurrentIndexChanged(int index);

Q_SIGNALS:
    void newGroupingColumn(int column);
};

#endif // GROUPPLOTUI_H
