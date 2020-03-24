#ifndef GROUPPLOT_H
#define GROUPPLOT_H

#include <QEvent>

#include <qwt_scale_div.h>
#include <qwt_plot_curve.h>

#include "PlotBase.h"
#include "Quantiles.h"
#include "qwtble_global.h"

class NotchedMarker;
class QwtPlotCurve;
class YAxisNumberPicker;

/**
 * @brief Plot on which user can group by text columns.
 */
class QWTBLE_EXPORT GroupPlot : public PlotBase
{
    Q_OBJECT
public:
    explicit GroupPlot(QWidget* parent = nullptr);

    ~GroupPlot() override;

    GroupPlot& operator=(const GroupPlot& other) = delete;
    GroupPlot(const GroupPlot& other) = delete;

    GroupPlot& operator=(GroupPlot&& other) = delete;
    GroupPlot(GroupPlot&& other) = delete;

    QSize minimumSizeHint() const override;

public Q_SLOTS:
    void setNewData(QVector<Quantiles> quantiles,
                    QVector<QString> intervalStrings);

protected:
    bool event(QEvent* event) override;

private:
    QVector<QString>
    shortenIntervalsNamesIfNeeded(const QVector<QString>& intervalsNames,
                                  const QVector<Quantiles>& quantilesForIntervals);

    ///Maximum number of chars in label.
    static constexpr int maxCharsInLabel_ {20};

    std::unique_ptr<NotchedMarker> marker_;

    //Quantiles.
    QVector<Quantiles> quantiles_;

    //Names used on axis.
    QVector<QString> shortIntervalNames_;

    ///Names used in tooltip.
    QVector<QString> longIntervalNames_;

    std::unique_ptr<YAxisNumberPicker> picker_;
};
#endif // GROUPPLOT_H
