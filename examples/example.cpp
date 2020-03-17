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
    15.85F, 26.77F, 51.61F, 144.44F, 106.F, 8.06F, 92.5F, 19.57F, 91.44F, 90.F,
    75.F, 39.56F, 0.2F, 25.F, 80.F, 54.86F, 2.13F, 4.84F, 15.F, 2.67F, 95.F,
    100.F, 5.F, 5.F, 96.38F, 1.99F, 75.08F, 93.37F, 99.82F, 94.81F, 2.35F,
    140.44F, 150.F, 138.72F, 295.25F, 50.F, 110.97F, 4.87F, 45.F, 60.F, 90.F,
    66.17F, 78.68F, 75.87F, 8.95F, 65.F, 1.3F, 5.83F, 44.13F, 59.65F, 102.52F,
    108.45F, 70.F, 70.F, 70.F, 70.F, 68.F, 7.92F, 36.34F, 30.3F, 93.69F,
    146.81F, 79.F, 100.F, 70.F, 61.79F, 38.42F, 19.41F, 45.45F, 7.39F, 223.55F,
    45.F, 90.F, 90.F, 75.21F, 45.F, 130.F, 17.44F, 75.F, 69.9F, 112.74F,
    126.36F, 40.F, 30.F, 1.88F, 46.2F, 2.99F, 48.69F, 21.74F, 98.39F, 65.F,
    147.98F, 25.F, 45.F, 5.38F
};

// As number of days since 1.1.1970.
static const QVector<float> exampleDateSeries
{
    13959.F, 13941.F, 13984.F, 13914.F, 13999.F, 13979.F, 13945.F, 13999.F,
    14013.F, 13972.F, 13992.F, 13969.F, 13951.F, 13970.F, 13951.F, 13970.F,
    13986.F, 13993.F, 14011.F, 13969.F, 13977.F, 14026.F, 13990.F, 13916.F,
    13972.F, 13999.F, 13980.F, 13956.F, 13977.F, 14019.F, 14028.F, 13999.F,
    13950.F, 13950.F, 14011.F, 14011.F, 14026.F, 13965.F, 14032.F, 14008.F,
    13951.F, 14012.F, 13991.F, 14007.F, 14019.F, 13980.F, 13997.F, 14042.F,
    13985.F, 13991.F, 13986.F, 13972.F, 13965.F, 13949.F, 13990.F, 14035.F,
    14008.F, 14019.F, 13964.F, 13957.F, 14033.F, 14014.F, 13980.F, 13980.F,
    13980.F, 13980.F, 13980.F, 13992.F, 13999.F, 13943.F, 13997.F, 13920.F,
    13977.F, 13944.F, 13986.F, 13956.F, 13966.F, 13951.F, 14032.F, 14027.F,
    13993.F, 13980.F, 13986.F, 13986.F, 13983.F, 13955.F, 13941.F, 14013.F,
    14042.F, 14039.F, 14042.F, 13937.F, 13914.F, 13915.F, 13930.F, 13845.F,
    13864.F, 13857.F, 13867.F, 13929.F, 13972.F, 13910.F, 13924.F, 13924.F,
    13927.F};

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

static double* getRawData(QVector<float> data)
{
    int numberOfItems {data.size()};
    double* rawData = new double[static_cast<unsigned long long>(numberOfItems)];
    for (int i = 0; i < examplePriceSeries.size();  ++i)
        rawData[i] = static_cast<double>(data[i]);
    return rawData;
}

static HistogramPlot* createHistogramPlot()
{
    Quantiles quantiles;
    QVector<float> dataForQuantiles(examplePriceSeries);
    quantiles.computeQuantiles(dataForQuantiles);
    auto histogramPlot = new HistogramPlot();
    const int numberOfItems {examplePriceSeries.size()};
    PlotData plotData(getRawData(exampleDateSeries),
                      getRawData(examplePriceSeries),
                      numberOfItems);
    histogramPlot->setNewData(plotData, quantiles, 10);
    return histogramPlot;
}

static BasicDataPlot* createBasicDataPlot()
{
    Quantiles quantiles;
    QVector<float> dataForQuantiles(examplePriceSeries);
    quantiles.computeQuantiles(dataForQuantiles);
    auto basicDataPlot = new BasicDataPlot();
    const auto [min, max] =
        std::minmax_element(exampleDateSeries.begin(), exampleDateSeries.end());
    quantiles.minX_ = *min;
    quantiles.maxX_ = *max;
    basicDataPlot->setAxisScale(QwtPlot::xBottom,
                                static_cast<double>(*min),
                                static_cast<double>(*max));
    const QVector<QPointF> linearRegressionPoints
    {
        {static_cast<double>(*min), 38.002},
        {static_cast<double>(*max), 78.4491}
    };
    const int numberOfItems {examplePriceSeries.size()};
    PlotData plotData(getRawData(exampleDateSeries),
                      getRawData(examplePriceSeries),
                      numberOfItems);
    basicDataPlot->setNewData(plotData,
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
