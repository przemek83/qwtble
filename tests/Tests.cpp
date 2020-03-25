#include <QTest>

#include "GroupPlotUITest.h"
#include "UtilitiesTest.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    UtilitiesTest utilitiesTest;
    QTest::qExec(&utilitiesTest);

    GroupPlotUITest groupPlotUITest;
    QTest::qExec(&groupPlotUITest);

    return 0;
}
