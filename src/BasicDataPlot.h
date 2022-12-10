#pragma once

#include <qwt_plot_curve.h>

#include "PlotBase.h"
#include "Quantiles.h"
#include "qwtble_global.h"

class XDateYAxisNumberPicker;

/**
 * @class BasicDataPlot
 * @brief Plot showing data plus quantiles and linear regression curves.
 */
class QWTBLE_EXPORT BasicDataPlot : public PlotBase
{
    Q_OBJECT
public:
    explicit BasicDataPlot(QWidget* parent = nullptr);

public Q_SLOTS:
    /**
     * @brief Set new data for plot.
     * @param data Data points.
     * @param quantiles Quantiles for data.
     * @param linearRegression Linear regression points.
     */
    void setNewData(const QVector<QPointF>& data, const Quantiles& quantiles,
                    const QVector<QPointF>& linearRegression);

private:
    class TimeScaleDraw : public QwtScaleDraw
    {
    public:
        TimeScaleDraw();

        ~TimeScaleDraw() override = default;

        TimeScaleDraw& operator=(const TimeScaleDraw& other) = delete;
        TimeScaleDraw(const TimeScaleDraw& other) = delete;

        TimeScaleDraw& operator=(TimeScaleDraw&& other) = delete;
        TimeScaleDraw(TimeScaleDraw&& other) = delete;

        [[nodiscard]] QwtText label(double v) const override;
    };

    void setPlotData(const QVector<QPointF>& data);

    void initPlotCurve();
    void initQ25();
    void initQ50();
    void initQ75();
    void initLinearRegression();
    void initLegend();

    void checkLegendItems();

    /**
     * @brief set given item checked on legend.
     * @param plot plot related to item on legend.
     */
    void setLegendItemChecked(QwtPlotCurve* plot);

    QwtPlotCurve plotQ25_;
    QwtPlotCurve plotQ50_;
    QwtPlotCurve plotQ75_;
    QwtPlotCurve plotLinearRegression_;
    QwtPlotCurve plotData_;

    std::unique_ptr<XDateYAxisNumberPicker> picker_;

private Q_SLOTS:
    void legendItemChecked(const QVariant& itemInfo, bool on, int index);
};
