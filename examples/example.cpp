#include <QApplication>
#include <QGroupBox>
#include <QStyleFactory>
#include <QWidget>
#include <QVBoxLayout>

#include <BasicDataPlot.h>
#include <GroupPlot.h>
#include <HistogramPlot.h>
#include <PlotBase.h>
#include <QuantilesPlot.h>

static QVector<QVector<float>> exampleValues {{3.5F, 6.7F, 4.7F, 6.6F, 3.F, 4.9F},
    {5.5F, 1.2F, 3.2F, 7.6F, 5.F, 4.9F, 0.3F, 7.3F},
    {2.1F, 1.7F, 4.3F, 6.6F, 1.F, 3.9F, 5.5F}};
static QVector<QString> exampleNames {"first", "second", "third"};

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
    groupPlot->setAxisScale(QwtPlot::xBottom, 0, exampleValues.size() + 1, 1);
    groupPlot->setNewData(quantilesVector, exampleNames);
    return groupPlot;
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

    QWidget widget;
    QHBoxLayout widgetLayout(&widget);
    widgetLayout.addWidget(wrapPlot("Quantiles plot", createQuantilesPlot()));
    widgetLayout.addWidget(wrapPlot("Grouping plot", createGroupPlot()));
    widget.setLayout(&widgetLayout);
    widget.show();
    widget.resize(500, 500);

    return QApplication::exec();
}
