#include <QTest>

#include "GroupPlotUITest.h"
#include "QuantilesTest.h"
#include "UtilitiesTest.h"

int main(int argc, char* argv[])
{
    const QApplication a(argc, argv);

    QLocale locale(QLocale::English, QLocale::UnitedStates);
    QLocale::setDefault(locale);

    UtilitiesTest utilitiesTest;
    QTest::qExec(&utilitiesTest);

    GroupPlotUITest groupPlotUITest;
    QTest::qExec(&groupPlotUITest);

    QuantilesTest quantilesTest;
    QTest::qExec(&quantilesTest);

    return 0;
}
