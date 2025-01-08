#include "HistogramPlotTest.h"

#include <QTest>
#include "qwt_legend.h"
#include "qwt_legend_label.h"
#include "qwt_plot_item.h"

#include <qwtble/HistogramPlot.h>

#include "Common.h"

namespace
{
void preparePlot(HistogramPlot& plot)
{
    Quantiles quantiles;
    QVector<double> prices{common::getPrices()};
    const QVector<double> dataForQuantiles(prices);
    quantiles.init(dataForQuantiles);

    QVector<double> plotData;
    plotData.reserve(prices.size());
    for (const auto& item : prices)
        plotData.append(item);
    plot.setNewData(std::move(plotData), quantiles, 10);
    plot.resize(800, 600);
}

void checkPlot(HistogramPlot& plot, QString expectedPath)
{
    QImage actual{plot.grab().toImage()};
    QImage expected(expectedPath);
    expected = expected.convertToFormat(actual.format());
    QCOMPARE(actual, expected);
}
}  // namespace

void HistogramPlotTest::testPlotWithData()
{
    HistogramPlot plot;
    preparePlot(plot);

    const QString expectedPath{
        QString::fromLatin1(":/res/HistogramPlotDefault.png")};
    checkPlot(plot, expectedPath);
}

void HistogramPlotTest::testPlotWithoutData()
{
    HistogramPlot plot;
    plot.setNewData({}, {}, 10);
    plot.resize(800, 600);

    QImage actual{plot.grab().toImage()};
    const QString expectedPath{
        QString::fromLatin1(":/res/HistogramPlotWithoutData.png")};
    checkPlot(plot, expectedPath);
}

void HistogramPlotTest::testLegendItemsChecking()
{
    HistogramPlot plot;
    preparePlot(plot);

    auto* legend{::qobject_cast<QwtLegend*>(plot.legend())};
    legend->checked(common::getItemInfo(plot, "Histogram"), false, 0);

    const QString expectedPath{
        QString::fromLatin1(":/res/HistogramPlotItemChecked.png")};
    checkPlot(plot, expectedPath);
}
