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

    const double maxValueForXAxis{8};
    plot.setAxisScale(QwtPlot::yLeft, 0, maxValueForXAxis);
    plot.setAxisScale(QwtPlot::yRight, 0, maxValueForXAxis);

    const double maxValueForBottomAxis{
        static_cast<double>(common::getValues().size()) + 0.5};
    plot.setAxisScale(QwtPlot::xBottom, 0.5, maxValueForBottomAxis, 1);
    plot.setNewData(std::move(quantilesVector), common::getNames());
    plot.resize(common::getPlotSize());
}
}  // namespace

void GroupPlotTest::testPlotWithData() const
{
    GroupPlot plot;
    preparePlot(plot);

    const QString expectedPath{
        QString::fromLatin1(":/res/GroupPlotDefault.png")};
    common::checkPlot(plot, expectedPath);
}

void GroupPlotTest::testPlotWithoutData() const
{
    GroupPlot plot;
    plot.setNewData({}, {});
    plot.resize(common::getPlotSize());

    const QString expectedPath{
        QString::fromLatin1(":/res/GroupPlotPlotWithoutData.png")};
    common::checkPlot(plot, expectedPath);
}
