#include "Quantiles.h"

#include <cmath>

#include <QDebug>

#include "QwtBleUtilities.h"

void Quantiles::clear()
{
    min_ = .0;
    q10_ = .0;
    q25_ = .0;
    q50_ = .0;
    q75_ = .0;
    q90_ = .0;
    max_ = .0;

    number_ = 0;
    avg_ = .0;
    stdDev_ = .0;

    minX_ = .0;
    maxX_ = .0;
}

void Quantiles::print()
{
    qDebug() << "min " << min_ << " q10 = " << q10_ << " q25_ = " << q25_ << \
             " q50 = " << q50_ << " q75 = " << q75_ << " q90 = " << q90_ << \
             " max = " << max_ << " number = " << number_ << " avg = " << \
             avg_ << " std dev = " << stdDev_ <<  " minX = " << minX_ << \
             " maxX = " << maxX_;
}

void Quantiles::computeQuantiles(QVector<double>& valuePerUnit)
{
    double EX = 0;
    double EX2 = 0;

    clear();

    number_ = valuePerUnit.count();

    for (auto pricePerMeter : valuePerUnit)
    {
        if (min_ > pricePerMeter || QwtBleUtilities::doublesAreEqual(min_, 0.))
            min_ = pricePerMeter;

        if (max_ < pricePerMeter || QwtBleUtilities::doublesAreEqual(max_, 0.))
            max_ = pricePerMeter;

        EX += pricePerMeter;
        EX2 += pricePerMeter * pricePerMeter;
    }

    EX /= number_;
    EX2 /= number_;

    if (number_ > 1)
        stdDev_ = sqrt(EX2 - EX * EX);
    else
        stdDev_ = .0;

    avg_ = EX;

    if (stdDev_ <= 0)
        return;

    qSort(valuePerUnit);

    if (number_ < 2)
    {
        double tmp = (number_ != 0 ? valuePerUnit.at(0) : 0);
        q10_ = tmp;
        q25_ = tmp;
        q50_ = tmp;
        q75_ = tmp;
        q90_ = tmp;
    }
    else
    {
        const double q10Level {0.1};
        double tmp = (number_ - 1) * q10Level;
        q10_ = valuePerUnit.at(static_cast<int>(floor(tmp))) + (tmp - floor(tmp)) *
               (valuePerUnit.at(static_cast<int>(ceil(tmp))) - valuePerUnit.at(static_cast<int>(floor(tmp))));

        const double q25Level {0.25};
        tmp = (number_ - 1) * q25Level;
        q25_ = valuePerUnit.at(static_cast<int>(floor(tmp))) + (tmp - floor(tmp)) *
               (valuePerUnit.at(static_cast<int>(ceil(tmp))) - valuePerUnit.at(static_cast<int>(floor(tmp))));

        const double q50Level {0.5};
        tmp = (number_ - 1) * q50Level;
        q50_ = valuePerUnit.at(static_cast<int>(floor(tmp))) + (tmp - floor(tmp)) *
               (valuePerUnit.at(static_cast<int>(ceil(tmp))) - valuePerUnit.at(static_cast<int>(floor(tmp))));

        const double q75Level {0.75};
        tmp = (number_ - 1) * q75Level;
        q75_ = valuePerUnit.at(static_cast<int>(floor(tmp))) + (tmp - floor(tmp)) *
               (valuePerUnit.at(static_cast<int>(ceil(tmp))) - valuePerUnit.at(static_cast<int>(floor(tmp))));

        const double q90Level {0.9};
        tmp = (number_ - 1) * q90Level;
        q90_ = valuePerUnit.at(static_cast<int>(floor(tmp))) + (tmp - floor(tmp)) *
               (valuePerUnit.at(static_cast<int>(ceil(tmp))) - valuePerUnit.at(static_cast<int>(floor(tmp))));
    }
}

QString Quantiles::getValuesAsToolTip() const
{
    QString toolTipText;
    toolTipText.append(QLatin1String("<table>"));
    toolTipText += valueAsHtmlRow(PLOT_INFO_COUNT, number_);
    toolTipText += valueAsHtmlRow(PLOT_INFO_AVG, avg_);
    toolTipText += valueAsHtmlRow(PLOT_INFO_MAX, max_);

    if (number_ > 1)
    {
        toolTipText += valueAsHtmlRow(PLOT_INFO_Q90, q90_);
        toolTipText += valueAsHtmlRow(PLOT_INFO_Q75, q75_);
        toolTipText += valueAsHtmlRow(PLOT_INFO_Q50, q50_);
        toolTipText += valueAsHtmlRow(PLOT_INFO_Q25, q25_);
        toolTipText += valueAsHtmlRow(PLOT_INFO_Q10, q10_);
    }

    toolTipText += valueAsHtmlRow(PLOT_INFO_MIN, min_);

    if (number_ > 1)
        toolTipText += valueAsHtmlRow(PLOT_INFO_STD_DEV, stdDev_);

    toolTipText.append(QLatin1String("</table>"));

    return toolTipText;
}

std::array<QString, Quantiles::PLOT_INFO_END> Quantiles::getPlotInfoNames()
{
    std::array<QString, PLOT_INFO_END> plotInfoNames;
    plotInfoNames[PLOT_INFO_COUNT] =
        QObject::tr("Data count") + QLatin1Char(':');
    plotInfoNames[PLOT_INFO_MIN] = QStringLiteral("Minimum");
    plotInfoNames[PLOT_INFO_Q10] = QStringLiteral("Q10");
    plotInfoNames[PLOT_INFO_Q25] = QStringLiteral("Q25");
    plotInfoNames[PLOT_INFO_Q50] = QStringLiteral("Q50");
    plotInfoNames[PLOT_INFO_Q75] = QStringLiteral("Q75");
    plotInfoNames[PLOT_INFO_Q90] = QStringLiteral("Q90");
    plotInfoNames[PLOT_INFO_MAX] = QStringLiteral("Maximum");
    plotInfoNames[PLOT_INFO_AVG] = QObject::tr("Average");
    plotInfoNames[PLOT_INFO_STD_DEV] = QObject::tr("Std. deviation");
    return plotInfoNames;
}

QString Quantiles::valueAsHtmlRow(PlotInfo name, double value)
{
    static std::array<QString, PLOT_INFO_END> plotInfoNames = getPlotInfoNames();
    QString html(QStringLiteral("<tr><td>"));
    html.append(plotInfoNames.at(static_cast<size_t>(name)));
    html.append(QLatin1String("</td><td ALIGN=RIGHT>"));
    int precision = (PLOT_INFO_COUNT == name ? 0 : 2);
    html.append(QwtBleUtilities::doubleToStringUsingLocale(value, precision));
    html.append(QLatin1String("</td></tr>\n"));

    return html;
}
