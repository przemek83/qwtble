#pragma once

#include "PlotBase.h"
#include "Quantiles.h"
#include "qwtble_global.h"

class NotchedMarker;
class YAxisNumberPicker;

/// @class GroupPlot
/// @brief Plot showing data grouped by trait types using notched markers.
class QWTBLE_EXPORT GroupPlot : public PlotBase
{
    Q_OBJECT
public:
    explicit GroupPlot(QWidget* parent = nullptr);

    ~GroupPlot() override;

    QSize minimumSizeHint() const override;

public Q_SLOTS:
    /// @brief Set new data for group plot.
    /// @param quantilesVector Quantiles for each trait type.
    /// @param intervalStrings Names of trait types.
    void setNewData(QVector<Quantiles> quantilesVector,
                    const QVector<QString>& intervalStrings);

protected:
    bool event(QEvent* event) override;

private:
    static QVector<QString> createAxisIntervalsNames(
        const QVector<QString>& intervalsNames,
        const QVector<Quantiles>& quantilesVector);

    static QVector<QString> createTooltips(
        const QVector<QString>& intervalsNames,
        const QVector<Quantiles>& quantilesVector);

    /// Maximum number of chars in label.
    static constexpr int maxCharsInLabel_{20};

    std::unique_ptr<NotchedMarker> marker_;

    QVector<QString> tooltips_;

    std::unique_ptr<YAxisNumberPicker> picker_;
};
