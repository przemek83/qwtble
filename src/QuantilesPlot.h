#ifndef QUANTILESPLOT_H
#define QUANTILESPLOT_H

#include <qwt_scale_draw.h>

#include "PlotBase.h"
#include "Quantiles.h"
#include "qwtble_global.h"

class NotchedMarker;
class YAxisNumberPicker;

/**
 * @class QuantilesPlot
 * @brief Plot showing quantiles, min, max, avg and std deviation.
 */
class QWTBLE_EXPORT QuantilesPlot : public PlotBase
{
    Q_OBJECT
public:
    explicit QuantilesPlot(QWidget* parent = nullptr);

    ~QuantilesPlot() override;

    QuantilesPlot& operator=(const QuantilesPlot& other) = delete;
    QuantilesPlot(const QuantilesPlot& other) = delete;

    QuantilesPlot& operator=(QuantilesPlot&& other) = delete;
    QuantilesPlot(QuantilesPlot&& other) = delete;

    QSize minimumSizeHint() const override;

    QSize sizeHint() const override;

public Q_SLOTS:
    /**
     * @brief Set new quantiles for plot.
     * @param quantiles New quantiles.
     */
    void setNewData(Quantiles quantiles);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    class IntervalsScaleDraw: public QwtScaleDraw
    {
    public:
        explicit IntervalsScaleDraw(int count);

        ~IntervalsScaleDraw() override = default;

        IntervalsScaleDraw& operator=(const IntervalsScaleDraw& other) = delete;
        IntervalsScaleDraw(const IntervalsScaleDraw& other) = delete;

        IntervalsScaleDraw& operator=(IntervalsScaleDraw&& other) = delete;
        IntervalsScaleDraw(IntervalsScaleDraw&& other) = delete;

        QwtText label(double value) const override;

    private:
        int count_;
    };

    void setupLegend(int plotWidth);

    std::unique_ptr<NotchedMarker> marker_;

    std::unique_ptr<YAxisNumberPicker> picker_;
};

#endif // QUANTILESPLOT_H
