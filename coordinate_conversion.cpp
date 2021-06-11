//
// Created by admin on 2021/6/8.
//

#include <cmath>
#include "basic_math.h"
#include "coordinate_conversion.h"

ReferenceEllipsoid::ReferenceEllipsoid(double a, double b):a_(a),b_(b)
{
    f_ = (a - b)/a;
    fe_ = sqrt(a*a-b*b)/a;
    se_ = sqrt(a*a - b*b)/b;
    c_ = a*a/b;
}

double ReferenceEllipsoid::CalculateAuxiliaryParametersW(double lat)
{
    double lat_rad, W;
    lat_rad = degree_to_radiance(lat);
    W = sqrt(1-fe_*fe_*pow(sin(lat_rad), 2));
    return W;
}

double ReferenceEllipsoid::CalculateAuxiliaryParametersV(double lat)
{
    double lat_rad, V;
    lat_rad = degree_to_radiance(lat);
    V = sqrt(1+pow(se_*cos(lat_rad), 2));
    return V;
}

double ReferenceEllipsoid::CalculateCurvatureRadiusMeridian(double lat)
{
    double W, M;
    W = CalculateAuxiliaryParametersW(lat);
    M = a_*(1-fe_*fe_)/pow(W, 3);
    return M;
}

double ReferenceEllipsoid::CalculateCurvatureRadiusPrimeVertical(double lat)
{
    double W, N;
    W = CalculateAuxiliaryParametersW(lat);
    N = a_/W;
    return N;
}


Cartesian3D ReferenceEllipsoid::CalculateCartesian3dWithGeodeticCoordinate(GeodeticCoord geo_coord)
{
    double lon, lat, h, lon_rad, lat_rad;
    lon = geo_coord.lon, lat=geo_coord.lat, h=geo_coord.height;
    lon_rad = degree_to_radiance(lon);
    lat_rad = degree_to_radiance(lat);

    double N, tmp_val;
    N = CalculateCurvatureRadiusPrimeVertical(lat);
    tmp_val = (N+h)*cos(lat_rad);

    Cartesian3D cart3;
    cart3.x = tmp_val*cos(lon_rad);
    cart3.y = tmp_val*sin(lon_rad);
    cart3.z = (N*(1-pow(se_, 2)))*sin(lat_rad);

    return cart3;
}


double ReferenceEllipsoid::CalculateGeodeticLatitude(Cartesian3D cartesian3d, double precison_thr)
{
    double x, y, z;
    x = cartesian3d.x, y=cartesian3d.y, z=cartesian3d.z;

    double lat_prev, lat_post, lat_rad;

    double sum_xy_pow_sqrt;
    sum_xy_pow_sqrt = sqrt(pow(x, 2)+pow(y,2));

    double t0, t1, p, k;
    t0 = z/sum_xy_pow_sqrt;
    p =  c_*pow(fe_, 2)/sum_xy_pow_sqrt;
    k = 1 + pow(se_, 2);

    while (true) {
        t1 = t0 + p*t1/sqrt(k+pow(t1, 2));

        // 解算 大地纬度
        lat_prev = atan2(t0, 1.0);
        lat_post = atan2(t1, 1.0);
        if (abs(lat_post - lat_prev) < precison_thr)
            break;

        t0 = t1;
    }
    return lat_post;
}


GeodeticCoord ReferenceEllipsoid::CalculateGeodeticCoordinateWithCartesian3D(Cartesian3D cartesian3d, double lat_precison_thr)
{
    double x, y, z, N;
    x = cartesian3d.x, y=cartesian3d.y, z=cartesian3d.z;

    GeodeticCoord geo_coord;
    geo_coord.lon = radiance_to_degree(atan2(y, x));

    // 计算大地纬度
    geo_coord.lat = CalculateGeodeticLatitude(cartesian3d, lat_precison_thr);

    N = CalculateCurvatureRadiusPrimeVertical(geo_coord.lat);
    // 计算大地高度
    geo_coord.height = z/sin(geo_coord.lat) - N*(1-pow(fe_, 2));

    return geo_coord;
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
