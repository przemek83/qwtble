#include "UtilitiesTest.h"

#include <QSignalSpy>
#include <QTest>

#include "QwtBleUtilities.h"

void UtilitiesTest::testStringFromDays()
{
    QCOMPARE(QwtBleUtilities::stringFromDays(0), QString("1/1/1970"));
    QCOMPARE(QwtBleUtilities::stringFromDays(-100), QString("23/9/1969"));
    QCOMPARE(QwtBleUtilities::stringFromDays(20000), QString("4/10/2024"));
}
