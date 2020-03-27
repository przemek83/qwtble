#include "GroupPlot.h"

#include <QEvent>
#include <QToolTip>

#include "NotchedMarker.h"
#include "StringsScaleDraw.h"
#include "QwtBleUtilities.h"
#include "YAxisNumberPicker.h"

GroupPlot::GroupPlot(QWidget* parent)
    : PlotBase(tr("Grouping"), parent),
      marker_(new NotchedMarker({})), picker_(new YAxisNumberPicker(canvas()))
{
    setStdScaleDraw(yRight);

    marker_->attach(this);

    enableAxis(QwtPlot::yRight, true);

    setAxisScaleDraw(xBottom, new StringsScaleDraw({}));
    QFont font = axisFont(QwtPlot::xBottom);
    font.setStyleStrategy(QFont::PreferAntialias);
    setAxisFont(QwtPlot::xBottom, font);
}

GroupPlot::~GroupPlot() = default;

void GroupPlot::setNewData(QVector<Quantiles> quantilesVector,
                           QVector<QString> intervalStrings)
{
    tooltips_ = createTooltips(intervalStrings, quantilesVector);
    QVector<QString> shortIntervalNames =
        createAxisIntervalsNames(intervalStrings, quantilesVector);
    setAxisScaleDraw(xBottom,
                     new StringsScaleDraw(std::move(shortIntervalNames)));
    marker_->setQuantiles(std::move(quantilesVector));

    if (QToolTip::isVisible())
        QToolTip::hideText();

    replot();
}

QVector<QString>
GroupPlot::createAxisIntervalsNames(const QVector<QString>& intervalsNames,
                                    const QVector<Quantiles>& quantilesVector) const
{
    QVector<QString> shortenNames;
    const QString moreChars(QStringLiteral("..."));
    for (int i = 0; i < intervalsNames.size(); ++i)
    {
        QString name = intervalsNames[i];
        QString countString =
            QString(" (" + QString::number(quantilesVector[i].number_) + ")");

        if (name.size() + countString.count() > maxCharsInLabel_)
        {
            name.chop(name.size() - maxCharsInLabel_ + countString.count() +
                      moreChars.size());
            name.append(moreChars);
        }
        name.append(countString);
        shortenNames.append(name);
    }
    return shortenNames;
}

QVector<QString>
GroupPlot::createTooltips(const QVector<QString>& intervalsNames,
                          const QVector<Quantiles>& quantilesVector) const
{
    QVector<QString> tooltips;
    for (int i = 0; i < intervalsNames.size(); ++i)
        tooltips.append("<B>" + intervalsNames.at(i) +
                        "</B></BR>" +
                        quantilesVector.at(i).getValuesAsToolTip());
    return tooltips;
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
        const int x = picker_->getAreaOfMouse();
        if (x >= 1 && x <= tooltips_.size() && picker_->getMouseInWidget())
        {
            setToolTip(tooltips_[x - 1]);
        }
        else
        {
            setToolTip(QLatin1String(""));
            event->ignore();
            if (QToolTip::isVisible())
                QToolTip::hideText();
            return true;
        }
    }

    return PlotBase::event(event);
}
