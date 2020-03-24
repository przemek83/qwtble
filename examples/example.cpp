#include <QApplication>
#include <QGroupBox>
#include <QStyleFactory>
#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <QScrollArea>

#include <BasicDataPlot.h>
#include <GroupPlot.h>
#include <HistogramPlot.h>
#include <HistogramPlotUI.h>
#include <PlotBase.h>
#include <QuantilesPlot.h>
#include <QwtBleUtilities.h>

static QVector<QVector<double>> exampleValues {{3.5, 6.7, 4.7, 6.6, 3., 4.9},
    {5.5, 1.2, 3.2, 7.6, 5., 4.9, 0.3, 7.3},
    {2.1, 1.7, 4.3, 6.6, 1., 3.9, 5.5},
    {1.1, 3.2, 3.8, 6.5, 2., 2.9, 7.5, 3.2, 5.5},
    {2.1, 1.7, 4.3, 6.1, 2.}};
static QVector<QString> exampleNames {"first", "second", "third", "fourth", "fifth"};

static const QVector<double> examplePriceSeries
{
    84.66, 40., 5., 7.02, 177.01, 110.23, 138.12, 54.94, 20., 80., 15.85, 26.77,
    51.61, 144.44, 106., 8.06, 92.5, 19.57, 91.44, 90., 75., 39.56, 0.2, 25.,
    80., 54.86, 2.13, 4.84, 15., 2.67, 95., 100., 5., 5., 96.38, 1.99, 75.08,
    93.37, 99.82, 94.81, 2.35, 140.44, 150., 138.72, 295.25, 50., 110.97, 4.87,
    45., 60., 90., 66.17, 78.68, 75.87, 8.95, 65., 1.3, 5.83, 44.13, 59.65,
    102.52, 108.45, 70., 70., 70., 70., 68., 7.92, 36.34, 30.3, 93.69, 146.81,
    79., 100., 70., 61.79, 38.42, 19.41, 45.45, 7.39, 223.55, 45., 90., 90.,
    75.21, 45., 130., 17.44, 75., 69.9, 112.74, 126.36, 40., 30., 1.88, 46.2,
    2.99, 48.69, 21.74, 98.39, 65., 147.98, 25., 45., 5.38
};

// As number of days since 1.1.1970.
static const QVector<double> exampleDateSeries
{
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

static QGroupBox* wrapPlot(const QString& name,
                           QWidget* widget)
{
    auto groupBox = new QGroupBox(name);
    auto layout = new QVBoxLayout();
    layout->addWidget(widget);
    groupBox->setLayout(layout);
    return groupBox;
}

static QuantilesPlot* createQuantilesPlot()
{
    auto quantilesPlot = new QuantilesPlot();
    Quantiles quantiles;
    quantiles.computeQuantiles(exampleValues.first());
    quantilesPlot->setAxisScale(QwtPlot::xBottom, 0, 2);
    quantilesPlot->setNewData(quantiles);
    return quantilesPlot;
}

static GroupPlot* createGroupPlot()
{
    QVector<Quantiles> quantilesVector;
    for (auto& values : exampleValues)
    {
        Quantiles quantiles;
        quantiles.computeQuantiles(values);
        quantilesVector.push_back(quantiles);
    }
    auto groupPlot = new GroupPlot();
    groupPlot->setAxisScale(QwtPlot::yLeft, 0, 8);
    groupPlot->setAxisScale(QwtPlot::yRight, 0, 8);
    groupPlot->setAxisScale(QwtPlot::xBottom, 0.5, exampleValues.size() + 0.5, 1);
    groupPlot->setNewData(quantilesVector, exampleNames);
    return groupPlot;
}

static HistogramPlot* createHistogramPlot()
{
    Quantiles quantiles;
    QVector<double> dataForQuantiles(examplePriceSeries);
    quantiles.computeQuantiles(dataForQuantiles);
    auto histogramPlot = new HistogramPlot();
    QVector<double> plotData;
    for (const auto& item : examplePriceSeries)
        plotData.append(item);
    histogramPlot->setNewData(std::move(plotData), std::move(quantiles), 10);
    return histogramPlot;
}

static HistogramPlotUI* createHistogramPlotUI()
{
    Quantiles quantiles;
    QVector<double> dataForQuantiles(examplePriceSeries);
    quantiles.computeQuantiles(dataForQuantiles);
    auto histogramPlotUI = new HistogramPlotUI();
    QVector<double> plotData;
    for (const auto& item : examplePriceSeries)
        plotData.append(item);
    histogramPlotUI->dataChanged(std::move(plotData), std::move(quantiles));
    return histogramPlotUI;
}

static BasicDataPlot* createBasicDataPlot()
{
    Quantiles quantiles;
    QVector<double> dataForQuantiles(examplePriceSeries);
    quantiles.computeQuantiles(dataForQuantiles);
    auto basicDataPlot = new BasicDataPlot();
    const auto [min, max] =
        std::minmax_element(exampleDateSeries.begin(), exampleDateSeries.end());
    quantiles.minX_ = *min;
    quantiles.maxX_ = *max;
    basicDataPlot->setAxisScale(QwtPlot::xBottom, *min, *max);
    const QVector<QPointF> linearRegressionPoints
    {
        {*min, 38.002},
        {*max, 78.4491}
    };

    QVector<QPointF> data;
    for (int i = 0; i < examplePriceSeries.size(); ++i)
        data.append({exampleDateSeries[i], examplePriceSeries[i]});
    basicDataPlot->setNewData(std::move(data),
                              quantiles,
                              linearRegressionPoints);
    return basicDataPlot;
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

    QWidget widget;
    QVBoxLayout widgetLayout(&widget);

    QSplitter* upperSplitter = new QSplitter(&widget);
    upperSplitter->addWidget(wrapPlot("Quantiles plot", createQuantilesPlot()));
    upperSplitter->addWidget(wrapPlot("Grouping plot", createGroupPlot()));
    widgetLayout.addWidget(upperSplitter);

    QSplitter* lowerSplitter = new QSplitter(&widget);
    lowerSplitter->addWidget(wrapPlot("Histogram plot", createHistogramPlot()));
    lowerSplitter->addWidget(wrapPlot("Histogram plot UI", createHistogramPlotUI()));
    lowerSplitter->addWidget(wrapPlot("Basic data plot", createBasicDataPlot()));
    lowerSplitter->setStretchFactor(0, 1);
    lowerSplitter->setStretchFactor(1, 1);
    lowerSplitter->setStretchFactor(2, 2);
    widgetLayout.addWidget(lowerSplitter);

    widget.setLayout(&widgetLayout);
    widget.resize(1000, 750);
    widget.show();

    return QApplication::exec();
}
