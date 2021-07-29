//
// Created by admin on 2021/7/16.
//

#ifndef CPP_CODE_SUCCESSIVE_CORRECTION_H
#define CPP_CODE_SUCCESSIVE_CORRECTION_H

// successive correction method (SCM)


float degree_to_radiance(float deg);
float GreatCircleDistance(float lon1, float lat1, float lon2, float lat2, float radius);
float WeightFunction(float R, float r);
void SuccessiveCorrection(float *bkg_data, int bkg_rows, int bkg_cols,
                          float *obs_data, int obs_rows, int obs_cols,
                          float *dst_data, int dst_rows, int dst_cols,
                          float *lats, int lats_size,
                          float *lons, int lons_size,
                          float search_radius,
                          float influence_radius,
                          float fill_value);

#endif //CPP_CODE_SUCCESSIVE_CORRECTION_H
