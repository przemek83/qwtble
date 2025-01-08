#pragma once

#include <QObject>

class GroupPlotTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testPlotWithData();
    void testPlotWithoutData();
};
