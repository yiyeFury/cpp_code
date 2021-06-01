//
// Created by xie on 2021/6/1.
//

#ifndef CPP_CODE_SOLAR_POSITION_H
#define CPP_CODE_SOLAR_POSITION_H

#endif //CPP_CODE_SOLAR_POSITION_H

/*
 Solar Position Algorithm for Solar Radiation Applications
 (https://www.nrel.gov/docs/fy08osti/34302.pdf)

 mean solar day: 平太阳日
 Terrestrial Time: 地球时，现代在地球表面上的时间标准
 heliocentric: 日心的
 apparent sidereal time: 真恒星时
 mean sidereal time: 平恒星时
 sun right ascension: 太阳赤经
 sun declination: 太阳赤纬
 hour angle: 时角
 topocentric: 站心的
 equatorial horizontal parallax: 赤道地平视差

*/

double CalculateJulianDay(int y, int m, int d, int hh, int mm, int ss);
bool IsLeapYear(int y);
int DayOfYear(int y, int m, int d);