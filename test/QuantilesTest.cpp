#include "QuantilesTest.h"

#include <QRegularExpression>
#include <QTest>

#include <qwtble/Quantiles.h>

void QuantilesTest::testToolTip()
{
    Quantiles quantiles;
    quantiles.init(values_);
    const QString expected(
        QStringLiteral("<table>"
                       "<tr><td>Data count:</td><td ALIGN=RIGHT></td></tr>\n"
                       "<tr><td>Average</td><td ALIGN=RIGHT></td></tr>\n"
                       "<tr><td>Maximum</td><td ALIGN=RIGHT></td></tr>\n"
                       "<tr><td>Q90</td><td ALIGN=RIGHT></td></tr>\n"
                       "<tr><td>Q75</td><td ALIGN=RIGHT></td></tr>\n"
                       "<tr><td>Q50</td><td ALIGN=RIGHT></td></tr>\n"
                       "<tr><td>Q25</td><td ALIGN=RIGHT></td></tr>\n"
                       "<tr><td>Q10</td><td ALIGN=RIGHT></td></tr>\n"
                       "<tr><td>Minimum</td><td ALIGN=RIGHT></td></tr>\n"
                       "<tr><td>Std. deviation</td><td ALIGN=RIGHT></td></tr>\n"
                       "</table>"));
    // Ignore numbers due to localization. Test only structure of tooltip.
    const QLocale& locale = QLocale::system();
    const QRegularExpression regexp{
        QRegularExpression(QStringLiteral(">[0-9]*\\") + locale.decimalPoint() +
                           QStringLiteral("?[0-9]*<"))};
    QCOMPARE(expected, quantiles.getValuesAsToolTip().replace(
                           regexp, QStringLiteral("><")));
}

void QuantilesTest::testComputing()
{
    Quantiles quantiles;
    quantiles.init(values_);
    QCOMPARE(quantiles.count_, 11);
    QCOMPARE(quantiles.mean_, 66.6209090909);
    QCOMPARE(quantiles.max_, 177.01);
    QCOMPARE(quantiles.q90_, 138.12);
    QCOMPARE(quantiles.q75_, 97.445);
    QCOMPARE(quantiles.q50_, 54.94);
    QCOMPARE(quantiles.q25_, 17.925);
    QCOMPARE(quantiles.q10_, 7.02);
    QCOMPARE(quantiles.min_, 5.00);
    QCOMPARE(quantiles.stdDev_, 54.4808128785);
    QCOMPARE(quantiles.minX_, 0);
    QCOMPARE(quantiles.maxX_, 0);
}

void QuantilesTest::testComputingEmptyData()
{
    Quantiles quantiles;
    const QVector<double> emptyData{};
    quantiles.init(emptyData);
    QCOMPARE(quantiles.count_, 0);
    QCOMPARE(quantiles.mean_, 0);
    QCOMPARE(quantiles.max_, 0);
    QCOMPARE(quantiles.q90_, 0);
    QCOMPARE(quantiles.q75_, 0);
    QCOMPARE(quantiles.q50_, 0);
    QCOMPARE(quantiles.q25_, 0);
    QCOMPARE(quantiles.q10_, 0);
    QCOMPARE(quantiles.min_, 0);
    QCOMPARE(quantiles.stdDev_, 0);
    QCOMPARE(quantiles.minX_, 0);
    QCOMPARE(quantiles.maxX_, 0);
}

void QuantilesTest::testComputingSinleItemData()
{
    Quantiles quantiles;
    const QVector<double> singleItemData{3};
    quantiles.init(singleItemData);
    QCOMPARE(quantiles.count_, 1);
    QCOMPARE(quantiles.mean_, 3);
    QCOMPARE(quantiles.max_, 3);
    QCOMPARE(quantiles.q90_, 0);
    QCOMPARE(quantiles.q75_, 0);
    QCOMPARE(quantiles.q50_, 0);
    QCOMPARE(quantiles.q25_, 0);
    QCOMPARE(quantiles.q10_, 0);
    QCOMPARE(quantiles.min_, 3);
    QCOMPARE(quantiles.stdDev_, 0);
    QCOMPARE(quantiles.minX_, 0);
    QCOMPARE(quantiles.maxX_, 0);
}
