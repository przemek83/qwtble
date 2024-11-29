#include <qwtble/Quantiles.h>

#include <cmath>

#include <QObject>

#include <qwtble/QwtBleUtilities.h>

void Quantiles::clear()
{
    min_ = .0;
    q10_ = .0;
    q25_ = .0;
    q50_ = .0;
    q75_ = .0;
    q90_ = .0;
    max_ = .0;
    count_ = 0;
    mean_ = .0;
    stdDev_ = .0;
    minX_ = .0;
    maxX_ = .0;
}

double Quantiles::calculateStdDev(int count, double EX, double EX2)
{
    if (count > 1)
        return sqrt(EX2 - EX * EX);
    return .0;
}

double Quantiles::computeQuantile(const QVector<double>& values,
                                  double interval)
{
    return values.at(static_cast<int>(floor(interval))) +
           (interval - floor(interval)) *
               (values.at(static_cast<int>(ceil(interval))) -
                values.at(static_cast<int>(floor(interval))));
}

void Quantiles::setQuantiles(const QVector<double>& values)
{
    const int count{static_cast<int>(values.size())};
    if (count <= 1)
    {
        const double value = values.front();
        q10_ = value;
        q25_ = value;
        q50_ = value;
        q75_ = value;
        q90_ = value;
    }
    else
    {
        const double q10Level{0.1};
        double currentInterval = (count - 1) * q10Level;
        q10_ = computeQuantile(values, currentInterval);

        const double q25Level{0.25};
        currentInterval = (count - 1) * q25Level;
        q25_ = computeQuantile(values, currentInterval);

        const double q50Level{0.5};
        currentInterval = (count - 1) * q50Level;
        q50_ = computeQuantile(values, currentInterval);

        const double q75Level{0.75};
        currentInterval = (count - 1) * q75Level;
        q75_ = computeQuantile(values, currentInterval);

        const double q90Level{0.9};
        currentInterval = (count - 1) * q90Level;
        q90_ = computeQuantile(values, currentInterval);
    }
}

std::tuple<double, double> Quantiles::calculateEXAndEX2(
    const QVector<double>& values)
{
    double EX = 0;
    double EX2 = 0;
    for (auto value : values)
    {
        EX += value;
        EX2 += value * value;
    }
    EX /= count_;
    EX2 /= count_;
    return {EX, EX2};
}

void Quantiles::init(QVector<double> values)
{
    clear();

    if (values.empty())
        return;

    count_ = values.count();

    std::sort(values.begin(), values.end());
    min_ = values.front();
    max_ = values.back();

    auto [EX, EX2] = calculateEXAndEX2(values);
    mean_ = EX;
    stdDev_ = calculateStdDev(values.count(), EX, EX2);
    if (stdDev_ <= 0)
        return;

    setQuantiles(values);
}

QString Quantiles::getValuesAsToolTip() const
{
    QString toolTipText;
    toolTipText.append(QLatin1String("<table>"));
    toolTipText += valueAsHtmlRow(PLOT_INFO_COUNT, count_);
    toolTipText += valueAsHtmlRow(PLOT_INFO_MEAN, mean_);
    toolTipText += valueAsHtmlRow(PLOT_INFO_MAX, max_);

    if (count_ > 1)
    {
        toolTipText += valueAsHtmlRow(PLOT_INFO_Q90, q90_);
        toolTipText += valueAsHtmlRow(PLOT_INFO_Q75, q75_);
        toolTipText += valueAsHtmlRow(PLOT_INFO_Q50, q50_);
        toolTipText += valueAsHtmlRow(PLOT_INFO_Q25, q25_);
        toolTipText += valueAsHtmlRow(PLOT_INFO_Q10, q10_);
    }

    toolTipText += valueAsHtmlRow(PLOT_INFO_MIN, min_);

    if (count_ > 1)
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
    plotInfoNames[PLOT_INFO_MEAN] = QObject::tr("Average");
    plotInfoNames[PLOT_INFO_STD_DEV] = QObject::tr("Std. deviation");
    return plotInfoNames;
}

QString Quantiles::valueAsHtmlRow(PlotInfo name, double value)
{
    static std::array<QString, PLOT_INFO_END> plotInfoNames =
        getPlotInfoNames();
    QString html(QStringLiteral("<tr><td>"));
    html.append(plotInfoNames.at(static_cast<size_t>(name)));
    html.append(QLatin1String("</td><td ALIGN=RIGHT>"));
    const int precision = (PLOT_INFO_COUNT == name ? 0 : 2);
    html.append(QwtBleUtilities::doubleToStringUsingLocale(value, precision));
    html.append(QLatin1String("</td></tr>\n"));

    return html;
}
