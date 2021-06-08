//
// Created by admin on 2021/6/8.
//

#ifndef CPP_CODE_COORDINATE_CONVERSION_H
#define CPP_CODE_COORDINATE_CONVERSION_H

#endif //CPP_CODE_COORDINATE_CONVERSION_H

#include <cmath>

typedef struct {
    double x, y, z;
}Cartesian3D;

typedef struct {
    double radius, lon, lat;
}SphericalCoord;


class SphericalCoordinate
{
public:
    SphericalCoord CartesianToSpherical(const double &x, const double &y, const double &z);
    Cartesian3D SphericalToCartesian(const double &radius, const double &lon, const double &lat);
};
