#include "UtilitiesTest.h"

#include <QTest>

#include <qwtble/QwtBleUtilities.h>

void UtilitiesTest::testStringFromDays()
{
    using qwt_ble_utilities::stringFromDays;
    QCOMPARE(stringFromDays(0), QStringLiteral("1/1/1970"));
    QCOMPARE(stringFromDays(-100), QStringLiteral("23/9/1969"));
    QCOMPARE(stringFromDays(20'000), QStringLiteral("4/10/2024"));
}

void UtilitiesTest::testFloatsAreEqual()
{
    using qwt_ble_utilities::floatsAreEqual;
    QCOMPARE(floatsAreEqual(4.00001F, 4.00002F), false);
    QCOMPARE(floatsAreEqual(4.000001F, 4.000002F), true);
}

void UtilitiesTest::testDoublesAreEqual()
{
    using qwt_ble_utilities::doublesAreEqual;
    QCOMPARE(doublesAreEqual(4.00000000001, 4.00000000002), false);
    QCOMPARE(doublesAreEqual(4.000000000001, 4.000000000002), true);
}
