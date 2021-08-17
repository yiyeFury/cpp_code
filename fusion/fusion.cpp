//
// Created by admin on 2021/8/5.
//

#define PY_SSIZE_T_CLEAN
// #include <Python.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <omp.h>
#include <Dense>
#include <LU>
#include "fusion.h"
#include "../common.h"

using namespace std;
using namespace Eigen;


/*
 * *********************************************************************************************************************
 * common function
 */
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


/*
 * *********************************************************************************************************************
 * successive correction
 */
float WeightFunction(float rr, float r)
{
/*
 * 经验权重函数
 */
float w;
double R2 = pow(rr, 2);
double r2 = pow(r, 2);

// w = max(0.0, (R2-r2)/(R2+r2));
w = (R2-r2)/(R2+r2);
return w;
}


void SuccessiveCorrection(float *bkg_data, int bkg_rows, int bkg_cols,
                          float *obs_data, int obs_rows, int obs_cols,
                          float *dst_data, int dst_rows, int dst_cols,
                          float *lats, int lats_size,
                          float *lons, int lons_size,
                          float search_radius,
                          float influence_radius,
                          float fill_value,
                          int num_thread)
{
    /*
     * 逐步订正计算: 单次订正计算
     * M: no. of rows
     * N: no. of columns
     * bkg_data: 背景场数据
     * obs_data: 观测场数据
     * dst_data: 逐步订正 插值结果
     * lats: 纬度数组 90 ~ -90
     * lons: 经度数组 0~360
     * search_radius: 搜索半径(比较大圆距离), km
     * num_thread: 并行计算线程 数
     */
    
    // 搜索匹配
    // 粗匹配，根据经纬度 筛选, 特殊考虑：1)北极：2)经度 0 和 360 接边
    // 精确匹配，计算大圆距离
    
    // float R=6378.137;  // km, wgs84 地球半径
    
    float degress_radius = 1.5*search_radius / 100.0;
    // 粗匹配时需要特殊考虑的位置
    // float lat_up_limit = 90.0 - degress_radius;
    // float lon_left_limit = 0.0 + degress_radius;
    // float lon_right_limit = 360.0 - degress_radius;
    
    float lon_left_bound, lon_right_bound, lat_top_bound, lat_bottom_bound;
    int ii, jj;
    int cnt;  // 统计 当前范围内有效点个数
    
    float dist;  // 计算距离
    float weight, weight_sum;  // 记录权重
    float weight_val, weight_val_sum;  // 记录权重与观测值得乘积
    
    // PrintArray(lats);
    // 循环遍历
    
    int r, c;
#pragma omp parallel for num_threads(num_thread) private(c, lon_left_bound, lon_right_bound, lat_top_bound, lat_bottom_bound, ii, jj, cnt, dist, weight, weight_sum, weight_val, weight_val_sum)
    for (r=0;r<bkg_rows;r++)
    {
        // int tmp_id = omp_get_thread_num();
        // cout<<"id: "<<tmp_id<<endl;
        
        for (c=0;c<bkg_cols;c++)
        {
            // if (r!=0 || c!=N-1) continue;
            
            vector<int> lat_idx, lon_idx;
            
            if (isnan(*(bkg_data+r*bkg_cols+c))) {  // 背景场为无效值，跳过
                // cout <<"background data is nan: "<<r<<" row, "<<c<<" column"<<endl;
                continue;
            }
            
            // 粗匹配
            lon_left_bound = lons[c] - degress_radius;
            if (lon_left_bound < 0) {  // 经度边界出现小于0
                lon_left_bound += 360;
            }
            
            lon_right_bound = lons[c] + degress_radius;
            if (lon_right_bound > 360) {
                lon_right_bound -= 360;
            }
            
            // 经度查找
            if (lon_right_bound < lon_left_bound) {
                
                for (ii=0;ii<bkg_cols;ii++) {
                    if ((lons[ii] >= lon_left_bound) || (lons[ii] <= lon_right_bound)) {
                        lon_idx.push_back(ii);
                    }
                }
            } else {
                for (ii=0;ii<bkg_cols;ii++) {
                    if ((lons[ii] >= lon_left_bound) && (lons[ii] <= lon_right_bound)) {
                        lon_idx.push_back(ii);
                    }
                }
            }
            
            lat_top_bound = lats[r] + degress_radius;
            lat_bottom_bound = lats[r] - degress_radius;
            // 纬度查找
            for (ii=0;ii<bkg_rows;ii++) {  // 暂不考虑极区 纬度范围 80~-80
                if ((lats[ii] >= lat_bottom_bound) && (lats[ii] <= lat_top_bound)) {
                    lat_idx.push_back(ii);
                }
            }
            
            if ((lon_idx.size()==0) || (lat_idx.size()==0)) {  // 粗匹配未找到点
                // cout <<"no coarse match found: "<<r<<" row, "<<c<<" column"<<endl;
                continue;
            }
            
            // 根据粗匹配结果，计算大圆距离，精确距离匹配
            cnt = 0;  // 记录单前点 匹配到的有效点数量
            weight_sum = 0.0, weight_val_sum = 0.0;
            for (auto &tmp_ii: lat_idx) {
                for (auto &tmp_jj: lon_idx) {
                    // 当前位置，观测场 为无效值
                    if (isnan(*(obs_data+tmp_ii*bkg_cols+tmp_jj))) continue;
                    if (isnan(*(bkg_data+tmp_ii*bkg_cols+tmp_jj))) continue;
                    // double GreatCircleDistance(T lon1, T lat1, T lon2, T lat2, T radius)
                    // cout<<r<<"   "<<c<<"   "<<tmp_jj<<"   "<<tmp_ii<<endl;
                    // cout<<lons[c]<<"   "<<lats[r]<<"   "<<lons[tmp_jj]<<"   "<<lats[tmp_ii]<<endl;
                    dist  = GreatCircleDistance(lons[c], lats[r], lons[tmp_jj], lats[tmp_ii], R);
                    // cout<<"dist: "<<dist<<endl;
                    // 位于搜索半径之外
                    // cout<<"dist is: "<<dist<<", lon: "<<lons[c]<<", lat: "<<lats[r]<<", match lon: "<<lons[tmp_jj]<<", match lat: "<<lats[tmp_ii]<<endl;
                    if (dist > search_radius) continue;
                    
                    // WeightFunction(float R, float r)
                    weight = WeightFunction(influence_radius, dist);
                    weight_val = weight*(*(obs_data+tmp_ii*bkg_cols+tmp_jj) - *(bkg_data+tmp_ii*bkg_cols+tmp_jj));
                    
                    weight_val_sum += weight_val;
                    weight_sum += weight;
                    cnt++;
                }
            }
            
            if (cnt > 0) {
                // cout<<"no. of match: "<<cnt<<", row: "<<r<<", column: "<<c<<endl;
                *(dst_data+r*bkg_cols+c) = *(bkg_data+r*bkg_cols+c) + weight_val_sum/weight_sum;
            }
            // else {
            //     cout <<"no match found: "<<r<<" row, "<<c<<" column"<<endl;
            // }
        }
    }
    
}


/*
 * *********************************************************************************************************************
 * optimum interpolation
 */
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


void OptimumInterpolation(float *bkg_data, int bkg_rows, int bkg_cols,
                          float *obs_data, int obs_rows, int obs_cols,
                          float *dst_data, int dst_rows, int dst_cols,
                          float *error_variance, int err_rows, int err_cols,
                          float *lats, int lats_size,
                          float *lons, int lons_size,
                          float search_radius,
                          float lat_scale, float lon_scale,
                          float lam, float sig,
                          float fill_value,
                          int num_thread)
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
    int r, c;
#pragma omp parallel for num_threads(num_thread) private(r, ii, jj, cnt, dist, num_pts, tmp_val)
    for (c = 0; c < cols; c++)
    {
        // int tmp_id = omp_get_thread_num();
        // cout<<"id: "<<tmp_id<<endl;
        for (r = 0; r < rows; r++)
        {
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


/*
 * *********************************************************************************************************************
 * test
 */

// int main()
// {
//
//     const int kROW=3, kCOLUMN=4;
//     int ii, jj;
//
//     float search_radius;
//
//     float lats[kROW];
//     float lons[kCOLUMN];
//
//     float bkg_data[kROW*kCOLUMN];
//     float obs_data[kROW*kCOLUMN];
//     float dst_data[kROW*kCOLUMN];
//     float error_variance[kROW*kCOLUMN];
//
//     for (ii=0;ii<kROW;ii++) {
//         lats[ii] = 60.0 - ii*0.25;
//     }
//
//     for (jj=0;jj<kCOLUMN;jj++) {
//         lons[jj] = 100.0 + jj*0.25;
//     }
//
//     for (ii = 0; ii < kROW; ii++) {
//         for (jj = 0; jj < kCOLUMN; jj++) {
//             bkg_data[ii * kCOLUMN + jj] = 1.0;
//             obs_data[ii * kCOLUMN + jj] = ii * 2 + jj;
//             dst_data[ii * kCOLUMN + jj] = 0.0;
//             error_variance[ii * kCOLUMN + jj] = 0.0;
//         }
//     }
//
//     cout<<"\nbackground data\n";
//     PrintArray(bkg_data, kROW, kCOLUMN);
//
//     cout<<"\n\nobservation data\n";
//     PrintArray(obs_data, kROW, kCOLUMN);
//
//     // test for OI
//     cout<<"\nOI\n\n";
//     search_radius=200.0;
//     float lat_scale=150.0;
//     float lon_scale=300.0;
//     float lam=1.0, sig=1.0;
//     OptimumInterpolation(bkg_data, kROW, kCOLUMN,
//                          obs_data, kROW, kCOLUMN,
//                          dst_data, kROW, kCOLUMN,
//                          error_variance, kROW, kCOLUMN,
//                          lats, kROW,
//                          lons, kCOLUMN,
//                          search_radius,
//                          lat_scale, lon_scale,
//                          lam, sig,
//                          99.9,
//                          4);
//
//     cout<<"\n\nOI result\n";
//     PrintArray(dst_data, kROW, kCOLUMN);
//
//     cout<<"\nOI error variance\n";
//     PrintArray(error_variance, kROW, kCOLUMN);
//
//     // test for SCM
//     search_radius = 200.0;
//     float influence_radius = 500.0;
//     SuccessiveCorrection(bkg_data, kROW, kCOLUMN,
//             obs_data, kROW, kCOLUMN,
//             dst_data, kROW, kCOLUMN,
//             lats, kROW,
//             lons, kCOLUMN,
//             search_radius,
//             influence_radius,
//             99.9,
//             4);
//
//     cout<<"\n\nSCM result\n";
//     PrintArray(dst_data, kROW, kCOLUMN);
//
//     return 0;
// }

