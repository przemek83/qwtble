#include "GroupPlotTest.h"

#include <QTest>

#include <qwtble/GroupPlot.h>

#include "Common.h"

namespace
{
const QVector<QVector<double>> exampleValues{
    {3.5, 6.7, 4.7, 6.6, 3., 4.9},
    {5.5, 1.2, 3.2, 7.6, 5., 4.9, 0.3, 7.3},
    {2.1, 1.7, 4.3, 6.6, 1., 3.9, 5.5},
    {1.1, 3.2, 3.8, 6.5, 2., 2.9, 7.5, 3.2, 5.5},
    {2.1, 1.7, 4.3, 6.1, 2.}};

const QVector<QString> exampleNames{
    QStringLiteral("circle"), QStringLiteral("triangle"),
    QStringLiteral("square"), QStringLiteral("rectangle"),
    QStringLiteral("cube")};

void preparePlot(GroupPlot& plot)
{
    QVector<Quantiles> quantilesVector;
    quantilesVector.reserve(exampleValues.size());
    for (auto& values : exampleValues)
    {
        Quantiles quantiles;
        quantiles.init(values);
        quantilesVector.push_back(quantiles);
    }

    plot.setAxisScale(QwtPlot::yLeft, 0, 8);
    plot.setAxisScale(QwtPlot::yRight, 0, 8);
    plot.setAxisScale(QwtPlot::xBottom, 0.5, exampleValues.size() + 0.5, 1);
    plot.setNewData(std::move(quantilesVector), exampleNames);
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
