#pragma once

#include <QBrush>
#include <QVector>

#include <qwt_plot_item.h>

#include "qwtble_global.h"

struct Quantiles;

/// @class NotchedMarker
/// @brief Notched marker displaying quantiles, min, max and mean.
class QWTBLE_EXPORT NotchedMarker : public QwtPlotItem
{
public:
    /// @brief NotchedMarker constructor.
    /// @param quantiles Vector of quantiles structures to present.
    explicit NotchedMarker(QVector<Quantiles> quantiles);

    int rtti() const override;

    void draw(QPainter* painter, const QwtScaleMap& xMap,
              const QwtScaleMap& yMap, const QRectF& rect) const override;

    /// @brief Activate or disable drawing of legend.
    /// @param drawLegend Draw legend. True for drawing, false for not drawing.
    void setDrawLegend(bool drawLegend);

    /// @brief Check if legend is drawn.
    /// @return True if active, false if not active.
    bool getDrawLegend() const;

    /// @brief Set new vector of quantiles for present.
    /// @param quantilesVector Vector of quantiles.
    void setQuantiles(QVector<Quantiles> quantilesVector);

private:
    void initMarkerBrush();

    double calculateItemWidth(const QwtScaleMap& xMap) const;

    void drawElements(QPainter* p, const QwtScaleMap& xMap,
                      const QwtScaleMap& yMap) const;

    void drawLegend(QPainter* p, const QRectF& rect) const;

    struct ElementRecipe
    {
        double minY_{0.};
        double q10Y_{0.};
        double q25Y_{0.};
        double q50Y_{0.};
        double q75Y_{0.};
        double q90Y_{0.};
        double maxY_{0.};
        double meanY_{0.};
        double fromX_{0.};
        double toX_{0.};
    };

    void drawElement(QPainter* p, const ElementRecipe& recipe) const;
    static void drawElementUpperPart(QPainter* p, const ElementRecipe& recipe);
    void drawElementCenterPart(QPainter* p, const ElementRecipe& recipe) const;
    static void drawElementLowerPart(QPainter* p, const ElementRecipe& recipe);
    static void drawMeanCross(QPainter* p, const ElementRecipe& recipe);

    static ElementRecipe createElementRecipe(const QwtScaleMap& yMap,
                                             double centerX, double width,
                                             const Quantiles& quantiles);

    static void drawLegendTexts(QPainter* p, const ElementRecipe& recipe);

    static ElementRecipe createLegendRecipe(const QRectF& rect,
                                            int sectionHeight, double startY);

    static double calculateIndent(const ElementRecipe& recipe);

    static constexpr int LEGEND_SPACING{4};
    static constexpr double INDENT_FACTOR{0.25};

    QBrush markerBrush_;

    QVector<Quantiles> quantilesVector_;

    bool drawLegend_{false};
};
