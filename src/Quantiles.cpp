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

double Quantiles::calculateStdDev(int count, double ex, double ex2)
{
    if (count > 1)
        return ::sqrt(ex2 - (ex * ex));
    return .0;
}

double Quantiles::computeQuantile(const QVector<double>& values,
                                  double interval)
{
    int lowerIndex{static_cast<int>(::floor(interval))};
    int upperIndex{static_cast<int>(::ceil(interval))};
    double lowerValue{values.at(lowerIndex)};
    double upperValue{values.at(upperIndex)};
    double fraction{interval - ::floor(interval)};
    return lowerValue + (fraction * (upperValue - lowerValue));
}

void Quantiles::setQuantiles(const QVector<double>& values)
{
    const int count{static_cast<int>(values.size())};

    const double q10Level{0.1};
    double currentInterval{(count - 1) * q10Level};
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

std::tuple<double, double> Quantiles::calculateEXAndEX2(
    const QVector<double>& values) const
{
    double ex{0};
    double ex2{0};
    for (auto value : values)
    {
        ex += value;
        ex2 += value * value;
    }
    ex /= count_;
    ex2 /= count_;
    return {ex, ex2};
}

void Quantiles::init(QVector<double> values)
{
    clear();

    if (values.empty())
        return;

    count_ = static_cast<int>(values.count());

    std::sort(values.begin(), values.end());
    min_ = values.front();
    max_ = values.back();

    auto [ex, ex2]{calculateEXAndEX2(values)};
    mean_ = ex;
    stdDev_ = calculateStdDev(count_, ex, ex2);
    if (stdDev_ <= 0)
        return;

    setQuantiles(values);
}

QString Quantiles::getValuesAsToolTip() const
{
    QString toolTipText;
    toolTipText.append(QStringLiteral("<table>"));
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

    toolTipText.append(QStringLiteral("</table>"));

    return toolTipText;
}

std::array<QString, Quantiles::PLOT_INFO_END> Quantiles::getPlotInfoNames()
{
    std::array<QString, PLOT_INFO_END> plotInfoNames;
    plotInfoNames[PLOT_INFO_COUNT] =
        QObject::tr("Data count") + QStringLiteral(":");
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
    const std::array<QString, PLOT_INFO_END> plotInfoNames{getPlotInfoNames()};
    QString html{QStringLiteral("<tr><td>")};
    html.append(plotInfoNames.at(static_cast<size_t>(name)));
    html.append(QStringLiteral("</td><td ALIGN=RIGHT>"));
    int precision{2};
    if (name == PLOT_INFO_COUNT)
        precision = 0;
    html.append(qwt_ble_utilities::doubleToStringUsingLocale(value, precision));
    html.append(QStringLiteral("</td></tr>\n"));

    return html;
}
