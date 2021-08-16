//
// Created by admin on 2021/8/5.
//

#ifndef CPP_CODE_FUSION_H
#define CPP_CODE_FUSION_H

#include <vector>
#include <cmath>
#include <Dense>


using namespace std;
using namespace Eigen;

#define MPI 3.141592653589793
#define R 6378.137  // km, wgs84 地球半径

float degree_to_radiance(float deg);
float GreatCircleDistance(float lon1, float lat1, float lon2, float lat2, float radius);

void SpaceMatchDegreeWindow(float *lats, int rows,
                            float *lons, int cols,
                            const float pt_lat, const float pt_lon,
                            const float degress_radius,
                            vector<int> &lat_idx, vector<int> &lon_idx);

float CorrelationErrorOI(float lon1, float lat1, float lon2, float lat2,
                         float lon_scale=150.0, float lat_scale=300.0);

void CorrelationErrorMatrixObsOI(const vector<int> lat_idx, const vector<int> lon_idx,
                                 Matrix<float, Dynamic, Dynamic> &corr_mat);


void CorrelationErrorMatrixBkgOI(const float *lats, int rows,
                                 const float *lons, int cols,
                                 const vector<int> lat_idx, const vector<int> lon_idx,
                                 Matrix<float, Dynamic, Dynamic> &corr_mat,
                                 const float lat_scale = 150.0, const float lon_scale = 300.0);


void CorrelationErrorVectorBkgOI(const float *lats, int rows,
                                 const float *lons, int cols,
                                 const vector<int> lat_idx, const vector<int> lon_idx,
                                 const float pt_lat, const float pt_lon,
                                 Matrix<float, Dynamic, 1> &corr_vec,
                                 const float lat_scale = 150.0, const float lon_scale = 300.0);


// void OptimumInterpolation(float *bkg_data, int bkg_rows, int bkg_cols,
//                           float *obs_data, int obs_rows, int obs_cols,
//                           float *dst_data, int dst_rows, int dst_cols,
//                           float *error_variance, int err_rows, int err_cols,
//                           float *lats, int lats_size,
//                           float *lons, int lons_size,
//                           float fill_value,
//                           float search_radius,
//                           float lat_scale=150.0, float lon_scale=300.0,
//                           float lam=1.0, float sig=1.0);

void OptimumInterpolation(const float *bkg_data, int bkg_rows, int bkg_cols,
                          const float *obs_data, int obs_rows, int obs_cols,
                          float *dst_data, int dst_rows, int dst_cols,
                          float *error_variance, int err_rows, int err_cols,
                          float *lats, int lats_size,
                          float *lons, int lons_size,
                          float fill_value,
                          float search_radius,
                          float lat_scale, float lon_scale,
                          float lam, float sig);



#endif //CPP_CODE_FUSION_H
