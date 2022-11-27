#include "GroupPlotUITest.h"

#include <GroupPlotUI.h>
#include <QComboBox>
#include <QSignalSpy>
#include <QTest>

void GroupPlotUITest::testTraitChange()
{
    GroupPlotUI groupPlotUI({{"a", 0}, {"b", 1}, {"c", 2}});
    auto* comboBox = groupPlotUI.findChild<QComboBox*>();
    QSignalSpy newColumnSpy(&groupPlotUI, &GroupPlotUI::traitIndexChanged);
    const int newIndex{2};
    comboBox->setCurrentIndex(newIndex);
    const int SIGNAL_RECEIVED{1};
    QCOMPARE(newColumnSpy.count(), SIGNAL_RECEIVED);
    QCOMPARE(newColumnSpy[0], {newIndex});
}
