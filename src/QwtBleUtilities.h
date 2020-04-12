#ifndef UTILITIES_H
#define UTILITIES_H

#include <QDate>
#include <QString>

#include "qwtble_global.h"

namespace QwtBleUtilities
{
/**
 * @brief Calculate date 1/1/1970 + given days and return string representation.
 * @param daysToAdd Number of days to add.
 * @return Date as string.
 **/
QString QWTBLE_EXPORT stringFromDays(int daysToAdd);

/**
 * @brief Date 1/1/1970 used as reference conversions.
 * @return Date 1/1/1970.
 */
QDate QWTBLE_EXPORT getStartOfTheWorld();

/**
 * @brief Get default formatting which should be used.
 * @return Default formatting as string.
 */
QString QWTBLE_EXPORT getDefaultDateFormat();

/**
 * @brief Check if 2 given doubles are equal.
 * @param left Left double.
 * @param right Right double.
 * @return True when equal, false otherwise.
 */
bool QWTBLE_EXPORT doublesAreEqual(double left, double right);

/**
 * @brief Check if 2 given floats are equal.
 * @param left Left float.
 * @param right Right float.
 * @return True when equal, false otherwise.
 */
bool QWTBLE_EXPORT floatsAreEqual(float left, float right);

/**
 * @brief Visualize given number as string using localization formatting.
 * @param value Double value to visualize.
 * @param precision Precision for visualization.
 * @return Double value as string created using locale.
 **/
QString QWTBLE_EXPORT doubleToStringUsingLocale(double value, int precision);

static constexpr int BIG_TRANSPARENCY_FACTOR{50};
static constexpr int SMALL_TRANSPARENCY_FACTOR{200};

/// Values used to enforce drawing order of items on plots.
static constexpr int LOW_ORDER{1};
static constexpr int MEDIUM_ORDER{2};
static constexpr int HIGH_ORDER{3};

static constexpr double DEFAULT_LABEL_ROTATION{-50.0};
}  // namespace QwtBleUtilities

#endif  // UTILITIES_H
