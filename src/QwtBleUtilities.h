#ifndef UTILITIES_H
#define UTILITIES_H

#include <QDate>
#include <QString>

#include "qwtble_global.h"

namespace QwtBleUtilities
{
/**
 * Calculate date 1/1/1970 + given days and return string.
 * @param daysToAdd amount of days to add.
 * @return date in for of string.
 **/
QString QWTBLE_EXPORT stringFromDays(int daysToAdd);

///Date 1/1/1970 used as reference for dates conversion.
const QWTBLE_EXPORT QDate& getStartOfTheWorld();

QString QWTBLE_EXPORT getDefaultDateFormat();

bool QWTBLE_EXPORT doublesAreEqual(double left, double right);
bool QWTBLE_EXPORT floatsAreEqual(float left, float right);

/**
 * Visualize given number as string using localization options/format.
 * @param value number to visualize.
 * @param precison precision for visualization.
 * @return number as string conveted using locale.
 **/
QString QWTBLE_EXPORT doubleToStringUsingLocale(double value, int precison);

static constexpr int BIG_TRANSPARENCY_FACTOR {50};
static constexpr int SMALL_TRANSPARENCY_FACTOR {200};

/// Values used to enforce drawing order of items on plots.
static constexpr int LOW_ORDER{1};
static constexpr int MEDIUM_ORDER{2};
static constexpr int HIGH_ORDER{3};

static constexpr double DEFAULT_LABEL_ROTATION {-50.0};
}

#endif // UTILITIES_H
