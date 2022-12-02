#include "NotchedMarker.h"

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_div.h>
#include <qwt_scale_map.h>
#include <QPainter>
#include <QPainterPath>
#include <QVector>

#include "Quantiles.h"
#include "QwtBleUtilities.h"

NotchedMarker::NotchedMarker(QVector<Quantiles> quantiles)
    : quantilesVector_(std::move(quantiles))
{
    setZ(QwtBleUtilities::HIGH_ORDER);
    setRenderHint(QwtPlotItem::RenderAntialiased, true);

    initMarkerBrush();
}

int NotchedMarker::rtti() const { return QwtPlotItem::Rtti_PlotUserItem; }

void NotchedMarker::draw(QPainter* painter, const QwtScaleMap& xMap,
                         const QwtScaleMap& yMap, const QRectF& rect) const
{
    if (quantilesVector_.empty() ||
        plot()->axisScaleDiv(QwtPlot::yLeft).isEmpty())
        return;

    painter->save();
    painter->setBrush(QBrush(Qt::red, Qt::NoBrush));
    if (drawLegend_)
        drawLegend(painter, rect);
    drawElements(painter, xMap, yMap);
    painter->restore();
}

void NotchedMarker::setDrawLegend(bool drawLegend) { drawLegend_ = drawLegend; }

bool NotchedMarker::getDrawLegend() const { return drawLegend_; }

void NotchedMarker::setQuantiles(QVector<Quantiles> quantilesVector)
{
    quantilesVector_ = std::move(quantilesVector);
}

void NotchedMarker::initMarkerBrush()
{
    QLinearGradient gradient;
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    QColor whiteAlpha(Qt::white);
    whiteAlpha.setAlpha(QwtBleUtilities::SMALL_TRANSPARENCY_FACTOR);
    QColor endAlpha(Qt::black);
    endAlpha.setAlpha(QwtBleUtilities::BIG_TRANSPARENCY_FACTOR);
    gradient.setColorAt(0, whiteAlpha);
    gradient.setColorAt(1, endAlpha);
    markerBrush_ = QBrush(gradient);
}

double NotchedMarker::calculateItemWidth(const QwtScaleMap& xMap) const
{
    const QwtScaleDiv& scaleBottom = plot()->axisScaleDiv(QwtPlot::xBottom);
    double width = xMap.pDist() / (scaleBottom.range() * 2);

    // Item should take 90% of place.
    const double widthFactor{.9};
    width *= widthFactor;

    return width;
}

void NotchedMarker::drawElements(QPainter* p, const QwtScaleMap& xMap,
                                 const QwtScaleMap& yMap) const
{
    const double width{calculateItemWidth(xMap)};
    for (int i = 0; i < quantilesVector_.size(); ++i)
    {
        const Quantiles& quantiles = quantilesVector_[i];
        const double centerX = xMap.transform(i + 1);
        const ElementRecipe recipe{
            createElementRecipe(yMap, centerX, width, quantiles)};

        // If min = max draw only one line.
        if (QwtBleUtilities::doublesAreEqual(quantiles.min_, quantiles.max_))
        {
            const double indent{calculateIndent(recipe)};
            p->drawLine(QPointF(recipe.fromX + indent, recipe.minY),
                        QPointF(recipe.toX - indent, recipe.minY));
            continue;
        }
        drawElement(p, recipe);
    }
}

void NotchedMarker::drawElementUpperPart(QPainter* p,
                                         const ElementRecipe& recipe) const
{
    const double indent{calculateIndent(recipe)};
    const double centerX = (recipe.fromX + recipe.toX) / 2;

    // Draw horizontal line for max.
    p->setPen(QPen(Qt::DotLine));
    p->drawLine(QPointF(recipe.fromX + indent, recipe.maxY),
                QPointF(recipe.toX - indent, recipe.maxY));

    // Draw horizontal line for q90.
    p->setPen(QPen(Qt::SolidLine));
    p->drawLine(QPointF(recipe.fromX + indent, recipe.q90Y),
                QPointF(recipe.toX - indent, recipe.q90Y));

    // Draw vertical line from q90 to q75.
    p->drawLine(QPointF(centerX, recipe.q90Y), QPointF(centerX, recipe.q75Y));
}

void NotchedMarker::drawElementCenterPart(QPainter* p,
                                          const ElementRecipe& recipe) const
{
    const double indent{calculateIndent(recipe)};
    const double notchFactor = 0.85;
    QPainterPath path(
        QPoint(static_cast<int>(recipe.fromX), static_cast<int>(recipe.q25Y)));
    path.lineTo(recipe.fromX,
                recipe.q25Y - (recipe.q25Y - recipe.q50Y) * notchFactor);
    path.lineTo(recipe.fromX + indent, recipe.q50Y);
    path.lineTo(recipe.fromX,
                recipe.q75Y + (recipe.q50Y - recipe.q75Y) * notchFactor);
    path.lineTo(recipe.fromX, recipe.q75Y);
    path.lineTo(recipe.toX, recipe.q75Y);
    path.lineTo(recipe.toX,
                recipe.q75Y + (recipe.q50Y - recipe.q75Y) * notchFactor);
    path.lineTo(recipe.toX - indent, recipe.q50Y);
    path.lineTo(recipe.toX,
                recipe.q25Y - (recipe.q25Y - recipe.q50Y) * notchFactor);
    path.lineTo(recipe.toX, recipe.q25Y);
    path.closeSubpath();
    p->fillPath(path, markerBrush_);
    p->drawPath(path);
}

void NotchedMarker::drawElementLowerPart(QPainter* p,
                                         const ElementRecipe& recipe) const
{
    const double indent{calculateIndent(recipe)};
    const double centerX = (recipe.fromX + recipe.toX) / 2;

    // Draw q50.
    p->drawLine(QPointF(recipe.fromX + indent, recipe.q50Y),
                QPointF(recipe.toX - indent, recipe.q50Y));

    // Draw vertical line from q25 to q10.
    p->drawLine(QPointF(centerX, recipe.q25Y), QPointF(centerX, recipe.q10Y));

    // Draw horizontal line for q10.
    p->drawLine(QPointF(recipe.fromX + indent, recipe.q10Y),
                QPointF(recipe.toX - indent, recipe.q10Y));

    // Draw horizontal line for min.
    p->setPen(QPen(Qt::DotLine));
    p->drawLine(QPointF(recipe.fromX + indent, recipe.minY),
                QPointF(recipe.toX - indent, recipe.minY));
    p->setPen(QPen(Qt::SolidLine));
}

void NotchedMarker::drawMeanCross(QPainter* p,
                                  const ElementRecipe& recipe) const
{
    const double indent{calculateIndent(recipe)};
    const double centerX = (recipe.fromX + recipe.toX) / 2;
    const double crossWidth{indent / 4};
    p->drawLine(QPointF(centerX - crossWidth, recipe.meanY - crossWidth),
                QPointF(centerX + crossWidth, recipe.meanY + crossWidth));
    p->drawLine(QPointF(centerX + crossWidth, recipe.meanY - crossWidth),
                QPointF(centerX - crossWidth, recipe.meanY + crossWidth));
}

void NotchedMarker::drawElement(QPainter* p, const ElementRecipe& recipe) const
{
    drawElementUpperPart(p, recipe);
    drawElementCenterPart(p, recipe);
    drawElementLowerPart(p, recipe);
    drawMeanCross(p, recipe);
}

NotchedMarker::ElementRecipe NotchedMarker::createElementRecipe(
    const QwtScaleMap& yMap, double centerX, double width,
    const Quantiles& quantiles)
{
    ElementRecipe recipe;
    recipe.minY = yMap.transform(quantiles.min_);
    recipe.maxY = yMap.transform(quantiles.max_);
    recipe.q90Y = yMap.transform(quantiles.q90_);
    recipe.q75Y = yMap.transform(quantiles.q75_);
    recipe.q50Y = yMap.transform(quantiles.q50_);
    recipe.q25Y = yMap.transform(quantiles.q25_);
    recipe.q10Y = yMap.transform(quantiles.q10_);
    recipe.meanY = yMap.transform(quantiles.mean_);
    recipe.fromX = centerX - width;
    recipe.toX = centerX + width;
    return recipe;
}

void NotchedMarker::drawLegendTexts(QPainter* p, const ElementRecipe& recipe)
{
    // Place on x axis where legend text starts.
    const double textStartX = recipe.toX + LEGEND_SPACING;

    // Place on y axis where legend text starts.
    const double textStartY = recipe.meanY + LEGEND_SPACING;
    p->drawText(QPointF(textStartX, textStartY), QObject::tr("mean"));
    p->drawText(QPointF(textStartX, recipe.maxY + LEGEND_SPACING),
                QStringLiteral("max"));
    p->drawText(QPointF(textStartX, recipe.q90Y + LEGEND_SPACING),
                QStringLiteral("Q90"));
    p->drawText(QPointF(textStartX, recipe.q75Y + LEGEND_SPACING),
                QStringLiteral("Q75"));
    p->drawText(QPointF(textStartX, recipe.q50Y + LEGEND_SPACING),
                QStringLiteral("Q50"));
    p->drawText(QPointF(textStartX, recipe.q25Y + LEGEND_SPACING),
                QStringLiteral("Q25"));
    p->drawText(QPointF(textStartX, recipe.q10Y + LEGEND_SPACING),
                QStringLiteral("Q10"));
    p->drawText(QPointF(textStartX, recipe.minY + LEGEND_SPACING),
                QStringLiteral("min"));
}

NotchedMarker::ElementRecipe NotchedMarker::createLegendRecipe(
    const QRectF& rect, int sectionHeight, double startY)
{
    ElementRecipe recipe;
    const int width = 4 * LEGEND_SPACING;
    recipe.meanY = startY;
    int elementNumber{0};
    recipe.maxY = startY + ++elementNumber * sectionHeight;
    recipe.q90Y = startY + ++elementNumber * sectionHeight;
    recipe.q75Y = startY + ++elementNumber * sectionHeight;
    recipe.q50Y = startY + ++elementNumber * sectionHeight;
    recipe.q25Y = startY + ++elementNumber * sectionHeight;
    recipe.q10Y = startY + ++elementNumber * sectionHeight;
    recipe.minY = startY + ++elementNumber * sectionHeight;
    recipe.fromX = rect.x() + LEGEND_SPACING;
    recipe.toX = recipe.fromX + width;
    return recipe;
}

double NotchedMarker::calculateIndent(const ElementRecipe& recipe)
{
    return (recipe.toX - recipe.fromX) * INDENT_FACTOR;
}

void NotchedMarker::drawLegend(QPainter* p, const QRectF& rect) const
{
    // Size of single part of legend.
    const int sectionHeight = 5 * LEGEND_SPACING;

    // Top y axis point from where legend starts.
    const double startY = rect.y() + 2 * LEGEND_SPACING;
    const ElementRecipe recipe{createLegendRecipe(rect, sectionHeight, startY)};
    drawElement(p, recipe);
    drawLegendTexts(p, recipe);
}
