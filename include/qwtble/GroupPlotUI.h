#pragma once

#include <memory>

#include <QWidget>

#include "GroupPlot.h"
#include "Quantiles.h"
#include "QuantilesPlot.h"
#include "qwtble_global.h"

class QSplitter;
class QScrollBar;
class QwtPlot;

namespace Ui
{
class GroupPlotUI;
}  // namespace Ui

/// @class GroupPlotUI
/// @brief Widget pairing quantiles and grouping plots with trait combo box.
class QWTBLE_EXPORT GroupPlotUI : public QWidget
{
    Q_OBJECT
public:
    explicit GroupPlotUI(const QVector<std::pair<QString, int> >& stringColumns,
                         QWidget* parent = nullptr);

    ~GroupPlotUI() override;

public Q_SLOTS:
    /// @brief Set new data for plots.
    /// @param intervalsNames Names used on bottom axis of group plot.
    /// @param quantilesForIntervals Quantiles for each trait type.
    /// @param quantiles General quantiles.
    void setNewData(const QVector<QString>& intervalsNames,
                    QVector<Quantiles> quantilesForIntervals,
                    const Quantiles& quantiles);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    /// @brief Add splitter with group and quantiles plots.
    /// @return Splitter.
    QSplitter* setupSplitter();

    double calculateExpectedExtent() const;

    static double getPlotBottomExtent(const QwtPlot& plot);

    std::unique_ptr<Ui::GroupPlotUI> ui_;

    GroupPlot groupPlot_;

    QuantilesPlot quantilesPlot_;

private Q_SLOTS:
    void updateQuantilesPlotExtent();

    void comboBoxCurrentIndexChanged(int index);

Q_SIGNALS:
    void syncPlotSizes();

    /// @brief Signal emitted when user changes trait in combo box.
    /// @param newIndex index.
    void traitIndexChanged(int newIndex);
};
