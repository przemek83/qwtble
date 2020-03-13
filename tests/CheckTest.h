#ifndef CHECKTEST
#define CHECKTEST

#include <QObject>

class CheckTest: public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase();

    void testFirst();
};

#endif // CHECKTEST
