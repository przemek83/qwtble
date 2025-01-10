#pragma once

#include <QObject>

class BasicDataPlotTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    static void testPlotWithData();
    static void testPlotWithoutData();
    static void testLegendItemsChecking();
};
