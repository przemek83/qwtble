#include "Common.h"

#include <QTest>
#include <QVariant>

#include "qwt_legend.h"
#include "qwt_legend_label.h"
#include "qwt_plot.h"
#include "qwt_plot_item.h"

namespace common
{
QVector<double> getPrices()
{
    return {
        84.66,  40.,    5.,     7.02,  177.01, 110.23, 138.12, 54.94,  20.,
        80.,    15.85,  26.77,  51.61, 144.44, 106.,   8.06,   92.5,   19.57,
        91.44,  90.,    75.,    39.56, 0.2,    25.,    80.,    54.86,  2.13,
        4.84,   15.,    2.67,   95.,   100.,   5.,     5.,     96.38,  1.99,
        75.08,  93.37,  99.82,  94.81, 2.35,   140.44, 150.,   138.72, 295.25,
        50.,    110.97, 4.87,   45.,   60.,    90.,    66.17,  78.68,  75.87,
        8.95,   65.,    1.3,    5.83,  44.13,  59.65,  102.52, 108.45, 70.,
        70.,    70.,    70.,    68.,   7.92,   36.34,  30.3,   93.69,  146.81,
        79.,    100.,   70.,    61.79, 38.42,  19.41,  45.45,  7.39,   223.55,
        45.,    90.,    90.,    75.21, 45.,    130.,   17.44,  75.,    69.9,
        112.74, 126.36, 40.,    30.,   1.88,   46.2,   2.99,   48.69,  21.74,
        98.39,  65.,    147.98, 25.,   45.,    5.38};
}

QVector<double> getDates()
{
    return {
        13959., 13941., 13984., 13914., 13999., 13979., 13945., 13999., 14013.,
        13972., 13992., 13969., 13951., 13970., 13951., 13970., 13986., 13993.,
        14011., 13969., 13977., 14026., 13990., 13916., 13972., 13999., 13980.,
        13956., 13977., 14019., 14028., 13999., 13950., 13950., 14011., 14011.,
        14026., 13965., 14032., 14008., 13951., 14012., 13991., 14007., 14019.,
        13980., 13997., 14042., 13985., 13991., 13986., 13972., 13965., 13949.,
        13990., 14035., 14008., 14019., 13964., 13957., 14033., 14014., 13980.,
        13980., 13980., 13980., 13980., 13992., 13999., 13943., 13997., 13920.,
        13977., 13944., 13986., 13956., 13966., 13951., 14032., 14027., 13993.,
        13980., 13986., 13986., 13983., 13955., 13941., 14013., 14042., 14039.,
        14042., 13937., 13914., 13915., 13930., 13845., 13864., 13857., 13867.,
        13929., 13972., 13910., 13924., 13924., 13927.};
}

QVector<QVector<double>> getValues()
{
    return {{3.5, 6.7, 4.7, 6.6, 3., 4.9},
            {5.5, 1.2, 3.2, 7.6, 5., 4.9, 0.3, 7.3},
            {2.1, 1.7, 4.3, 6.6, 1., 3.9, 5.5},
            {1.1, 3.2, 3.8, 6.5, 2., 2.9, 7.5, 3.2, 5.5},
            {2.1, 1.7, 4.3, 6.1, 2.}};
}

QVector<QString> getNames()
{
    return {QStringLiteral("circle"), QStringLiteral("triangle"),
            QStringLiteral("square"), QStringLiteral("rectangle"),
            QStringLiteral("cube")};
}

QVariant getItemInfo(QwtPlot& plot, const QString& text)
{
    const auto* legend{::qobject_cast<QwtLegend*>(plot.legend())};
    const QList<QwtLegendLabel*> children{
        legend->findChildren<QwtLegendLabel*>()};

    for (const auto* child : children)
    {
        if (child->text().text() == text)
            return QVariant::fromValue(legend->itemInfo(child));
    }

    return {};
}

QSize getPlotSize() { return {800, 600}; }

void checkPlot(QwtPlot& plot, const QString& expectedFileName)
{
    QString expectedPath;
#ifdef Q_OS_WIN
    expectedPath = QStringLiteral(":/windows/res/windows/");
    // QLabel label("Running on Windows");
    // qDebug() << "This code is compiled for Windows.";
#else
    expectedPath = QStringLiteral(":/unix-like/res/unix-like/");
    // QLabel label("Running on non-Windows OS");
    // qDebug() << "This code is compiled for a non-Windows OS.";
#endif

    const QImage actual{plot.grab().toImage()};
    QImage expected(expectedPath + expectedFileName);
    expected = expected.convertToFormat(actual.format());
    QCOMPARE(actual, expected);
}

void checkPlotCanvas(QwtPlot& plot, const QString& expectedFileName)
{
    const QImage actual{plot.canvas()->grab().toImage()};
    QImage expected(expectedFileName);
    expected = expected.convertToFormat(actual.format());
    QCOMPARE(actual, expected);
}
}  // namespace common
