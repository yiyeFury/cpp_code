//
// Created by admin on 2021/6/8.
//

#ifndef CPP_CODE_COORDINATE_REFERENCE_H
#define CPP_CODE_COORDINATE_REFERENCE_H

#include <cmath>

typedef struct {
    double x, y, z;
}Cartesian3D;

using GeodeticCoord = struct {double lon, lat, height;};

typedef struct {
    double radius, lon, lat;
}SphericalCoord;

using EllipsoidWGS84 = struct
{
    double a = 6378137;  // unit: m
    double b = 6356752.3142;  // unit:m，约等于，可用长半轴和曲率半径求出
    double inv_f = 298.257223563;
};

using EllipsoidCGCS2000 = struct
{
    double a = 6378137;  // unit: m
    double b = 6356752.3141;  // unit:m，约等于，可用长半轴和曲率半径求出
    double inv_f = 298.257222101;
};


class ReferenceEllipsoid
{
public:
    double a_;  // semi-major axis
    double b_;  // semi-minor axis
    double inv_f_; // inverse flattening
    // double f_;  // flattening
    double fe_;  // first eccentricity
    double se_;  // second eccentricity
    double c_;  // 辅助参数
    double W_;
    double V_;

    ReferenceEllipsoid(double a, double inv_f);

    double CalculateAuxiliaryParametersW(double lat);
    double CalculateAuxiliaryParametersV(double lat);
    double CalculateCurvatureRadiusMeridian(double B);
    double CalculateCurvatureRadiusPrimeVertical(double B);

    GeodeticCoord CalculateGeodeticCoordinateWithCartesian3D(Cartesian3D cartesian3d, double lat_precison_thr=0.001);
    Cartesian3D CalculateCartesian3dWithGeodeticCoordinate(GeodeticCoord geo_coord);
    double CalculateGeodeticLatitude(Cartesian3D cartesian3d, double precison_thr=0.001);
};


class SphericalCoordinate
{
public:
    SphericalCoord CartesianToSpherical(const double &x, const double &y, const double &z);
    Cartesian3D SphericalToCartesian(const double &radius, const double &lon, const double &lat);
};

class WebMercator
{
public:
    double a_=6378137.0;  // ellipsoid semi-major axis, unit: m
    double lon0_=0.0;  // longitude of natural origin, unit: degree
    double fe_=0.0;  // false easting, unit: m
    double fn_=0.0;  // false northing, unit: m

public:
    WebMercator();
    Cartesian3D MapProjection(double lon, double lat);
    GeodeticCoord Inverse(double x, double y);

};


#endif //CPP_CODE_COORDINATE_REFERENCE_H