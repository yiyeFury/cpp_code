//
// Created by admin on 2021/6/8.
//

#include <cmath>
#include "basic_math.h"
#include "coordinate_conversion.h"


void ReferenceEllipsoid::CalculateParameters()
{
    f = (a - b)/a;
    fe = sqrt(a*a-b*b)/a;
    se = sqrt(a*a - b*b)/b;
}


void ReferenceEllipsoid::CalculateAuxiliaryParameters(double B)
{
    c = a*a/b;

    double B_rad = degree_to_radiance(B);
    W = sqrt(1-fe*fe*pow(sin(B_rad), 2));
    V = sqrt(1+pow(se*cos(B_rad), 2));
}

double ReferenceEllipsoid::CalculateCurvatureRadiusMeridian(double B)
{
    double B_rad, W, M;
    B_rad = degree_to_radiance(B);
    W = sqrt(1-fe*fe*pow(sin(B_rad), 2));
    M = a*(1-fe*fe)/pow(W, 3);
    return M;

}

double ReferenceEllipsoid::CalculateCurvatureRadiusPrimeVertical(double B)
{
    double B_rad, W, N;
    B_rad = degree_to_radiance(B);
    W = sqrt(1-fe*fe*pow(sin(B_rad), 2));
    N = a/W;
    return N;
}


SphericalCoord SphericalCoordinate::CartesianToSpherical(const double &x, const double &y, const double &z)
{
    SphericalCoord coord;
    double lon_rad, colat_rad, colat_deg;
    //  the distance (radius) from a point to the origin
    coord.radius = sqrt(x*x+y*y+z*z);

    lon_rad = atan2(y, x);
    coord.lon = radiance_to_degree(lon_rad);

    colat_rad = acos(z/radius);  // zenith angle or colatitude
    colat_deg = radiance_to_degree(colat_rad);
    coord.lat = 90.0 - colat_deg;
    return coord;
}

Cartesian3D SphericalCoordinate::SphericalToCartesian(const double &radius, const double &lon, const double &lat)
{
    double colat_rad, lon_rad;
    colat_rad = degree_to_radiance(90.0 - lat);
    lon_rad = degree_to_radiance(lon);

    Cartesian3D Cart;
    Cart.x = radius*cos(lon_rad)*sin(colat_rad);
    Cart.y = radius*sin(lon_rad)*sin(colat_rad);
    Cart.z = radius*cos(colat_rad);
    return Cart;
}
