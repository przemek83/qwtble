﻿#include "GroupPlot.h"

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

void GroupPlot::setNewData(const QVector<Quantiles>& quantiles,
                           QVector<QString>& intervalStrings)
{
    quantiles_.clear();
    quantiles_ = quantiles;
    longIntervalNames_ = intervalStrings;
    shortenIntervalsNamesIfNeeded(intervalStrings, quantiles_);
    shortIntervalNames_ = intervalStrings;

    //No leak here.
    setAxisScaleDraw(xBottom, new StringsScaleDraw(&shortIntervalNames_));

    if (QToolTip::isVisible())
    {
        QToolTip::hideText();
    }

    replot();
}

void GroupPlot::shortenIntervalsNamesIfNeeded(QVector<QString>& intervalsNames,
                                              const QVector<Quantiles>& quantilesForIntervals)
{
    for (int i = 0; i < intervalsNames.size(); ++i)
    {
        const QString moreChars(QStringLiteral("..."));
        QString count =
            QString(" (" + QString::number(quantilesForIntervals[i].number_) + ")");

        if (intervalsNames[i].size() - maxCharsInLabel_ + count.count() > 0)
        {
            intervalsNames[i].chop(intervalsNames[i].size() -
                                   maxCharsInLabel_ +
                                   count.count() +
                                   moreChars.size());
            intervalsNames[i].append(moreChars);
        }
        intervalsNames[i].append(count);
    }
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
