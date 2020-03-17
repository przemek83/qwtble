#include <QApplication>
#include <QGroupBox>
#include <QStyleFactory>
#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>

#include <BasicDataPlot.h>
#include <GroupPlot.h>
#include <HistogramPlot.h>
#include <PlotBase.h>
#include <QuantilesPlot.h>
#include <QwtBleUtilities.h>

static QVector<QVector<float>> exampleValues {{3.5F, 6.7F, 4.7F, 6.6F, 3.F, 4.9F},
    {5.5F, 1.2F, 3.2F, 7.6F, 5.F, 4.9F, 0.3F, 7.3F},
    {2.1F, 1.7F, 4.3F, 6.6F, 1.F, 3.9F, 5.5F},
    {1.1F, 3.2F, 3.8F, 6.5F, 2.F, 2.9F, 7.5F, 3.2F, 5.5F},
    {2.1F, 1.7F, 4.3F, 6.1F, 2.F}};
static QVector<QString> exampleNames {"first", "second", "third", "fourth", "fifth"};

static const QVector<float> examplePriceSeries
{
    84.66F, 40.F, 5.F, 7.02F, 177.01F, 110.23F, 138.12F, 54.94F, 20.F, 80.F,
    15.85F, 26.77F, 51.61F, 144.44F, 106.F, 8.06F, 92.5F, 19.57F, 91.44F,
    90.F, 75.F, 39.56F, 0.2F, 25.F, 80.F, 54.86F, 2.13F, 4.84F, 15.F,
    2.67F, 95.F, 100.F, 5.F, 5.F, 96.38F, 1.99F, 75.08F, 93.37F, 99.82F,
    94.81F, 2.35F, 140.44F, 150.F, 138.72F, 295.25F, 50.F, 110.97F, 4.87F,
    45.F, 60.F, 90.F, 66.17F, 78.68F, 75.87F, 8.95F, 65.F, 1.3F, 5.83F,
    44.13F, 59.65F, 102.52F, 108.45F, 70.F, 70.F, 70.F, 70.F, 68.F, 7.92F,
    36.34F, 30.3F, 93.69F, 146.81F, 79.F, 100.F, 70.F, 61.79F, 38.42F,
    19.41F, 45.45F, 7.39F, 223.55F, 45.F, 90.F, 90.F, 75.21F, 45.F, 130.F,
    17.44F, 75.F, 69.9F, 112.74F, 126.36F, 40.F, 30.F, 1.88F, 46.2F, 2.99F,
    48.69F, 21.74F, 98.39F, 65.F, 147.98F, 25.F, 45.F, 5.38F
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
                           PlotBase* plot)
{
    auto groupBox = new QGroupBox(name);
    auto layout = new QVBoxLayout();
    layout->addWidget(plot);
    groupBox->setLayout(layout);
    return groupBox;
}

static QuantilesPlot* createQuantilesPlot()
{
    auto quantilesPlot = new QuantilesPlot();
    Quantiles quantiles;
    quantiles.computeQuantiles(exampleValues.first());
    quantilesPlot->setAxisScale(QwtPlot::xBottom, 0, 2, 0);
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
    QVector<float> dataForQuantiles(examplePriceSeries);
    quantiles.computeQuantiles(dataForQuantiles);
    auto histogramPlot = new HistogramPlot();
    const int numberOfItems {examplePriceSeries.size()};
    double* dataX = new double[static_cast<unsigned long long>(numberOfItems)];
    double* dataY = new double[static_cast<unsigned long long>(numberOfItems)];
    for (int i = 0; i < examplePriceSeries.size();  ++i)
        dataY[i] = static_cast<double>(examplePriceSeries[i]);
    PlotData plotData(dataX, dataY, numberOfItems);
    histogramPlot->setNewData(plotData, quantiles, 10);
    return histogramPlot;
}

static BasicDataPlot* createBasicDataPlot()
{
    Quantiles quantiles;
    QVector<float> dataForQuantiles(examplePriceSeries);
    quantiles.computeQuantiles(dataForQuantiles);
    auto basicDataPlot = new BasicDataPlot();
    const int numberOfItems {examplePriceSeries.size()};
    double* dataX = new double[static_cast<unsigned long long>(numberOfItems)];
    for (int i = 0; i < exampleDateSeries.size(); ++i)
        dataX[i] = exampleDateSeries[i];
    double* dataY = new double[static_cast<unsigned long long>(numberOfItems)];
    for (int i = 0; i < examplePriceSeries.size(); ++i)
        dataY[i] = static_cast<double>(examplePriceSeries[i]);
    const auto [min, max] = std::minmax_element(exampleDateSeries.begin(), exampleDateSeries.end());
    quantiles.minX_ = static_cast<float>(*min);
    quantiles.maxX_ = static_cast<float>(*max);
    basicDataPlot->setAxisScale(QwtPlot::xBottom, *min, *max);
    PlotData plotData(dataX, dataY, numberOfItems);
    basicDataPlot->setNewData(plotData, quantiles, {{13845, 38.002}, {14042, 78.4491}});
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
    upperSplitter->addWidget(wrapPlot("Histogram plot", createHistogramPlot()));
    upperSplitter->setSizes({200, 600});
    widgetLayout.addWidget(upperSplitter);
    QSplitter* lowerSplitter = new QSplitter(&widget);
    lowerSplitter->addWidget(wrapPlot("Grouping plot", createGroupPlot()));
    lowerSplitter->addWidget(wrapPlot("Basic data plot", createBasicDataPlot()));
    lowerSplitter->setSizes({300, 500});
    widgetLayout.addWidget(lowerSplitter);
    widget.setLayout(&widgetLayout);
    widget.show();
    widget.resize(800, 600);

    return QApplication::exec();
}
