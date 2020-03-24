#ifndef QUANTILESPLOT_H
#define QUANTILESPLOT_H

#include <qwt_scale_draw.h>

#include "PlotBase.h"
#include "Quantiles.h"
#include "qwtble_global.h"

class NotchedMarker;
class YAxisNumberPicker;

/**
 * @brief plot showing quantiles (q25, q50, q75, min, max, avg).
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

    void setNewData(Quantiles quantiles);

    QSize minimumSizeHint() const override;

    QSize sizeHint() const override;

    void forceResize();

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

        QwtText label(double v) const override;

    private:
        int count_;
    };

    std::unique_ptr<NotchedMarker> marker_;

    //One, but marker expects vector.
    QVector<Quantiles> quantiles_;

    std::unique_ptr<YAxisNumberPicker> picker_;
};

#endif // QUANTILESPLOT_H
