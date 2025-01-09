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

void QuantilesPlotTest::testReset()
{
    QuantilesPlot plot;
    preparePlot(plot);

    QwtPlotPanner panner(plot.canvas());
    panner.setMouseButton(Qt::LeftButton);

    plot.show();
    QPoint endPos(50, 50);
    QPoint startPos(100, 100);

    // Force showing label.
    QTest::mousePress(plot.canvas(), Qt::LeftButton, Qt::NoModifier, endPos);
    QTest::mouseMove(plot.canvas(), endPos);
    QTest::mouseRelease(plot.canvas(), Qt::LeftButton, Qt::NoModifier, endPos);

    QImage beforeMove{plot.grab().toImage()};

    QTest::mousePress(plot.canvas(), Qt::LeftButton, Qt::NoModifier, startPos);
    QTest::mouseMove(plot.canvas(), endPos);
    QTest::mouseRelease(plot.canvas(), Qt::LeftButton, Qt::NoModifier, endPos);

    QImage afterMove{plot.grab().toImage()};
    QCOMPARE_NE(beforeMove, afterMove);

    QMouseEvent customEvent(QEvent::MouseButtonDblClick, endPos, endPos,
                            Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QCoreApplication::sendEvent(plot.canvas(), &customEvent);

    QImage afterReset{plot.grab().toImage()};
    QCOMPARE(beforeMove, afterReset);
}
