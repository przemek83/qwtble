#pragma once

#include <QObject>

class UtilitiesTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testStringFromDays();
    void testFloatsAreEqual();
    void testDoublesAreEqual();
};
