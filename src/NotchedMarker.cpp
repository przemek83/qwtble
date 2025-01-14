#include <qwtble/NotchedMarker.h>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_div.h>
#include <qwt_scale_map.h>
#include <QPainter>
#include <QPainterPath>
#include <QVector>

#include <qwtble/Quantiles.h>
#include <qwtble/QwtBleUtilities.h>

NotchedMarker::NotchedMarker(QVector<Quantiles> quantiles)
    : quantilesVector_(std::move(quantiles))
{
    setZ(qwt_ble_utilities::HIGH_ORDER);
    setRenderHint(QwtPlotItem::RenderAntialiased, true);

    initMarkerBrush();
}

int NotchedMarker::rtti() const { return QwtPlotItem::Rtti_PlotUserItem; }

void NotchedMarker::draw(QPainter* painter, const QwtScaleMap& xMap,
                         const QwtScaleMap& yMap,
                         const QRectF& canvasRect) const
{
    if (quantilesVector_.empty() ||
        plot()->axisScaleDiv(QwtPlot::yLeft).isEmpty())
        return;

    painter->save();
    painter->setBrush(QBrush(Qt::red, Qt::NoBrush));
    if (drawLegend_)
        drawLegend(painter, canvasRect);
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
    whiteAlpha.setAlpha(qwt_ble_utilities::SMALL_TRANSPARENCY_FACTOR);
    QColor endAlpha(Qt::black);
    endAlpha.setAlpha(qwt_ble_utilities::BIG_TRANSPARENCY_FACTOR);
    gradient.setColorAt(0, whiteAlpha);
    gradient.setColorAt(1, endAlpha);
    markerBrush_ = QBrush(gradient);
}

double NotchedMarker::calculateItemWidth(const QwtScaleMap& xMap) const
{
    const QwtScaleDiv& scaleBottom{plot()->axisScaleDiv(QwtPlot::xBottom)};
    double width{xMap.pDist() / (scaleBottom.range() * 2)};

    // Item should take 90% of place.
    const double widthFactor{.9};
    width *= widthFactor;

    return width;
}

void NotchedMarker::drawElements(QPainter* p, const QwtScaleMap& xMap,
                                 const QwtScaleMap& yMap) const
{
    const double width{calculateItemWidth(xMap)};
    const int quantilesSize{static_cast<int>(quantilesVector_.size())};
    for (int i{0}; i < quantilesSize; ++i)
    {
        const Quantiles& quantiles{quantilesVector_[i]};
        const double centerX{xMap.transform(i + 1)};
        const ElementRecipe recipe{
            createElementRecipe(yMap, centerX, width, quantiles)};

        // If min = max draw only one line.
        if (qwt_ble_utilities::doublesAreEqual(quantiles.min_, quantiles.max_))
        {
            const double indent{calculateIndent(recipe)};
            p->drawLine(QPointF(recipe.fromX_ + indent, recipe.minY_),
                        QPointF(recipe.toX_ - indent, recipe.minY_));
        }
        else
        {
            drawElement(p, recipe);
        }
    }
}

void NotchedMarker::drawElementUpperPart(QPainter* p,
                                         const ElementRecipe& recipe)
{
    const double indent{calculateIndent(recipe)};
    const double centerX{(recipe.fromX_ + recipe.toX_) / 2};

    // Draw horizontal line for max.
    p->setPen(QPen(Qt::DotLine));
    p->drawLine(QPointF(recipe.fromX_ + indent, recipe.maxY_),
                QPointF(recipe.toX_ - indent, recipe.maxY_));

    // Draw horizontal line for q90.
    p->setPen(QPen(Qt::SolidLine));
    p->drawLine(QPointF(recipe.fromX_ + indent, recipe.q90Y_),
                QPointF(recipe.toX_ - indent, recipe.q90Y_));

    // Draw vertical line from q90 to q75.
    p->drawLine(QPointF(centerX, recipe.q90Y_), QPointF(centerX, recipe.q75Y_));
}

void NotchedMarker::drawElementCenterPart(QPainter* p,
                                          const ElementRecipe& recipe) const
{
    const double indent{calculateIndent(recipe)};
    const double notchFactor{0.85};
    QPainterPath path(QPoint(static_cast<int>(recipe.fromX_),
                             static_cast<int>(recipe.q25Y_)));
    path.lineTo(recipe.fromX_,
                recipe.q25Y_ - ((recipe.q25Y_ - recipe.q50Y_) * notchFactor));
    path.lineTo(recipe.fromX_ + indent, recipe.q50Y_);
    path.lineTo(recipe.fromX_,
                recipe.q75Y_ + ((recipe.q50Y_ - recipe.q75Y_) * notchFactor));
    path.lineTo(recipe.fromX_, recipe.q75Y_);
    path.lineTo(recipe.toX_, recipe.q75Y_);
    path.lineTo(recipe.toX_,
                recipe.q75Y_ + ((recipe.q50Y_ - recipe.q75Y_) * notchFactor));
    path.lineTo(recipe.toX_ - indent, recipe.q50Y_);
    path.lineTo(recipe.toX_,
                recipe.q25Y_ - ((recipe.q25Y_ - recipe.q50Y_) * notchFactor));
    path.lineTo(recipe.toX_, recipe.q25Y_);
    path.closeSubpath();
    p->fillPath(path, markerBrush_);
    p->drawPath(path);
}

void NotchedMarker::drawElementLowerPart(QPainter* p,
                                         const ElementRecipe& recipe)
{
    const double indent{calculateIndent(recipe)};
    const double centerX{(recipe.fromX_ + recipe.toX_) / 2};

    // Draw q50.
    p->drawLine(QPointF(recipe.fromX_ + indent, recipe.q50Y_),
                QPointF(recipe.toX_ - indent, recipe.q50Y_));

    // Draw vertical line from q25 to q10.
    p->drawLine(QPointF(centerX, recipe.q25Y_), QPointF(centerX, recipe.q10Y_));

    // Draw horizontal line for q10.
    p->drawLine(QPointF(recipe.fromX_ + indent, recipe.q10Y_),
                QPointF(recipe.toX_ - indent, recipe.q10Y_));

    // Draw horizontal line for min.
    p->setPen(QPen(Qt::DotLine));
    p->drawLine(QPointF(recipe.fromX_ + indent, recipe.minY_),
                QPointF(recipe.toX_ - indent, recipe.minY_));
    p->setPen(QPen(Qt::SolidLine));
}

void NotchedMarker::drawMeanCross(QPainter* p, const ElementRecipe& recipe)
{
    const double indent{calculateIndent(recipe)};
    const double centerX{(recipe.fromX_ + recipe.toX_) / 2};
    const double crossWidth{indent / 4};
    p->drawLine(QPointF(centerX - crossWidth, recipe.meanY_ - crossWidth),
                QPointF(centerX + crossWidth, recipe.meanY_ + crossWidth));
    p->drawLine(QPointF(centerX + crossWidth, recipe.meanY_ - crossWidth),
                QPointF(centerX - crossWidth, recipe.meanY_ + crossWidth));
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
    recipe.minY_ = yMap.transform(quantiles.min_);
    recipe.maxY_ = yMap.transform(quantiles.max_);
    recipe.q90Y_ = yMap.transform(quantiles.q90_);
    recipe.q75Y_ = yMap.transform(quantiles.q75_);
    recipe.q50Y_ = yMap.transform(quantiles.q50_);
    recipe.q25Y_ = yMap.transform(quantiles.q25_);
    recipe.q10Y_ = yMap.transform(quantiles.q10_);
    recipe.meanY_ = yMap.transform(quantiles.mean_);
    recipe.fromX_ = centerX - width;
    recipe.toX_ = centerX + width;
    return recipe;
}

void NotchedMarker::drawLegendTexts(QPainter* p, const ElementRecipe& recipe)
{
    // Place on x axis where legend text starts.
    const double textStartX{recipe.toX_ + LEGEND_SPACING};

    // Place on y axis where legend text starts.
    const double textStartY{recipe.meanY_ + LEGEND_SPACING};
    p->drawText(QPointF(textStartX, textStartY), QObject::tr("mean"));
    p->drawText(QPointF(textStartX, recipe.maxY_ + LEGEND_SPACING),
                QStringLiteral("max"));
    p->drawText(QPointF(textStartX, recipe.q90Y_ + LEGEND_SPACING),
                QStringLiteral("Q90"));
    p->drawText(QPointF(textStartX, recipe.q75Y_ + LEGEND_SPACING),
                QStringLiteral("Q75"));
    p->drawText(QPointF(textStartX, recipe.q50Y_ + LEGEND_SPACING),
                QStringLiteral("Q50"));
    p->drawText(QPointF(textStartX, recipe.q25Y_ + LEGEND_SPACING),
                QStringLiteral("Q25"));
    p->drawText(QPointF(textStartX, recipe.q10Y_ + LEGEND_SPACING),
                QStringLiteral("Q10"));
    p->drawText(QPointF(textStartX, recipe.minY_ + LEGEND_SPACING),
                QStringLiteral("min"));
}

NotchedMarker::ElementRecipe NotchedMarker::createLegendRecipe(
    const QRectF& rect, int sectionHeight, double startY)
{
    ElementRecipe recipe;
    const int width{4 * LEGEND_SPACING};
    recipe.meanY_ = startY;
    int elementNumber{0};
    ++elementNumber;
    recipe.maxY_ = startY + (elementNumber * sectionHeight);
    ++elementNumber;
    recipe.q90Y_ = startY + (elementNumber * sectionHeight);
    ++elementNumber;
    recipe.q75Y_ = startY + (elementNumber * sectionHeight);
    ++elementNumber;
    recipe.q50Y_ = startY + (elementNumber * sectionHeight);
    ++elementNumber;
    recipe.q25Y_ = startY + (elementNumber * sectionHeight);
    ++elementNumber;
    recipe.q10Y_ = startY + (elementNumber * sectionHeight);
    ++elementNumber;
    recipe.minY_ = startY + (elementNumber * sectionHeight);
    recipe.fromX_ = rect.x() + LEGEND_SPACING;
    recipe.toX_ = recipe.fromX_ + width;
    return recipe;
}

double NotchedMarker::calculateIndent(const ElementRecipe& recipe)
{
    return (recipe.toX_ - recipe.fromX_) * INDENT_FACTOR;
}

void NotchedMarker::drawLegend(QPainter* p, const QRectF& rect) const
{
    // Size of single part of legend.
    const int sectionHeight{5 * LEGEND_SPACING};

    // Top y axis point from where legend starts.
    const double startY{rect.y() + (2 * LEGEND_SPACING)};
    const ElementRecipe recipe{createLegendRecipe(rect, sectionHeight, startY)};
    drawElement(p, recipe);
    drawLegendTexts(p, recipe);
}
