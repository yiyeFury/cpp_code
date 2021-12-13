//
// Created by xie on 2021/12/2.
//

#ifndef CPP_CODE_IDW_H
#define CPP_CODE_IDW_H

#define MPI 3.141592653589793
#define R 6378.137  // km, wgs84 地球半径


float degree_to_radianceIDW(float deg);

float GreatCircleDistanceIDW(float lon1, float lat1, float lon2, float lat2, float radius);

float WeightFunctionIDW(float rr, float r);

void InverseDistanceWeight(float *obs_data, int obs_size,
                           float *obs_lats, float *obs_lons,
                           float *dst_data, int dst_rows, int dst_cols,
                           float *dst_lats, float *dst_lons,
                           float search_radius,
                           float power_value,
                           int num_thread);

#endif //CPP_CODE_IDW_H
