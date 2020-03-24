#ifndef BASICDATAPLOT_H
#define BASICDATAPLOT_H

#include <qwt_plot.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>

#include "PlotBase.h"
#include "Quantiles.h"
#include "qwtble_global.h"

class XDateYAxisNumberPicker;
class QMouseEvent;

/**
 * @brief Linear regression plot with data and quantile 25, 50 and 75.
 */
class QWTBLE_EXPORT BasicDataPlot : public PlotBase
{
    Q_OBJECT
public:
    explicit BasicDataPlot(QWidget* parent = nullptr);

    ~BasicDataPlot() override;

    BasicDataPlot& operator=(const BasicDataPlot& other) = delete;
    BasicDataPlot(const BasicDataPlot& other) = delete;

    BasicDataPlot& operator=(BasicDataPlot&& other) = delete;
    BasicDataPlot(BasicDataPlot&& other) = delete;

public Q_SLOTS:
    virtual void setNewData(QVector<QPointF> data,
                            Quantiles quantiles,
                            QVector<QPointF> linearRegression);

private:
    void setPlotData(QVector<QPointF> data);

    void initPlotCurve();
    void initQ25();
    void initQ50();
    void initQ75();
    void initLinearRegression();
    void initLegend();

    QwtPlotCurve plotQ25_;
    QwtPlotCurve plotQ50_;
    QwtPlotCurve plotQ75_;
    QwtPlotCurve plotLinearRegression_;

    class TimeScaleDraw: public QwtScaleDraw
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

    std::unique_ptr<XDateYAxisNumberPicker> picker_;

    /**
     * @brief set given item checked on legend.
     * @param plot plot related to item on legend.
     */
    void setLegendItemChecked(QwtPlotCurve* plot);

    QwtPlotCurve plotCurve_;

private Q_SLOTS:
    void legendItemChecked(const QVariant& itemInfo, bool on, int index);
};

#endif // BASICDATAPLOT_H
