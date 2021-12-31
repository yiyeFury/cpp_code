//
// Created by xie on 2021/12/30.
//

#include <cmath>
#include "normalized_geostationary_projection.h"

#include <iostream>

using namespace std;

NormGeostationaryProjection::NormGeostationaryProjection(float lon,
                                                         float coff,
                                                         long int cfac,
                                                         float loff,
                                                         long int lfac): sub_lon(lon), COFF(coff), CFAC(cfac), LOFF(loff), LFAC(lfac)
{}


void NormGeostationaryProjection::ScaleFunc(double x, double y, float &col, float &row)
{
    double xd, yd;  // 将x、y转为角度
    xd = x/M_PI*180;
    yd = y/M_PI*180;

    double val;
    val = pow(2, -16);

    col = COFF + round(xd * val *CFAC);
    row = LOFF + round(yd * val * LFAC);
}

void NormGeostationaryProjection::ScaleFuncInv(float col, float row, double &x, double &y)
{
    double val;
    val = pow(2, -16);

    double xx ,yy;
    xx = (col - COFF) / CFAC / val;
    yy = (row - LOFF) / LFAC / val;

    double xr, yr;  // 转为弧度
    xr = xx / 180.0*M_PI;
    yr = yy / 180.0*M_PI;

    x = xr, y=yr;
}

void NormGeostationaryProjection::GeoToImage(float lon, float lat, float &col, float &row)
{
    double sub_lonR, lonR, latR;
    sub_lonR = sub_lon * M_PI / 180.0;
    lonR = lon * M_PI / 180.0;
    latR = lat * M_PI / 180.0;

    // 计算地心经纬度
    double phiR;
    phiR = atan(pow(eb/ea, 2)) * tan(latR);

    double val, re;
    val = (pow(ea, 2) - pow(eb, 2))/pow(ea, 2);
    re = eb / sqrt(1- val*pow(cos(phiR), 2));

    double lonR_diff = lonR - sub_lonR;
    double r1, r2, r3, rn;
    r1 = h - re*cos(phiR)*cos(lonR_diff);
    r2 = -1 * cos(phiR) *sin(lonR_diff);
    r3 = re*sin(phiR);
    rn = sqrt(pow(r1, 2) + pow(r2, 2) + pow(r3, 2));

    double x, y;
    x = atan(-1*r2/r1);
    y = asin(-1*r3/rn);

    ScaleFunc(x, y, col, row);
}

void NormGeostationaryProjection::ImageToGeo(float col, float row, float &lon, float &lat)
{
    double x, y;
    ScaleFuncInv(col, row, x, y);

    double val1, val2;
    val1 = h*cos(x)*cos(y);
    val2 = pow(cos(y), 2) + pow(ea/eb*sin(y), 2);

    double sd_val, sn_val;
    double s1, s2, s3, sxy;
    sd_val = sqrt(pow(val1, 2) - val2*(pow(h, 2) - pow(ea, 2)));
    sn_val = (val1 - sd_val)/val2;

    s1 = h - sn_val * cos(x) * cos(y);
    s2 = sn_val * sin(x) * sin(y);
    s3 = -1 * sn_val * sin(y);
    sxy = sqrt(pow(s1, 2) + pow(s2, 2));

    double lonR, latR;
    lonR = atan(s2/ s1);
    latR = atan(pow(ea, 2)/pow(eb, 2)*s3/sxy);

    lon = lonR/M_PI*180.0 + sub_lon;
    lat = latR/M_PI*180.0;
}

// int main()
// {
//     NormGeostationaryProjection gs1(140.7, 11000.5, 81865099, 11000.5, 81865099);
//     float lonD, latD, col, row;
//     lonD = 140.7;
//     latD = 0.0;
//
//     gs1.GeoToImage(lonD, latD, col, row);
//     cout<<"row: "<<row<<"; "<<"col: "<<col<<endl;
//
//     float lon1, lat1;
//
//     gs1.ImageToGeo(col, row, lon1, lat1);
//     cout<<"lon: "<<lon1<<"; "<<"lat: "<<lat1<<endl;
//
//     return 0;
// }
