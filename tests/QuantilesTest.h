#pragma once

#include <QObject>
#include <QVector>

class QuantilesTest : public QObject
{
    Q_OBJECT
private:
    QVector<double> values_{84.66,  40.,   5.,  7.02, 177.01, 110.23,
                            138.12, 54.94, 20., 80.,  15.85};
private Q_SLOTS:
    void testToolTip() const;

    static void testToolTipForOneValue();

    void testComputing();

    static void testComputingEmptyData();

    static void testComputingSingleItemData();
};
