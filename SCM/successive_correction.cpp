//
// Created by admin on 2021/7/23.
//
#define PY_SSIZE_T_CLEAN
// #include <Python.h>
#include <cmath>
#include <vector>
#include <omp.h>
#include <iostream>

#include "successive_correction.h"
#include "../common.h"

using namespace std;

#define MPI 3.141592653589793

float degree_to_radiance(float deg)
{
    // 将 角度 计算为 弧度
    float rad = MPI*deg/180.0;
    return rad;
}


float GreatCircleDistance(float lon1, float lat1, float lon2, float lat2, float radius)
{
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


float WeightFunction(float R, float r)
{
    /*
     * 经验权重函数
     */
    float w;
    double R2 = pow(R, 2);
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
    
    float R=6378.137;  // km, wgs84 地球半径
    
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
    #pragma omp parallel for num_threads(num_thread)
    for (r=0;r<bkg_rows;r++)
    {
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


int main()
{

    const int kROW=4, kCOLUMN=5;

    float *bkg_data;
    float *obs_data;
    float *dst_data;

    float lats[kROW] = {10.0, 9.0, 8.0, 7.0};
    float lons[kCOLUMN] = {21.0, 22.0, 23.0, 24.0, 25.0};
    float search_radius = 200.0;
    float influence_radius = 500.0;

    float val = 1.0;
    
    for (int ii = 0; ii < kROW; ii++) {
        for (int jj = 0; jj < kCOLUMN; jj++) {
            *(bkg_data + ii * kCOLUMN + jj) = val;
            *(obs_data + ii * kCOLUMN + jj) = val + 1.0;
            *(dst_data + ii * kCOLUMN + jj) = 100.0;
            
        }
    }


    SuccessiveCorrection(bkg_data, kROW, kCOLUMN,
            obs_data, kROW, kCOLUMN,
            dst_data, kROW, kCOLUMN,
            lats, kROW,
            lons, kCOLUMN,
            search_radius,
            influence_radius,
            99.9,
            4);


    cout<<"\nbackground data\n";
    PrintArray(bkg_data, kROW, kCOLUMN);

    cout<<"\n\nobservation data\n";
    PrintArray(obs_data, kROW, kCOLUMN);

    cout<<"\n\nresult\n";
    PrintArray(dst_data, kROW, kCOLUMN);

    return 0;
}


