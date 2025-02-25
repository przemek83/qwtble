#pragma once

#include <array>

#include <QMetaType>
#include <QString>
#include <QVector>

#include "qwtble_global.h"

/// @class Quantiles
/// @brief Struct for min, max, mean, quantiles and std dev.
struct QWTBLE_EXPORT Quantiles
{
public:
    // Y axis variables.
    double min_{.0};
    double q10_{.0};
    double q25_{.0};
    double q50_{.0};
    double q75_{.0};
    double q90_{.0};
    double max_{.0};

    int count_{0};
    double mean_{.0};
    double stdDev_{.0};

    // X axis variables.
    double minX_{.0};
    double maxX_{.0};

    void clear();

    /// @brief Initialize structure using given values.
    /// @param values Values using which struct is filled.
    void init(QVector<double> values);

    /// @brief Generate HTML like tooltip from current values.
    /// @return HTML like tool tip.
    QString getValuesAsToolTip() const;

private:
    static double computeQuantile(const QVector<double>& values,
                                  double interval);
    static double calculateStdDev(int count, double ex, double ex2);
    void setQuantiles(const QVector<double>& values);
    std::tuple<double, double> calculateEXAndEX2(
        const QVector<double>& values) const;

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
        PLOT_INFO_MEAN,
        PLOT_INFO_STD_DEV,
        PLOT_INFO_END
    };

    static std::array<QString, PLOT_INFO_END> getPlotInfoNames();

    static QString valueAsHtmlRow(PlotInfo name, double value);
};

Q_DECLARE_METATYPE(Quantiles);

Q_DECLARE_TYPEINFO(Quantiles, Q_MOVABLE_TYPE);
