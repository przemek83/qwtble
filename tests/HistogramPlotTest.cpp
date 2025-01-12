#include "HistogramPlotTest.h"

#include <QTest>
#include "qwt_legend.h"
#include "qwt_plot_item.h"

#include <qwtble/HistogramPlot.h>

#include "Common.h"

namespace
{
void preparePlot(HistogramPlot& plot)
{
    Quantiles quantiles;
    const QVector<double> prices{common::getPrices()};
    quantiles.init(prices);

    QVector<double> plotData;
    plotData.reserve(prices.size());
    for (const auto& item : prices)
        plotData.append(item);
    plot.setNewData(std::move(plotData), quantiles, 10);
    plot.resize(common::getPlotSize());
}
}  // namespace

void HistogramPlotTest::testPlotWithData()
{
    HistogramPlot plot;
    preparePlot(plot);

    const QImage actual{plot.grab().toImage()};
    actual.save("HistogramPlotDefault.png");

    const QString expectedPath{QString::fromLatin1("HistogramPlotDefault.png")};
    common::checkPlot(plot, expectedPath);
}

void HistogramPlotTest::testPlotWithoutData()
{
    HistogramPlot plot;
    plot.setNewData({}, {}, 10);
    plot.resize(common::getPlotSize());

    const QImage actual{plot.grab().toImage()};
    actual.save("HistogramPlotWithoutData.png");

    const QString expectedPath{
        QString::fromLatin1("HistogramPlotWithoutData.png")};
    common::checkPlot(plot, expectedPath);
}

void HistogramPlotTest::testLegendItemsChecking()
{
    HistogramPlot plot;
    preparePlot(plot);

    auto* legend{::qobject_cast<QwtLegend*>(plot.legend())};
    emit legend->checked(common::getItemInfo(plot, QStringLiteral("Histogram")),
                         false, 0);

    const QImage actual{plot.grab().toImage()};
    actual.save("HistogramPlotItemChecked.png");

    const QString expectedPath{
        QString::fromLatin1("HistogramPlotItemChecked.png")};
    common::checkPlot(plot, expectedPath);
}
