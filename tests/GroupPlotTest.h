#pragma once

#include <QObject>

class GroupPlotTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    static void testPlotWithData();
    static void testPlotWithoutData();
};
