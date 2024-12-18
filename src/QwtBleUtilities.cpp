#include <qwtble/QwtBleUtilities.h>

#include <QLocale>

namespace QwtBleUtilities
{
QString stringFromDays(int daysToAdd)
{
    static const QDate startOfTheWorld{getStartOfTheWorld()};
    return startOfTheWorld.addDays(daysToAdd).toString(getDefaultDateFormat());
}

QDate getStartOfTheWorld() { return {1970, 1, 1}; }

QString getDefaultDateFormat() { return QStringLiteral("d/M/yyyy"); }

bool doublesAreEqual(double left, double right)
{
    static const double qtDoublePrecision{1e-12};
    return std::abs(left - right) <=
           qtDoublePrecision * std::max({1.0, std::abs(left), std::abs(right)});
}

bool floatsAreEqual(float left, float right)
{
    static const float qtFloatPrecision{1e-6F};
    return std::abs(left - right) <=
           qtFloatPrecision * std::max({1.0F, std::abs(left), std::abs(right)});
}

QString doubleToStringUsingLocale(double value, int precision)
{
    static bool initialized{false};
    static QLocale locale = QLocale::system();
    if (!initialized)
    {
        locale.setNumberOptions(locale.numberOptions() &
                                ~QLocale::OmitGroupSeparator);
        initialized = true;
    }

    return locale.toString(value, 'f', precision);
}
}  // namespace QwtBleUtilities
