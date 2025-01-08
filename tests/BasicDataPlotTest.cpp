#include "BasicDataPlotTest.h"

#include <QTest>
#include "qwt_legend.h"
#include "qwt_legend_label.h"
#include "qwt_plot_item.h"

#include <qwtble/BasicDataPlot.h>

#include "Common.h"

namespace
{
QVector<QPointF> getData()
{
    const QVector<double> prices{common::getPrices()};
    const QVector<double> dates{common::getDates()};
    QVector<QPointF> data;
    data.reserve(prices.size());
    for (int i = 0; i < prices.size(); ++i)
        data.append({dates[i], prices[i]});
    return data;
}

Quantiles getQuantiles()
{
    Quantiles quantiles;
    const QVector<double> prices{common::getPrices()};
    quantiles.init(prices);
    const QVector<double> dates{common::getDates()};
    const auto [min, max] = std::minmax_element(dates.cbegin(), dates.cend());
    quantiles.minX_ = *min;
    quantiles.maxX_ = *max;
    return quantiles;
}

std::pair<double, double> getMinMaxDates()
{
    const QVector<double> dates{common::getDates()};
    const auto [min, max]{std::minmax_element(dates.cbegin(), dates.cend())};
    return {*min, *max};
}

void preparePlot(BasicDataPlot& plot)
{
    const auto [min, max]{getMinMaxDates()};
    plot.setAxisScale(QwtPlot::xBottom, min, max);

    const QVector<QPointF> regressionPoints{{min, 38.002}, {max, 78.4491}};
    const QVector<QPointF> data{getData()};
    Quantiles quantiles{getQuantiles()};
    plot.setNewData(data, quantiles, regressionPoints);
    plot.resize(800, 600);
}

void checkPlot(BasicDataPlot& plot, QString expectedPath)
{
    QImage actual{plot.grab().toImage()};
    QImage expected(expectedPath);
    expected = expected.convertToFormat(actual.format());
    QCOMPARE(actual, expected);
}
}  // namespace

void BasicDataPlotTest::testPlotWithData()
{
    BasicDataPlot plot;
    preparePlot(plot);
    const QString expectedPath{
        QString::fromLatin1(":/res/BasicDataPlotDefault.png")};
    checkPlot(plot, expectedPath);
}

void BasicDataPlotTest::testPlotWithoutData()
{
    const QVector<QPointF> regressionPoints{{0, 0}, {0, 0}};
    Quantiles quantiles;
    BasicDataPlot plot;
    plot.setNewData({}, quantiles, regressionPoints);
    plot.resize(800, 600);

    const QString expectedPath{
        QString::fromLatin1(":/res/BasicDataPlotEmpty.png")};
    checkPlot(plot, expectedPath);
}

void BasicDataPlotTest::testLegendItemsChecking()
{
    BasicDataPlot plot;
    preparePlot(plot);

    auto* legend{::qobject_cast<QwtLegend*>(plot.legend())};
    legend->checked(common::getItemInfo(plot, "Q25"), false, 0);

    const QString expectedPath{
        QString::fromLatin1(":/res/BasicDataPlotItemChecked.png")};
    checkPlot(plot, expectedPath);
}
