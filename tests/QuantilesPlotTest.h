#pragma once

#include <QObject>

class QuantilesPlotTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testPlotWithData();
    void testPlotWithoutData();
};
