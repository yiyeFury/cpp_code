//
// Created by xie on 2021/12/2.
//

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <omp.h>

#include "IDW.h"

using namespace std;


float degree_to_radianceIDW(float deg)
{
    // 将 角度 计算为 弧度
    float rad = MPI*deg/180.0;
    return rad;
}


float GreatCircleDistanceIDW(float lon1, float lat1, float lon2, float lat2, float radius)
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

    lon1_rad = degree_to_radianceIDW(lon1), lat1_rad = degree_to_radianceIDW(lat1);
    lon2_rad = degree_to_radianceIDW(lon2), lat2_rad = degree_to_radianceIDW(lat2);

    delta_lon_rad = lon2_rad - lon1_rad;

    val = sin(lat1_rad)*sin(lat2_rad) + cos(lat1_rad)*cos(lat2_rad)*cos(delta_lon_rad);
    if (val > 1.0) val=1.0;
    if (val < -1.0) val=-1.0;
    central_angle = acos(val);
    d = radius*central_angle;
    return d;
}


float WeightFunctionIDW(float rr, float r)
{
    /*
     * 经验权重函数
     */
    double w;
    double R2 = pow(rr, 2);
    double r2 = pow(r, 2);

    w = max(0.0, (R2-r2)/(R2+r2));
    // w = (R2-r2)/(R2+r2);
    return w;
}


void InverseDistanceWeight(float *obs_data, int obs_size,
                           float *obs_lats, float *obs_lons,
                           float *dst_data, int dst_rows, int dst_cols,
                           float *dst_lats, float *dst_lons,
                           float search_radius,
                           float power_value,
                           int num_thread)
{
    float degress_radius = 2 * search_radius / 100.0;

    float lon_left_bound, lon_right_bound, lat_top_bound, lat_bottom_bound;
    int ii, jj;
    int cnt;  // 统计 当前范围内有效点个数

    double dist;  // 计算距离
    double weight, weight_sum;  // 记录权重
    double weight_val, weight_val_sum;  // 记录权重与观测值得乘积

    int r, c;
#pragma omp parallel for num_threads(num_thread) private(r, lon_left_bound, lon_right_bound, lat_top_bound, lat_bottom_bound, ii, jj, cnt, dist, weight, weight_sum, weight_val, weight_val_sum)
    for (c=0;c<dst_cols;c++)
    {
        for (r=0;r<dst_rows;r++)
        {
            vector<int> lat_idx, lon_idx;

            // 粗匹配
            // 纬度方向判断
            lat_top_bound = dst_lats[r] + degress_radius;
            lat_bottom_bound = dst_lats[r] - degress_radius;
            // 纬度查找
            for (ii=0;ii<obs_size;ii++) {  // 暂不考虑极区 纬度范围 80~-80
                if ((obs_lats[ii] >= lat_bottom_bound) && (obs_lats[ii] <= lat_top_bound)) {
                    lat_idx.push_back(ii);
                }
            }

            if (lat_idx.size()==0) {  // 粗匹配未找到点
                continue;
            }

            // 经度方向判断
            lon_left_bound = dst_lons[c] - degress_radius;
            if (lon_left_bound < 0) {  // 经度边界出现小于0
                lon_left_bound += 360;
            }

            lon_right_bound = dst_lons[c] + degress_radius;
            if (lon_right_bound > 360) {
                lon_right_bound -= 360;
            }

            // 经度查找
            if (lon_right_bound < lon_left_bound) {
                for (ii=0;ii<lat_idx.size();ii++) {
                    if ((obs_lons[ii] >= lon_left_bound) || (obs_lons[ii] <= lon_right_bound)) {
                        lon_idx.push_back(ii);
                    }
                }
            } else {
                for (ii=0;ii<lat_idx.size();ii++) {
                    if ((obs_lons[lat_idx[ii]] >= lon_left_bound) && (obs_lons[lat_idx[ii]] <= lon_right_bound)) {
                        lon_idx.push_back(lat_idx[ii]);
                    }
                }
            }

            if (lon_idx.size()==0) {  // 粗匹配未找到点
                continue;
            }

            // 根据粗匹配结果，计算大圆距离，精确距离匹配
            cnt = 0;  // 记录单前点 匹配到的有效点数量
            weight_sum = 0.0, weight_val_sum = 0.0;
            for (auto &tmp_ii: lon_idx) {
                // 当前位置，观测场 为无效值
                if (isnan(obs_data[tmp_ii])) continue;
                // double GreatCircleDistance(T lon1, T lat1, T lon2, T lat2, T radius)
                // cout<<r<<"   "<<c<<"   "<<tmp_jj<<"   "<<tmp_ii<<endl;
                // cout<<lons[c]<<"   "<<lats[r]<<"   "<<lons[tmp_jj]<<"   "<<lats[tmp_ii]<<endl;
                dist  = GreatCircleDistanceIDW(dst_lons[c], dst_lats[r], obs_lons[tmp_ii], obs_lats[tmp_ii], R);
                // cout<<"dist: "<<dist<<endl;
                // 位于搜索半径之外
                // cout<<"dist is: "<<dist<<", lon: "<<lons[c]<<", lat: "<<lats[r]<<", match lon: "<<lons[tmp_jj]<<", match lat: "<<lats[tmp_ii]<<endl;
                if (dist > search_radius) continue;

                cnt++;
                // (dist == 0)

                if (dist < 0.5) {
                    dist = 0.1;
                }

                weight = 1.0/pow(dist, power_value);
                // weight = WeightFunctionIDW(search_radius, dist);

                weight_val = weight*obs_data[tmp_ii];

                weight_val_sum += weight_val;
                weight_sum += weight;

            }

            if (cnt > 0) {
                // cout<<"no. of match: "<<cnt<<", row: "<<r<<", column: "<<c<<endl;
                // if (weight_sum > 0.0001)
                *(dst_data+r*dst_cols+c) = weight_val_sum/weight_sum;
            }

        }
    }
}

// int main()
// {
//     cout << "\nStart\n\n";
//
//     // void InverseDistanceWeight(float *obs_data, int obs_size,
//     //                            float *obs_lons,
//     //                            float *obs_lats,
//     //                            float *dst_data, int dst_rows, int dst_cols,
//     //                            float *dst_lats,
//     //                            float *dst_lons,
//     //                            float search_radius,
//     //                            float power_value,
//     //                            int num_thread)
//
//     int ii, jj;
//
//     const int obs_size = 10;
//     const int dst_rows = 15;
//     const int dst_cols = 20;
//
//     float obs_data[obs_size];
//     float obs_lons[obs_size];
//     float obs_lats[obs_size];
//
//     for(ii = 0;ii < obs_size; ii++) {
//         obs_data[ii] = ii*1.0;
//         obs_lons[ii] = ii*1.0;
//         obs_lats[ii] = ii*1.0;
//     }
//
//     float dst_data[dst_rows*dst_cols];
//     float dst_lats[dst_rows];
//     float dst_lons[dst_cols];
//
//     for(ii=0;ii<dst_rows;ii++) {
//         dst_lats[ii] = ii*1.0/1.5;
//     }
//
//     for(ii=0;ii<dst_cols;ii++) {
//         dst_lons[ii] = ii*1.0/2.0;
//     }
//
//     for(ii=0;ii<dst_rows;ii++) {
//         for(jj=0;jj<dst_cols;jj++)
//             dst_data[ii*dst_cols+jj] = 0.0;
//     }
//
//     InverseDistanceWeight(obs_data, obs_size,
//             obs_lons,
//             obs_lats,
//             dst_data, dst_rows, dst_cols,
//             dst_lats,
//             dst_lons,
//             200.0,
//             2,
//             1);
//
//     for(ii=0;ii<dst_rows;ii++) {
//         for(jj=0;jj<dst_cols;jj++)
//             cout<<"   "<<dst_data[ii*dst_cols+jj];
//         cout<<endl;
//     }
//
//
//     cout << "\n\nEnd\n";
//     return 0;
// }
