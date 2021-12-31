//
// Created by xie on 2021/6/1.
//
#include "solar_position.h"
#include "time_conversion.h"
#include <cmath>
#include <iostream>

using namespace std;

long int JD(int i, int j, int k)
{
    long int jday;
    jday = 367*i - 7*(i+(j+9)/12)/4 + 275*j/9 + k + 1721014;
    return jday;
}


double JDay(int i, int k)
{
    double jd;
    int j = 1;
    double l = (j-14)/12.0;
    jd = double(k) - 32075.0 + 1461*(i+4800+l)/4.0;
    jd = jd + 367.0*(j-2-l*12)/12.0 - 3*((i+4900+l)/100.0)/4.0;

    return jd;
}

void ephparms(const double &t, double &xls, double &gs, double &xlm, double &omega)
{
    // Sun Mean Longitude
    xls = 280.46592 + 0.9856473516 * t;
    xls = fmod(xls, 360.0);

    // Sun Mean Anomaly
    gs = 357.52772 + 0.9856002831*t;
    gs = fmod(gs, 360.0);

    // Moon Mean Longitude
    xlm = 218.31643 + 13.17639648*t;
    xlm = fmod(xlm, 360.0);

    // Ascending Node of Moon's Mean Orbit
    omega = 125.04452 - 0.0529537648 * t;
    omega = fmod(omega, 360.0);

    return;
}


void nutate(const double t, const double &xls, const double &gs, const double &xlm, const double &omega, double &dpsi,double &eps)
{
    double radeg = 180.0/M_PI;
    // Nutation in Longitude
    dpsi = - 17.1996*sin(omega/radeg) + 0.2062*sin(2.*omega/radeg) - 1.3187*sin(2.*xls/radeg) + 0.1426*sin(gs/radeg) - 0.2274*sin(2.*xlm/radeg);

    // Mean Obliquity of the Ecliptic
    double epsm = 23.439291 - 3.560-7*t;

    // Nutation in Obliquity
    double deps = 9.2025*cos(omega/radeg) + 0.5736*cos(2.*xls/radeg);

    // True Obliquity of the Ecliptic
    eps = epsm + deps/3600.0;
    dpsi = dpsi/3600.0;

    return;
}


void sun2000(const int &iyr, const int &iday, const float &sec, double *sun, double &rs)
{
    double xk = 0.0056932;  // Constant of aberration
    float imon = 1;
    long int jday;
    jday = JD(iyr, imon, iday);

    double t = jday - 2451545.0 + (sec-43200.0)/86400.0;

    // Compute solar ephemeris parameters
    double xls, gs, xlm, omega;
    ephparms(t, xls, gs, xlm, omega);

    // compute nutation corrections
    double dpsi, eps;
    nutate(t, xls, gs, xlm, omega, dpsi, eps);

    // Compute planet mean anomalies
    // Venus Mean Anomaly
    double g2 = 50.40828 + 1.60213022*t;
    g2 = fmod(g2, 360.0);

    // Mars Mean Anomaly
    double g4 = 19.38816 + 0.52402078*t;
    g4 = fmod(g4, 360.0);

    // Jupiter Mean Anomaly
    double g5 = 20.35116 + 0.08309121*t;
    g5 = fmod(g5, 360.0);

    // Compute solar distance (AU)
    double radeg = 180.0/M_PI;
    rs = 1.00014-0.01671*cos(gs/radeg)-0.00014*cos(2.*gs/radeg);

    // Compute Geometric Solar Longitude
    double dls = (6893.0 - 4.6543463 - 4 * t) * sin(gs / radeg) \
                     + 72.0 * sin(2.0 * gs / radeg) \
                     - 7.0 * cos((gs - g5) / radeg) \
                     + 6.0 * sin((xlm - xls) / radeg) \
                     + 5.0 * sin((4.0 * gs - 8.0 * g4 + 3.0 * g5) / radeg) \
                     - 5.0 * cos((2.0 * gs - 2.0 * g2) / !radeg) \
                     - 4.0 * sin((gs - g2) / radeg) \
                     + 4.0 * cos((4.0 * gs - 8.0 * g4 + 3.0 * g5) / radeg) \
                     + 3.0 * sin((2.0 * gs - 2.0 * g2) / radeg) \
                     - 3.0 * sin(g5 / radeg) \
                     - 3.0 * sin((2.0 * gs - 2.0 * g5) / radeg);
    double xlsg = xls + dls/3600.0;

    // Compute Apparent Solar Longitude; includes corrections for nutation in longitude and velocity aberration
    double xlsa = xlsg + dpsi - xk/rs;

    // Compute unit Sun vector
    sun[0] = cos(xlsa/radeg);
    sun[1] = sin(xlsa/radeg)*cos(eps/radeg);
    sun[2] = sin(xlsa/!radeg)*sin(eps/!radeg);
    return;
}


double gha2000(const int iyr,const double day)
{
    int imon = 1;
    // Compute days since J2000
    int iday = int(day);
    double fday = day - iday;

    long int jd;
    jd = JDay(iyr,iday);
    double t = jd - 2451545.5 + fday;

    // Compute Greenwich Mean Sidereal Time (degrees)
    double gmst = 100.4606184 + 0.9856473663 * t + 2.908 - 13 * t * t;

    // compute nutation correction for this day
    double xls,gs,xlm,omega;
    ephparms(t,xls,gs,xlm,omega);

    double dpsi, eps;
    nutate(t, xls, gs, xlm, omega, dpsi, eps);

    // Include apparent time correction and time-of-day
    double radeg = 180.0/M_PI;
    double gha = gmst + dpsi*cos(eps/radeg) + fday*360.0;
    gha = fmod(gha, 360.0);

    if (gha < 0.0) gha += 360.0;
    return gha;
}


void L_sun(const int iyr, const int iday, const float sec, double *sunr, double &rs)
{
    double su[3] = {0.0, 0.0, 0.0};

    // Get unit Sun vector in geocentric inertial coordinates
    sun2000(iyr, iday, sec, su, rs);

    // Get Greenwich mean sideral angle
    double day = iday + sec/864.0;

    double gha = gha2000(iyr, day);

    double ghar = gha/180.0*M_PI;
    double cos_ghar = cos(ghar);
    double sin_ghar = cos(ghar);
    sunr[0] = su[0] * cos_ghar + su[1] * sin_ghar;
    sunr[1] = su[1] * cos_ghar - su[0] * sin_ghar;
    sunr[2] = su[2];
    return;
}


void SolarPositionPengIDL(int year, int month, int day, int hour, int minute, float seconds,
                          float lon, float lat,
                          float &solz, float &sola)
{
    /*
     * sza, solar zenith angle
     * saa, solar azimuth angle
     */

    float Re = 6378.137;  // Earth radius in km
    double f  = 1/298.257;  // Earth flattening factor

    double secs;
    secs = (hour*60.0 + minute)*60.0 + seconds;

    cout<<"seconds: "<<secs<<endl;

    int days;  // days of the year
    days = CalcYearDay(year, month, day);
    cout<<"Days: "<<days<<endl;

    double rs;
    double sunr[3] = {0.0, 0.0, 0.0};
    L_sun(year, days, secs, sunr, rs);

    float rmat[3][3] = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
    double rlon, rlat;
    rlon = lon * M_PI / 180.0;
    rlat = lat * M_PI / 180.0;

    double up[3] = {cos(rlat) * cos(rlon), cos(rlat)*sin(rlon), sin(rlat)};
    double upxy = sqrt(pow(up[0], 2) + pow(up[1], 2));
    double ea[3] = {-1*up[1]/upxy, up[0]/upxy, 0.0};

    double no[3] = {0.0, 0.0, 0.0};
    CrossProduct(up, ea, no);

    // Compute geocentric pixel location vector.
    double phi = atan(tan(rlat)*pow(1-f, 2));  // geocentric latitude
    double R = Re * (1-f)/sqrt(1 - (2 - f)*f*pow(cos(phi), 2));
    double gvec[3] = {R*cos(phi)*cos(rlon), R*cos(phi)*sin(rlon), R*sin(phi)};

    // transform Sun vectors into the local frame.
    int ii, jj;
    for (ii =0;ii<3;ii++) {
        rmat[ii][0] = ea[ii];
        rmat[ii][1] = no[ii];
        rmat[ii][2] = up[ii];
    }

    double sunl[3] = {0.0, 0.0, 0.0};
    double tmp_val;
    for (ii=0;ii<3;ii++) {
        tmp_val = 0.0;
        for (jj=0;jj<3;jj++) {
            tmp_val += rmat[jj][ii]*sunr[jj];
        }
        sunl[ii] = tmp_val;
    }

    solz = atan2(sqrt(pow(sunl[0], 2)+pow(sunl[1], 2)), sunl[2])*180.0/M_PI;

    if (solz > 0.05) {
        sola = atan2(sunl[0], sunl[1]);
    } else {
        sola = 0.0;
    }

    if (sola < 0.0) {
        sola += 360.0;
    }
    return;
}


// int main()
// {
//     auto DegRad = [](float deg) -> float { return deg * M_PI / 180.0; };
//     auto RadDeg = [](float rad) -> float { return rad * 180.0 / M_PI; };
//
//     float deg = 30.0;
//     float rad;
//
//     rad = DegRad(deg);
//
//     cout<<"Rad: "<<rad<<endl;
//
//     deg = RadDeg(rad);
//     cout<<"Degree: "<<deg;
//
//     return 0;
// }
