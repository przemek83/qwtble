#include "Zoomer.h"

#include <QWheelEvent>

#include "Utilities.h"

Zoomer::Zoomer(QwtPlotCanvas* canvas):
    QwtPlotZoomer(canvas)
{
    setTrackerMode(AlwaysOn);

    // LeftButton for the zooming
    // MidButton for the panning
    // RightButton: zoom out by 1
    // Ctrl+RighButton: zoom out to full size

    setMousePattern(QwtEventPattern::MouseSelect2,
                    Qt::RightButton, Qt::ControlModifier);

    setMousePattern(QwtEventPattern::MouseSelect3,
                    Qt::RightButton);

    const QColor c(Qt::darkBlue);
    setRubberBandPen(c);
    setTrackerPen(c);
}

QwtText Zoomer::trackerTextF(const QPointF& pos) const
{
    QColor bg(Qt::white);
    bg.setAlpha(Utilities::SMALL_TRANSPARENCY_FACTOR);

    QwtText text = QwtPlotZoomer::trackerTextF(pos);
    text.setBackgroundBrush(QBrush(bg));
    return text;
}

void Zoomer::widgetWheelEvent(QWheelEvent* event)
{
    zoom((event->delta() > 0 ? 1 : -1));
    event->accept();
}

void Zoomer::restart()
{
    reset();
}
