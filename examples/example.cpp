#include <QApplication>
#include <QStyleFactory>
#include <QWidget>
#include <QVBoxLayout>

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
