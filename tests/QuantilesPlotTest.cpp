#include "QuantilesPlotTest.h"

#include <QTest>

#include <qwtble/QuantilesPlot.h>

#include "Common.h"

namespace
{
void preparePlot(QuantilesPlot& plot)
{
    Quantiles quantiles;
    quantiles.init(common::getValues().first());
    plot.setNewData(quantiles);
    plot.resize(common::getPlotSize());
}

void checkPlot(QuantilesPlot& plot, QString expectedPath)
{
    QImage actual{plot.grab().toImage()};
    QImage expected(expectedPath);
    expected = expected.convertToFormat(actual.format());
    QCOMPARE(actual, expected);
}
}  // namespace

void QuantilesPlotTest::testPlotWithData()
{
    QuantilesPlot plot;
    preparePlot(plot);

    const QString expectedPath{
        QString::fromLatin1(":/res/QuantilesPlotDefault.png")};
    checkPlot(plot, expectedPath);
}

void QuantilesPlotTest::testPlotWithoutData()
{
    QuantilesPlot plot;
    plot.setNewData({});
    plot.resize(common::getPlotSize());

    const QString expectedPath{
        QString::fromLatin1(":/res/QuantilesPlotWithoutData.png")};
    checkPlot(plot, expectedPath);
}
