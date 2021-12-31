//
// Created by xie on 2021/12/30.
//

#ifndef CPP_CODE_NORMALIZED_GEOSTATIONARY_PROJECTION_H
#define CPP_CODE_NORMALIZED_GEOSTATIONARY_PROJECTION_H

class NormGeostationaryProjection
{
public:
    NormGeostationaryProjection(float lon, float coff, long int cfac, float loff, long int lfac);
    void ImageToGeo(float col, float row, float &lon, float &lat);
    void GeoToImage(float lon, float lat, float &col, float &row);

private:
    void ScaleFunc(double x, double y, float &col, float &row);
    void ScaleFuncInv(float col, float row, double &x, double &y);

public:
    float sub_lon;
    float ea = 6378.1370;  // equator radius, km
    float eb = 6356.7523;  // polar radius, km
    int h = 42164;  // The distance between spacecraft and centre of earth, km

    float COFF;  // Column scaling factor
    long int CFAC;  // Line scaling factor
    float LOFF;  // Column offset
    long int LFAC;  // Line offset
private:
};

#endif //CPP_CODE_NORMALIZED_GEOSTATIONARY_PROJECTION_H
