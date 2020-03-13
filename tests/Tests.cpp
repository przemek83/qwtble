#include <QTest>

#include "CheckTest.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    CheckTest checkTest;
    QTest::qExec(&checkTest);

    return 0;
}
