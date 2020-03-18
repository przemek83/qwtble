#ifndef NOTCHEDMARKER_H
#define NOTCHEDMARKER_H

#include <qwt_plot_item.h>

#include "qwtble_global.h"

struct Quantiles;

/**
 * @brief Notched marker for display of quantiles, min, max and avg in one item.
 */
class QWTBLE_EXPORT NotchedMarker : public QwtPlotItem
{
public:
    explicit NotchedMarker(QVector<Quantiles>* quantiles);

    ~NotchedMarker() override = default;

    NotchedMarker& operator=(const NotchedMarker& other) = delete;
    NotchedMarker(const NotchedMarker& other) = delete;

    NotchedMarker& operator=(NotchedMarker&& other) = delete;
    NotchedMarker(NotchedMarker&& other) = delete;

    int rtti() const override;

    void draw(QPainter* p, const QwtScaleMap& xMap, const QwtScaleMap& yMap,
              const QRectF& rect) const override;

protected:
    void drawLegend(QPainter* p, const QRectF& rect) const;

    void drawElement(QPainter* p, int elementNumber,
                     const QwtScaleMap& xMap, const QwtScaleMap& yMap,
                     double width, const Quantiles& quantiles) const;

private:
    QBrush markerBrush_;

    QVector<Quantiles>* quantiles_;
};

#endif // NOTCHEDMARKER_H
