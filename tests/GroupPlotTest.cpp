#include "GroupPlotTest.h"

#include <QTest>

#include <qwtble/GroupPlot.h>

#include "Common.h"

namespace
{
void preparePlot(GroupPlot& plot)
{
    QVector<Quantiles> quantilesVector;
    quantilesVector.reserve(common::getValues().size());
    for (const auto& values : common::getValues())
    {
        Quantiles quantiles;
        quantiles.init(values);
        quantilesVector.push_back(quantiles);
    }

    plot.setAxisScale(QwtPlot::yLeft, 0, 8);
    plot.setAxisScale(QwtPlot::yRight, 0, 8);
    plot.setAxisScale(QwtPlot::xBottom, 0.5, common::getValues().size() + 0.5,
                      1);
    plot.setNewData(std::move(quantilesVector), common::getNames());
    plot.resize(common::getPlotSize());
}

void checkPlot(GroupPlot& plot, QString expectedPath)
{
    QImage actual{plot.grab().toImage()};
    QImage expected(expectedPath);
    expected = expected.convertToFormat(actual.format());
    QCOMPARE(actual, expected);
}
}  // namespace

void GroupPlotTest::testPlotWithData()
{
    GroupPlot plot;
    preparePlot(plot);

    const QString expectedPath{
        QString::fromLatin1(":/res/GroupPlotDefault.png")};
    checkPlot(plot, expectedPath);
}

void GroupPlotTest::testPlotWithoutData()
{
    GroupPlot plot;
    plot.setNewData({}, {});
    plot.resize(common::getPlotSize());

    const QString expectedPath{
        QString::fromLatin1(":/res/GroupPlotPlotWithoutData.png")};
    checkPlot(plot, expectedPath);
}
