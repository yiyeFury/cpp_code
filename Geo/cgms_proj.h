//
// Created by xie on 2021/12/30.
//

// Coordination Group for Meteorological Satellites

#ifndef CPP_CODE_CGMS_PROJ_H
#define CPP_CODE_CGMS_PROJ_H

class NormGeosProj
{
    // Normalized Geostationary Projection
public:
    NormGeosProj(float lon, float coff, long int cfac, float loff, long int lfac);
    void ImageToGeo(float col, float row, float &lon, float &lat);
    void GeoToImage(float lon, float lat, float &col, float &row);

private:
    void ScaleFunc(double x, double y, float &col, float &row);
    void ScaleFuncInv(float col, float row, double &x, double &y);

public:
    float sub_lon;
    float r_eq = 6378.1370;  // equator radius, km
    float r_pol = 6356.7523;  // polar radius, km
    int h = 42164;  // The distance between spacecraft and centre of earth, km

    float COFF;  // column offset
    long int CFAC;  // column scaling factor
    float LOFF;  // line offset
    long int LFAC;  // line scaling factor
private:
};

#endif //CPP_CODE_CGMS_PROJ_H
