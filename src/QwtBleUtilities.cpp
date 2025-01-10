#include <qwtble/QwtBleUtilities.h>

#include <QLocale>

namespace qwt_ble_utilities
{
QString stringFromDays(int daysToAdd)
{
    static const QDate startOfTheWorld{getStartOfTheWorld()};
    return startOfTheWorld.addDays(daysToAdd).toString(getDefaultDateFormat());
}

QDate getStartOfTheWorld()
{
    QDate startOfTheWorld{1970, 1, 1};
    return startOfTheWorld;
}

QString getDefaultDateFormat() { return QStringLiteral("d/M/yyyy"); }

bool doublesAreEqual(double left, double right)
{
    static const double qtDoublePrecision{1e-12};
    return std::abs(left - right) <=
           (qtDoublePrecision *
            std::max({1.0, std::abs(left), std::abs(right)}));
}

bool floatsAreEqual(float left, float right)
{
    static const float qtFloatPrecision{1e-6F};
    return std::abs(left - right) <=
           (qtFloatPrecision *
            std::max({1.0F, std::abs(left), std::abs(right)}));
}

QString doubleToStringUsingLocale(double value, int precision)
{
    QLocale locale{QLocale::system()};
    locale.setNumberOptions(locale.numberOptions() &
                            ~QLocale::OmitGroupSeparator);

    return locale.toString(value, 'f', precision);
}
}  // namespace qwt_ble_utilities
