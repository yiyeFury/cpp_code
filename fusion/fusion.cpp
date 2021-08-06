//
// Created by admin on 2021/8/5.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <Dense>
#include <LU>

#include "fusion.h"

using namespace std;
using namespace Eigen;


float degree_to_radiance(float deg)
{
    // 将 角度 计算为 弧度
    float rad = MPI*deg/180.0;
    return rad;
}


float GreatCircleDistance(float lon1, float lat1, float lon2, float lat2, float radius)
{
    /*
     * 根据经纬度，计算两个点位之间的大圆距离
     * lon1, lat1, lon2, lat2: degree
     * radius: km
     */
    float lon1_rad, lon2_rad;
    float lat1_rad, lat2_rad;
    float delta_lon_rad, central_angle, d;
    float val;
    
    lon1_rad = degree_to_radiance(lon1), lat1_rad = degree_to_radiance(lat1);
    lon2_rad = degree_to_radiance(lon2), lat2_rad = degree_to_radiance(lat2);
    
    delta_lon_rad = lon2_rad - lon1_rad;
    
    val = sin(lat1_rad)*sin(lat2_rad) + cos(lat1_rad)*cos(lat2_rad)*cos(delta_lon_rad);
    if (val > 1.0) val=1.0;
    if (val < -1.0) val=-1.0;
    central_angle = acos(val);
    d = radius*central_angle;
    return d;
}


void SpaceMatchDegreeWindow(float *lats, int rows,
                            float *lons, int cols,
                            const float pt_lat, const float pt_lon,
                            const float degree_radius,
                            vector<int> &lat_idx, vector<int> &lon_idx)
{
    /*
     * 采用 经纬度 比较，粗略提取 格点窗口
     */
    
    float lon_left_bound, lon_right_bound;
    float lat_top_bound, lat_bottom_bound;
    int ii;
    
    lon_left_bound = pt_lon - degree_radius;
    if (lon_left_bound < 0) {  // 经度边界出现小于0
        lon_left_bound += 360;
    }
    
    lon_right_bound = pt_lon + degree_radius;
    if (lon_right_bound > 360) {
        lon_right_bound -= 360;
    }
    
    // 经度查找
    if (lon_right_bound < lon_left_bound) {
        
        for (ii=0;ii<cols;ii++) {
            if ((lons[ii] >= lon_left_bound) || (lons[ii] <= lon_right_bound)) {
                lon_idx.push_back(ii);
            }
        }
    } else {
        for (ii=0;ii<cols;ii++) {
            if ((lons[ii] >= lon_left_bound) && (lons[ii] <= lon_right_bound)) {
                lon_idx.push_back(ii);
            }
        }
    }
    
    lat_top_bound = pt_lat + degree_radius;
    lat_bottom_bound = pt_lat - degree_radius;
    // 纬度查找
    for (ii=0;ii<rows;ii++) {  // 暂不考虑极区 纬度范围 80~-80
        if ((lats[ii] >= lat_bottom_bound) && (lats[ii] <= lat_top_bound)) {
            lat_idx.push_back(ii);
        }
    }
}


float CorrelationErrorOI(float lon1, float lat1, float lon2, float lat2,
                         float lon_scale, float lat_scale)
{
    /*
     * 最优插值: 计算背景误差协相关
     */
    
    double lon_dist, lat_dist;
    float val;
    lon_dist = GreatCircleDistance(lon1, lat1, lon2, lat1, R);
    lat_dist = GreatCircleDistance(lon1, lat1, lon1, lat2, R);
    val = exp(-(pow(lon_dist, 2)/pow(lon_scale, 2))-(pow(lat_dist, 2)/pow(lat_scale, 2)));
    return val;
}


void CorrelationErrorMatrixBkgOI(const float *lats, int rows,
                                 const float *lons, int cols,
                                 const vector<int> lat_idx, const vector<int> lon_idx,
                                 Matrix<float, Dynamic, Dynamic> &corr_mat,
                                 const float lat_scale, const float lon_scale)
{
    /*
     * 计算背景误差协相关矩阵
     */
    int ii, jj;
    int num = lat_idx.size();
    
    // 计算上三角矩阵
    for(ii=0;ii<num;ii++) {
        for(jj=ii;jj<num;jj++) {
            corr_mat(ii, jj) = CorrelationErrorOI(lons[lon_idx[ii]], lats[lat_idx[ii]],
                                                  lons[lon_idx[jj]], lats[lat_idx[jj]],
                                                  lon_scale, lat_scale);
        }
    }
    
    // 此矩阵为对称阵，由上三角得到下三角
    for (ii=0;ii<num;ii++) {
        for (jj=ii+1;jj<num;jj++) {
            corr_mat(jj, ii) = corr_mat(ii, jj);
        }
    }
}


void CorrelationErrorVectorBkgOI(const float *lats, int rows,
                                 const float *lons, int cols,
                                 const vector<int> lat_idx, const vector<int> lon_idx,
                                 const float pt_lat, const float pt_lon,
                                 Matrix<float, Dynamic, 1> &corr_vec,
                                 const float lat_scale, const float lon_scale)
{
    /*
     * 计算背景误差协相关矩阵
     */
    int ii;
    int num = lat_idx.size();
    for (ii = 0; ii < num; ii++) {
        corr_vec(ii) = CorrelationErrorOI(pt_lon, pt_lat,
                                          lons[lon_idx[ii]], lats[lat_idx[ii]],
                                          lon_scale, lat_scale);
    }
}

void CorrelationErrorMatrixObsOI(const vector<int> lat_idx, const vector<int> lon_idx,
                                 Matrix<float, Dynamic, Dynamic> &corr_mat_obs)
{
    int num_pts = lat_idx.size();
    // corr_mat_obs.setZero(num_pts, num_pts);
    int ii, jj;
    for (ii=0;ii<num_pts;ii++) {
        for (jj=0;jj<num_pts;jj++) {
            corr_mat_obs(ii, jj) = 0.0;
        }
    }
    
    for (ii=0;ii<num_pts;ii++)
        corr_mat_obs(ii, ii) = 1.0;
    
}


void OptimumInterpolation(const float *bkg_data, int bkg_rows, int bkg_cols,
                          const float *obs_data, int obs_rows, int obs_cols,
                          float *dst_data, int dst_rows, int dst_cols,
                          float *error_variance, int err_rows, int err_cols,
                          float *lats, int lats_size,
                          float *lons, int lons_size,
                          float fill_value,
                          float search_radius,
                          float lat_scale, float lon_scale,
                          float lam, float sig)
{
    /*
     * todo: 设置默认值测试
     * float lat_scale=150.0
     * float lon_scale=300.0
     * float lam=1.0
     * float sig=1.0
     */
    int rows=bkg_rows, cols=bkg_cols;
    
    float degree_radius = 1.5*search_radius/100.0;
    
    int ii, jj;
    int cnt;  // 统计 当前范围内有效点个数
    
    float dist;  // 计算距离
    int num_pts;
    float tmp_val;
    
    // 循环遍历
    for (int r=0;r<rows;r++) {
        for (int c=0;c<cols;c++) {
            vector<int> tmp_lon_idx, tmp_lat_idx;  // 采用经纬度进行粗匹配，记录窗口内点的经纬度下标
            vector<int> lat_idx, lon_idx;  // 记录匹配到的点的经纬度下标
            if (isnan(*(bkg_data + r * cols + c))) {  // 背景场为无效值，跳过
                continue;
            }
            
            // 经纬度 窗口粗匹配
            SpaceMatchDegreeWindow(lats, rows,
                                   lons, cols,
                                   lats[r], lons[c],
                                   degree_radius,
                                   tmp_lat_idx, tmp_lon_idx);
            
            if ((tmp_lon_idx.size() == 0) || (tmp_lat_idx.size() == 0)) {  // 粗匹配未找到点
                continue;
            }
            
            // 根据粗匹配结果，计算大圆距离，精确距离匹配
            for (auto &tmp_ii: tmp_lat_idx) {
                for (auto &tmp_jj: tmp_lon_idx) {
                    // 观测场、背景场 均为有效值
                    if (isnan(*(obs_data + tmp_ii * cols + tmp_jj)) || isnan(*(bkg_data + tmp_ii * cols + tmp_jj)))
                        continue;
                    
                    dist = GreatCircleDistance(lons[c], lats[r], lons[tmp_jj], lats[tmp_ii], R);
                    // 点 位于 距离之内
                    if (dist <= search_radius) {
                        lat_idx.push_back(tmp_ii);
                        lon_idx.push_back(tmp_jj);
                    }
                }
            }
            
            num_pts = lon_idx.size();
            if (num_pts == 0) continue;
            
            // 计算最优插值 ------------------------------------------------------
            // 初估场误差协方差--有效格点
            Matrix<float, Dynamic, Dynamic> corr_mat_bkg(num_pts, num_pts);
            CorrelationErrorMatrixBkgOI(lats, rows,
                                        lons, cols,
                                        lat_idx, lon_idx, corr_mat_bkg,
                                        lat_scale, lon_scale);
            
            // 初估场误差协方差--分析格点与有效格点
            Matrix<float, Dynamic, 1> corr_vec(num_pts);
            CorrelationErrorVectorBkgOI(lats, rows,
                                        lons, cols,
                                        lat_idx, lon_idx,
                                        lats[r], lons[c],
                                        corr_vec,
                                        lat_scale, lon_scale);
            
            // 观测场误差协相关
            Matrix<float, Dynamic, Dynamic> corr_mat_obs(num_pts, num_pts);
            CorrelationErrorMatrixObsOI(lat_idx, lon_idx,
                                        corr_mat_obs);
            
            // 求解权重
            Matrix<float, Dynamic, 1> weight(num_pts);
    
            Matrix<float, Dynamic, Dynamic> tmp_mat(num_pts, num_pts);
            tmp_mat = corr_mat_bkg+corr_mat_obs;
            
            weight = tmp_mat.lu().solve(corr_vec);
            
            // 计算分析误差最小方差
            tmp_val = 0.0;
            for (ii=0;ii<num_pts;ii++) {
                tmp_val += weight(ii)*corr_vec(ii);
            }
            *(error_variance + r * cols + c) = pow(sig, 2) * (1 - tmp_val);
            
            // 插值计算
            tmp_val = 0.0;
            for (ii = 0; ii < num_pts; ii++) {
                tmp_val += weight(ii) * (*(obs_data + lat_idx[ii] * cols + lon_idx[ii]) -
                                         *(bkg_data + lat_idx[ii] * cols + lon_idx[ii]));
            }
            
            *(dst_data + r * cols + c) = *(bkg_data + r * cols + c) + tmp_val;
        }
    }
    
}


// *********************************************************************************************************************
// int main()
// {
//     cout << "\nStart\n\n";
//
//     const int M = 3, N = 4;
//     float bkg_data[M*N], obs_data[M*N], dst_data[M*N], error_variance[M*N];
//     float lats[M], lons[N];
//
//     float search_radius=200;
//     float lat_scale=150;
//     float lon_scale=300;
//     float lam=1.0, sig=1.0;
//     float fill_value = NAN;
//
//     int ii, jj, cnt=0;
//     for (ii=0;ii<M;ii++) {
//         for (jj=0;jj<N;jj++) {
//             bkg_data[ii*N+jj] = 1.0;
//             obs_data[ii*N+jj] = (++cnt)*1.0;
//             dst_data[ii*N+jj] = 0.0;
//             error_variance[ii*N+jj] = 0.0;
//         }
//     }
//
//     for (ii=0;ii<M;ii++) {
//         lats[ii] = 60.0 - 0.25*ii;
//     }
//     for (ii=0;ii<N;ii++) {
//         lons[ii] = 120.0 + 0.25*ii;
//     }
//
//     PrintArray(bkg_data);
//     PrintArray(obs_data);
//
//     OptimumInterpolation(bkg_data, M, N,
//                          obs_data, M, N,
//                          dst_data, M, N,
//                          error_variance, M, N,
//                          lats, M,
//                          lons, N,
//                          fill_value,
//                          search_radius,
//                          lat_scale, lon_scale,
//                          lam, sig);
//     PrintArray(dst_data);
//
//     cout << "\n\nend\n" << endl;
//     // system("pause");
//     return 0;
// }

