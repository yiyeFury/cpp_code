//
// Created by admin on 2021/6/8.
//

#include <cmath>
#include "basic_math.h"
#include "coordinate_conversion.h"

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
