#ifndef PLOTBASE_H
#define PLOTBASE_H

#include <memory>

#include <QPointF>
#include <qwt_plot_magnifier.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_panner.h>
#include <qwt_scale_div.h>
#include <qwt_scale_draw.h>

#include "qwtble_global.h"

class QwtPlotPanner;
class PlotMagnifier;

/**
 * @brief PlotBase class for all plots.
 */
class QWTBLE_EXPORT PlotBase : public QwtPlot
{
    Q_OBJECT
public:
    explicit PlotBase(const QString& /*title*/, QWidget* parent = nullptr);

    ~PlotBase() override;

    PlotBase& operator=(const PlotBase& other) = delete;
    PlotBase(const PlotBase& other) = delete;

    PlotBase& operator=(PlotBase&& other) = delete;
    PlotBase(PlotBase&& other) = delete;

    void resetPlot();

    void setAxisScale(int axisId, double min, double max, double step = 0);

    QSize minimumSizeHint() const override;

protected:
    QwtPlotPanner panner_;

    std::unique_ptr<PlotMagnifier> magnifier_;

    void setStdScaleDraw(QwtPlot::Axis axis);

    void mouseDoubleClickEvent(QMouseEvent* event) override;

    void setPlotTitle(const QString& title);

private:
    class IntervalsScaleDraw: public QwtScaleDraw
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

    QMap<int, QPointF> initialScaleMap_;

    void clearDistData();
};

#endif // PLOTBASE_H
