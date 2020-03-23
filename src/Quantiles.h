#ifndef QUANTILES_H
#define QUANTILES_H

#include <array>

#include <QVector>
#include <QString>

#include "qwtble_global.h"

/**
 * @brief Quantiles struct. Computes, creates tooltip display, stores values.
 */
struct QWTBLE_EXPORT Quantiles
{
public:
    Quantiles() = default;

    ~Quantiles() = default;

    Quantiles& operator=(const Quantiles& other) = default;
    Quantiles(const Quantiles& other) = default;

    Quantiles& operator=(Quantiles&& other) = default;
    Quantiles(Quantiles&& other) = default;

    //Y axis variables.
    double min_ {.0};
    double q10_ {.0};
    double q25_ {.0};
    double q50_ {.0};
    double q75_ {.0};
    double q90_ {.0};
    double max_ {.0};

    int number_ {0};
    double avg_ {.0};
    double stdDev_ {.0};

    //X axis variables.
    double minX_ {.0};
    double maxX_ {.0};

    void clear();

    void print();

    void computeQuantiles(QVector<double>& valuePerUnit);

    QString getValuesAsToolTip() const;

private:
    enum PlotInfo : int
    {
        PLOT_INFO_COUNT = 0,
        PLOT_INFO_MIN,
        PLOT_INFO_Q10,
        PLOT_INFO_Q25,
        PLOT_INFO_Q50,
        PLOT_INFO_Q75,
        PLOT_INFO_Q90,
        PLOT_INFO_MAX,
        PLOT_INFO_AVG,
        PLOT_INFO_STD_DEV,
        PLOT_INFO_END
    };

    static std::array<QString, PLOT_INFO_END> getPlotInfoNames();

    static QString valueAsHtmlRow(PlotInfo name, double value);
};

#endif // QUANTILES_H
