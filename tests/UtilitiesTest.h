#pragma once

#include <QObject>

class UtilitiesTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    static void testStringFromDays();
    static void testFloatsAreEqual();
    static void testDoublesAreEqual();
};
