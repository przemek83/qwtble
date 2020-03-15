#include <QTest>

#include "UtilitiesTest.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    UtilitiesTest utilitiesTest;
    QTest::qExec(&utilitiesTest);

    return 0;
}
