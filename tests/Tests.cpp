#include <QTest>

#include "GroupPlotUITest.h"
#include "QuantilesTest.h"
#include "UtilitiesTest.h"

int main(int argc, char* argv[])
{
    const QApplication a(argc, argv);

    UtilitiesTest utilitiesTest;
    QTest::qExec(&utilitiesTest);

    GroupPlotUITest groupPlotUITest;
    QTest::qExec(&groupPlotUITest);

    QuantilesTest quantilesTest;
    QTest::qExec(&quantilesTest);

    return 0;
}
