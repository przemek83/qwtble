#include <QFontDatabase>
#include <QStyleFactory>
#include <QTest>

#include "BasicDataPlotTest.h"
#include "GroupPlotTest.h"
#include "GroupPlotUITest.h"
#include "HistogramPlotTest.h"
#include "QuantilesPlotTest.h"
#include "QuantilesTest.h"
#include "UtilitiesTest.h"

namespace
{
void setLightPalette()
{
    QPalette palette;
    const QColor color(240, 240, 240);
    const QColor altColor(225, 225, 225);
    palette.setColor(QPalette::Window, color);
    palette.setColor(QPalette::Button, color);
    palette.setColor(QPalette::Window, color);
    palette.setColor(QPalette::Dark, altColor);
    palette.setColor(QPalette::Light, altColor);
    palette.setColor(QPalette::Midlight, altColor);
    palette.setColor(QPalette::Mid, altColor);
    palette.setColor(QPalette::Shadow, altColor);
    palette.setColor(QPalette::WindowText, Qt::black);
    palette.setColor(QPalette::Base, Qt::white);
    palette.setColor(QPalette::AlternateBase, altColor);
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::black);
    palette.setColor(QPalette::Text, Qt::black);
    palette.setColor(QPalette::Button, color);
    palette.setColor(QPalette::ButtonText, Qt::black);
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Link, altColor);
    palette.setColor(QPalette::Highlight, altColor);
    palette.setColor(QPalette::HighlightedText, Qt::white);

    QApplication::setPalette(palette);
}

void setupFont()
{
    const int id{QFontDatabase::addApplicationFont(
        QStringLiteral(":/res/FiraMono-Regular.ttf"))};
    const QString family{QFontDatabase::applicationFontFamilies(id).at(0)};
    QFont font(family);
    font.setPointSize(12);
    font.setStyleStrategy(static_cast<QFont::StyleStrategy>(
        QFont::NoAntialias | QFont::PreferBitmap | QFont::NoSubpixelAntialias |
        QFont::PreferNoShaping | QFont::NoFontMerging));
    QApplication::setFont(font);
}
}  // namespace

int main(int argc, char* argv[])
{
    const QApplication app(argc, argv);

    QStyle* style{QStyleFactory::create(QStringLiteral("Fusion"))};
    QApplication::setStyle(style);
    setLightPalette();

    const QLocale locale(QLocale::English, QLocale::UnitedStates);
    QLocale::setDefault(locale);

    setupFont();

    int status{EXIT_SUCCESS};
    UtilitiesTest utilitiesTest;
    status |= QTest::qExec(&utilitiesTest);

    GroupPlotUITest groupPlotUITest;
    status |= QTest::qExec(&groupPlotUITest);

    QuantilesTest quantilesTest;
    status |= QTest::qExec(&quantilesTest);

    BasicDataPlotTest basicDataPlotTest;
    status |= QTest::qExec(&basicDataPlotTest);

    HistogramPlotTest histogramPlotTest;
    status |= QTest::qExec(&histogramPlotTest);

    GroupPlotTest groupPlotTest;
    status |= QTest::qExec(&groupPlotTest);

    QuantilesPlotTest quantilesPlotTest;
    status |= QTest::qExec(&quantilesPlotTest);

    return status;
}
