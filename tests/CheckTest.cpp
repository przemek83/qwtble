#include "CheckTest.h"

#include <QSignalSpy>
#include <QTest>

void CheckTest::initTestCase()
{
    //qApp->setStyleSheet(QStringLiteral("QSlider::handle:horizontal {width: 10px}"));
}

void CheckTest::testFirst()
{
    QCOMPARE(true, true);
}
