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
    QVector<float> exampleValues {3.5F, 6.7F, 4.7F, 6.6F, 3.F, 4.9F};
    quantiles.computeQuantiles(exampleValues);
    quantilesPlot->setNewData(quantiles);
    return quantilesPlot;
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

    QWidget widget;
    QHBoxLayout widgetLayout(&widget);
    widgetLayout.addWidget(wrapPlot("Quantiles plot", createQuantilesPlot()));
    widget.setLayout(&widgetLayout);
    widget.show();
    widget.resize(250, 500);

    return QApplication::exec();
}
