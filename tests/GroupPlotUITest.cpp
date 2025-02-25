#include "GroupPlotUITest.h"

#include <QComboBox>
#include <QSignalSpy>
#include <QTest>

#include <qwtble/GroupPlotUI.h>

void GroupPlotUITest::testTraitChange()
{
    const GroupPlotUI groupPlotUI({{"a", 0}, {"b", 1}, {"c", 2}});
    QComboBox* comboBox{groupPlotUI.findChild<QComboBox*>()};
    QSignalSpy newColumnSpy(&groupPlotUI, &GroupPlotUI::traitIndexChanged);
    const int newIndex{2};
    comboBox->setCurrentIndex(newIndex);
    const int SIGNAL_RECEIVED{1};
    QCOMPARE(newColumnSpy.count(), SIGNAL_RECEIVED);
    QCOMPARE(newColumnSpy[0], {newIndex});
}
