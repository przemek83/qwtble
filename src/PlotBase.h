#pragma once

#include <memory>

#include <qwt_plot.h>
#include <qwt_plot_panner.h>
#include <qwt_scale_draw.h>

#include "PlotMagnifier.h"
#include "qwtble_global.h"

class QwtPlotPanner;

/**
 * @class PlotBase
 * @brief Base class for all plots.
 */
class QWTBLE_EXPORT PlotBase : public QwtPlot
{
    Q_OBJECT
public:
    explicit PlotBase(const QString& title, QWidget* parent = nullptr);

    /**
     * @brief Reset state of plot.
     */
    void resetPlot();

    QSize minimumSizeHint() const override;

    /**
     * @brief Set axis stale remembering before passed passed parameters.
     * @param axisId Id of axis.
     * @param min Minimum on axis.
     * @param max Maximum on axis.
     * @param step Step on axis.
     */
    void setAxisScale(int axisId, double min, double max, double step = 0);

protected:
    void setStdScaleDraw(QwtPlot::Axis axis);

    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    class IntervalsScaleDraw : public QwtScaleDraw
    {
    public:
        IntervalsScaleDraw() = default;

        ~IntervalsScaleDraw() override = default;

        IntervalsScaleDraw& operator=(const IntervalsScaleDraw& other) = delete;
        IntervalsScaleDraw(const IntervalsScaleDraw& other) = delete;

        IntervalsScaleDraw& operator=(IntervalsScaleDraw&& other) = delete;
        IntervalsScaleDraw(IntervalsScaleDraw&& other) = delete;

        QwtText label(double v) const override;
    };

    QwtPlotPanner panner_;

    std::unique_ptr<PlotMagnifier> magnifier_;

    QMap<int, QPointF> initialScaleMap_;
};
