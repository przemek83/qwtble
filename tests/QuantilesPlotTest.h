#pragma once

#include <QObject>

class QuantilesPlotTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    static void testPlotWithData();
    static void testPlotWithoutData();
    // static void testReset();
};
