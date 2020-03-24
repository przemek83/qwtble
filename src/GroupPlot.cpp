#include "GroupPlot.h"

#include <QDebug>
#include <QToolTip>
#include <qwt_plot_layout.h>

#include "NotchedMarker.h"
#include "StringsScaleDraw.h"
#include "QwtBleUtilities.h"
#include "YAxisNumberPicker.h"

GroupPlot::GroupPlot(QWidget* parent)
    : PlotBase(tr("Grouping"), parent),
      marker_(new NotchedMarker(&quantiles_)),
      picker_(new YAxisNumberPicker(canvas()))
{
    quantiles_.clear();

    setStdScaleDraw(yRight);
    setAxisScaleDraw(xBottom, new StringsScaleDraw(&shortIntervalNames_));

    marker_->attach(this);

    //Font.
    enableAxis(QwtPlot::yRight, true);
    QFont font = axisFont(QwtPlot::xBottom);
    font.setStyleStrategy(QFont::PreferAntialias);
    setAxisFont(QwtPlot::xBottom, font);
}

GroupPlot::~GroupPlot() = default;

void GroupPlot::setNewData(QVector<Quantiles> quantiles,
                           QVector<QString> intervalStrings)
{
    quantiles_ = std::move(quantiles);
    longIntervalNames_ = std::move(intervalStrings);
    shortIntervalNames_ = shortenIntervalsNamesIfNeeded(longIntervalNames_, quantiles_);

    //No leak here.
    setAxisScaleDraw(xBottom, new StringsScaleDraw(&shortIntervalNames_));

    if (QToolTip::isVisible())
        QToolTip::hideText();

    replot();
}

QVector<QString>
GroupPlot::shortenIntervalsNamesIfNeeded(const QVector<QString>& intervalsNames,
                                         const QVector<Quantiles>& quantilesForIntervals)
{
    QVector<QString> shortenNames;
    const QString moreChars(QStringLiteral("..."));
    for (int i = 0; i < intervalsNames.size(); ++i)
    {
        QString name = intervalsNames[i];
        QString countString =
            QString(" (" + QString::number(quantilesForIntervals[i].number_) + ")");

        if (name.size() - maxCharsInLabel_ + countString.count() > 0)
        {
            name.chop(name.size() -
                      maxCharsInLabel_ +
                      countString.count() +
                      moreChars.size());
            name.append(moreChars);
        }
        name.append(countString);
        shortenNames.append(name);
    }
    return shortenNames;
}

QSize GroupPlot::minimumSizeHint() const
{
    const int minimumWidth {150};
    const int minimumHeight {100};
    return QSize(minimumWidth, minimumHeight);
}

bool GroupPlot::event(QEvent* event)
{
    if (event->type() == QEvent::ToolTip)
    {
        int x =  picker_->getAreaOfMouse();
        if (x >= 1 && x <= quantiles_.size() && picker_->getMouseInWidget())
        {
            setToolTip("<B>" + longIntervalNames_.at(x - 1) +
                       "</B></BR>" + quantiles_.at(x - 1).getValuesAsToolTip());
        }
        else
        {
            setToolTip(QLatin1String(""));
            event->ignore();
            if (QToolTip::isVisible())
            {
                QToolTip::hideText();
            }
            return true;
        }
    }

    return PlotBase::event(event);
}
