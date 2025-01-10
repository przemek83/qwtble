#pragma once

#include <QObject>

class BasicDataPlotTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testPlotWithData() const;
    void testPlotWithoutData() const;
    void testLegendItemsChecking() const;
};
