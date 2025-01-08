#pragma once

#include <QObject>

class HistogramPlotTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testPlotWithData();
    void testPlotWithoutData();
    void testLegendItemsChecking();
};
