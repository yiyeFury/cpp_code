//
// Created by admin on 2021/7/16.
//

#ifndef CPP_CODE_SUCCESSIVE_CORRECTION_H
#define CPP_CODE_SUCCESSIVE_CORRECTION_H

// successive correction method (SCM)
#include <cmath>
#include <vector>

#include "geodesy.h"
#include "common.h"

using namespace std;


float WeightFunction(float R, float r);

template<int M, int N>
void SuccessiveCorrection(const float (&bkg_data)[M][N], const float (&obs_data)[M][N],
                          float (&dst_data)[M][N],
                          const float (&lats)[M], const float (&lons)[N],
                          const float search_radius, const float influence_radius, const float fill_value=NAN)
{
    /*
     * 进行 逐步订正计算
     * M: no. of rows
     * N: no. of columns
     * bkg_data: 背景场数据
     * obs_data: 观测场数据
     * dst_data: 逐步订正 插值结果
     * lats: 纬度数组 90 ~ -90
     * lons: 经度数组 0~360
     * search_radius: 搜索半径(比较大圆距离), km
     */
    
    // 搜索匹配
    // 粗匹配，根据经纬度 筛选, 特殊考虑：1)北极：2)经度 0 和 360 接边
    // 精确匹配，计算大圆距离
    
    float R=6378.137;  // km, wgs84 地球半径
    
    float degress_radius = 1.5*search_radius / 100.0;
    // 粗匹配时需要特殊考虑的位置
    float lat_up_limit = 90.0 - degress_radius;
    float lon_left_limit = 0.0 + degress_radius;
    float lon_right_limit = 360.0 - degress_radius;
    
    float lon_left_bound, lon_right_bound, lat_top_bound, lat_bottom_bound;
    int ii, jj;
    int cnt;  // 统计 当前范围内有效点个数
    
    float dist;  // 计算距离
    float weight, weight_sum;  // 记录权重
    float weight_val, weight_val_sum;  // 记录权重与观测值得乘积
    
    // PrintArray(lats);
    // 循环遍历
    for (int r=0;r<M;r++) {
        for (int c=0;c<N;c++) {
            
            // if (r!=0 || c!=N-1) continue;
            
            vector<int> lat_idx, lon_idx;
            
            if (isnan(bkg_data[r][c])) {  // 背景场为无效值，跳过
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
        
                for (ii=0;ii<N;ii++) {
                    if ((lons[ii] >= lon_left_bound) || (lons[ii] <= lon_right_bound)) {
                        lon_idx.push_back(ii);
                    }
                }
            } else {
                for (ii=0;ii<N;ii++) {
                    if ((lons[ii] >= lon_left_bound) && (lons[ii] <= lon_right_bound)) {
                        lon_idx.push_back(ii);
                    }
                }
            }
    
            lat_top_bound = lats[r] + degress_radius;
            lat_bottom_bound = lats[r] - degress_radius;
            // 纬度查找
            for (ii=0;ii<M;ii++) {  // 暂不考虑极区 纬度范围 80~-80
                if ((lats[ii] >= lat_bottom_bound) && (lats[ii] <= lat_top_bound)) {
                    lat_idx.push_back(ii);
                }
            }
    
            if ((lon_idx.size()==0) || (lat_idx.size()==0)) {  // 粗匹配未找到点
                continue;
            }
            
            // 根据粗匹配结果，计算大圆距离，精确距离匹配
            cnt = 0;  // 记录单前点 匹配到的有效点数量
            weight_sum = 0.0, weight_val_sum = 0.0;
            for (auto &tmp_ii: lat_idx) {
                for (auto &tmp_jj: lon_idx) {
                    // 当前位置，观测场 为无效值
                    if (isnan(obs_data[tmp_ii][tmp_jj])) continue;
                    // double GreatCircleDistance(T lon1, T lat1, T lon2, T lat2, T radius)
                    // cout<<r<<"   "<<c<<"   "<<tmp_jj<<"   "<<tmp_ii<<endl;
                    // cout<<lons[c]<<"   "<<lats[r]<<"   "<<lons[tmp_jj]<<"   "<<lats[tmp_ii]<<endl;
                    dist  = GreatCircleDistance(lons[c], lats[r], lons[tmp_jj], lats[tmp_ii], R);
                    // cout<<"dist: "<<dist<<endl;
                    // 位于搜索半径之外
                    if (dist > search_radius) continue;
                    
                    // WeightFunction(float R, float r)
                    weight = WeightFunction(influence_radius, dist);
                    weight_val = weight*(obs_data[tmp_ii][tmp_jj] - bkg_data[r][c]);
                    
                    weight_val_sum += weight_val;
                    weight_sum += weight;
                    cnt++;
                }
                
            }
            if (cnt > 0) dst_data[r][c] = bkg_data[r][c] + weight_val_sum/weight_sum;
            
            
        }
    }
    
}



#endif //CPP_CODE_SUCCESSIVE_CORRECTION_H
