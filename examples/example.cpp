#include <QApplication>
//#include <QGroupBox>
//#include <QLabel>
//#include <QPushButton>
#include <QStyleFactory>
//#include <QTimer>
#include <QWidget>
#include <QVBoxLayout>
//#include <QWindow>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

    QWidget widget;
    QHBoxLayout widgetLayout(&widget);
    widget.setLayout(&widgetLayout);
    widget.show();

    return QApplication::exec();
}
