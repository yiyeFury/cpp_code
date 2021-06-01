//
// Created by xie on 2021/6/1.
//
#include "solar_position.h"


double CalculateJulianDay(int y, int m, int d, int hh=0, int mm=0, int ss=0)
{
    /* utc
     * y: year
     * m: month
     * d: day of month
     * hh: hour of day
     * mm: minute
     * ss: second
     */

    /*
    Meeus, J. “Astronomical Algorithms”. Second edition 1998, Willmann-Bell, Inc.,Richmond, Virginia, USA.
    ---Chapter7 Julian Day
    */
    double jd, D;
    int A, B;

    if (m <= 2) {
        y -= 1;
        m += 12;
    }

    // the day of the month(with decimal, if any)
    D = d + ((ss/60.0 + mm)/60.0 + hh)/24.0;

    // in the Gregorian calendar
    A = int(y/100);
    B = 2 - A + int(A/4);
    jd = int(365.25*(y + 4716)) + int(30.6001*(m+1)) + D + B - 1524.5;
    return jd;
}

bool IsLeapYear(int y)
{
    // 计算是否为闰年
    bool cond1, cond2;
    cond1 = (y % 4 == 0) && (y % 100 != 0);
    cond2 = y % 400 == 0;

    if (cond1 || cond2)
        return true;
    else
        return false;
}

int DayOfYear(int y, int m, int d)
{
    bool is_leap;
    int k, n;

    is_leap = IsLeapYear(y);
    k = is_leap? 1:2;
    n = int(275*m/9.0) - k*int((m+9)/12.0)+d-30;
    return n;
}