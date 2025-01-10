#include <QApplication>
#include <QGroupBox>
#include <QScrollArea>
#include <QSplitter>
#include <QStyleFactory>
#include <QVBoxLayout>
#include <QWidget>

#include <qwtble/BasicDataPlot.h>
#include <qwtble/GroupPlot.h>
#include <qwtble/GroupPlotUI.h>
#include <qwtble/HistogramPlot.h>
#include <qwtble/HistogramPlotUI.h>
#include <qwtble/Quantiles.h>
#include <qwtble/QuantilesPlot.h>

namespace
{
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

QVector<QVector<double>> getAlternativeValues()
{
    return {
        {3.5, 6.7, 4.7, 6.6, 3., 4.9, 5.5, 1.2},
        {3.2, 7.6, 5., 4.9, 0.3, 7.3, 2.1, 1.7, 4.3, 6.6, 1., 3.9, 5.5},
        {1.1, 3.2, 3.8, 6.5, 2., 2.9, 7.5, 3.2, 5.5, 2.1, 1.7, 4.3, 6.1, 2.}};
}

QVector<QString> getAlternativeNames()
{
    return {QStringLiteral("green"), QStringLiteral("black"),
            QStringLiteral("white")};
}

QVector<double> getPriceSeries()
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

// As number of days since 1.1.1970.
QVector<double> getDateSeries()
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

QGroupBox* wrapPlot(const QString& name, QWidget* widget)
{
    QGroupBox* groupBox{new QGroupBox(name)};
    QVBoxLayout* layout{new QVBoxLayout()};
    layout->addWidget(widget);
    groupBox->setLayout(layout);
    return groupBox;
}

QuantilesPlot* createQuantilesPlot()
{
    QuantilesPlot* quantilesPlot{new QuantilesPlot()};
    Quantiles quantiles;
    quantiles.init(getValues().first());
    quantilesPlot->setNewData(quantiles);
    return quantilesPlot;
}

GroupPlot* createGroupPlot()
{
    QVector<Quantiles> quantilesVector;
    quantilesVector.reserve(getValues().size());
    for (const auto& values : getValues())
    {
        Quantiles quantiles;
        quantiles.init(values);
        quantilesVector.push_back(quantiles);
    }
    GroupPlot* groupPlot{new GroupPlot()};
    groupPlot->setAxisScale(QwtPlot::yLeft, 0, 8);
    groupPlot->setAxisScale(QwtPlot::yRight, 0, 8);
    const double maxValueForBottomAxis{static_cast<double>(getValues().size()) +
                                       0.5};
    groupPlot->setAxisScale(QwtPlot::xBottom, 0.5, maxValueForBottomAxis, 1);
    groupPlot->setNewData(std::move(quantilesVector), getNames());
    return groupPlot;
}

GroupPlotUI* createGroupPlotUI()
{
    QVector<Quantiles> quantilesVector;
    quantilesVector.reserve(getValues().size());
    for (const auto& values : getValues())
    {
        Quantiles quantiles;
        quantiles.init(values);
        quantilesVector.push_back(quantiles);
    }

    QVector<Quantiles> otherQuantilesVector;
    otherQuantilesVector.reserve(getAlternativeValues().size());
    for (const auto& values : getAlternativeValues())
    {
        Quantiles quantiles;
        quantiles.init(values);
        otherQuantilesVector.push_back(quantiles);
    }

    QVector<double> allValues;
    allValues.reserve(getValues().size());
    for (const auto& values : getValues())
        allValues.append(values);

    Quantiles generalQuantiles;
    generalQuantiles.init(allValues);

    const QVector<std::pair<QString, int>> stringColumns{{"Shape", 0},
                                                         {"Color", 1}};
    GroupPlotUI* groupPlotUI{new GroupPlotUI(stringColumns)};
    QObject::connect(
        groupPlotUI, &GroupPlotUI::traitIndexChanged, groupPlotUI,
        [=](int column)
        {
            const QVector<QString>& names =
                (column == 0 ? getNames() : getAlternativeNames());
            const QVector<Quantiles>& quantiles =
                (column == 0 ? quantilesVector : otherQuantilesVector);
            groupPlotUI->setNewData(names, quantiles, generalQuantiles);
        });

    return groupPlotUI;
}

HistogramPlot* createHistogramPlot(const Quantiles& quantiles)
{
    QVector<double> plotData;
    const QVector<double> priceSeries{getPriceSeries()};
    plotData.reserve(priceSeries.size());
    for (const auto& item : priceSeries)
        plotData.append(item);

    HistogramPlot* histogramPlot{new HistogramPlot()};
    histogramPlot->setNewData(std::move(plotData), quantiles, 10);
    return histogramPlot;
}

HistogramPlotUI* createHistogramPlotUI(const Quantiles& quantiles)
{
    QVector<double> plotData;
    const QVector<double> priceSeries{getPriceSeries()};
    plotData.reserve(priceSeries.size());
    for (const auto& item : priceSeries)
        plotData.append(item);

    HistogramPlotUI* histogramPlotUI{new HistogramPlotUI()};
    histogramPlotUI->setNewData(std::move(plotData), quantiles);
    return histogramPlotUI;
}

BasicDataPlot* createBasicDataPlot(Quantiles& quantiles)
{
    const QVector<double> dateseries{getDateSeries()};
    const auto [min, max]{
        std::minmax_element(dateseries.cbegin(), dateseries.cend())};
    const QVector<QPointF> linearRegressionPoints{{*min, 38.002},
                                                  {*max, 78.4491}};

    const QVector<double> priceSeries{getPriceSeries()};
    const qsizetype seriesSize{priceSeries.size()};
    QVector<QPointF> data;
    data.reserve(seriesSize);
    for (qsizetype i{0}; i < seriesSize; ++i)
        data.append({dateseries[i], priceSeries[i]});

    BasicDataPlot* basicDataPlot{new BasicDataPlot()};
    basicDataPlot->setAxisScale(QwtPlot::xBottom, *min, *max);
    quantiles.minX_ = *min;
    quantiles.maxX_ = *max;
    basicDataPlot->setNewData(data, quantiles, linearRegressionPoints);
    return basicDataPlot;
}

void initUpperSplitter(QSplitter& splitter)
{
    splitter.addWidget(
        wrapPlot(QStringLiteral("Quantiles plot"), createQuantilesPlot()));
    splitter.addWidget(
        wrapPlot(QStringLiteral("Grouping plot"), createGroupPlot()));
    GroupPlotUI* groupPlotUI{createGroupPlotUI()};
    splitter.addWidget(
        wrapPlot(QStringLiteral("Grouping plot UI"), groupPlotUI));

    emit groupPlotUI->traitIndexChanged(0);
}

void initLowerSplitter(QSplitter& splitter)
{
    Quantiles quantiles;
    const QVector<double> priceSeries{getPriceSeries()};
    const QVector<double> dataForQuantiles(priceSeries);
    quantiles.init(dataForQuantiles);

    splitter.addWidget(wrapPlot(QStringLiteral("Histogram plot"),
                                createHistogramPlot(quantiles)));
    splitter.addWidget(wrapPlot(QStringLiteral("Histogram plot UI"),
                                createHistogramPlotUI(quantiles)));
    splitter.addWidget(wrapPlot(QStringLiteral("Basic data plot"),
                                createBasicDataPlot(quantiles)));
    splitter.setStretchFactor(0, 1);
    splitter.setStretchFactor(1, 1);
    splitter.setStretchFactor(2, 2);
}

}  // namespace

int main(int argc, char* argv[])
{
    const QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

    QWidget widget;
    QVBoxLayout widgetLayout(&widget);

    QSplitter upperSplitter;
    initUpperSplitter(upperSplitter);
    widgetLayout.addWidget(&upperSplitter);

    QSplitter lowerSplitter;
    initLowerSplitter(lowerSplitter);
    widgetLayout.addWidget(&lowerSplitter);

    widget.setLayout(&widgetLayout);
    widget.resize(1000, 750);
    widget.show();

    return QApplication::exec();
}
