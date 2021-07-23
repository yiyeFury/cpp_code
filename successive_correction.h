//
// Created by admin on 2021/7/16.
//

#ifndef CPP_CODE_SUCCESSIVE_CORRECTION_H
#define CPP_CODE_SUCCESSIVE_CORRECTION_H

// successive correction method (SCM)
#include <cmath>

float WeightFunction(float R, float r);

template<int M, int N, int D>
void SuccessiveCorrection(const float (&bkg_data)[M][N], const float (&obs_data)[M][N],
                          float (&dst_data)[M][N],
                          const float (&lats)[M], const float (&lons)[N],
                          const float search_radius, const float fill_value=NAN)
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
    
    float degress_radius = 1.5*search_radius / 100.0;
    // 粗匹配时需要特殊考虑的位置
    float lat_up_limit = 90.0 - degress_radius;
    float lon_left_limit = 0.0 + degress_radius;
    float lon_right_limit = 360.0 - degress_radius;
    
    float lon_left_bound, lon_right_bound, lat_top_bound, lat_bottom_bound;
    int ii;
    bool is_lon_cross;
    // 循环遍历
    for (int r=0;r<M;r++) {
        for (int c=0;c<N;c++) {
            vector<int> lat_idx, lon_idx;
            is_lon_cross = false;
            if (isnan(bkg_data[r][c])) {  // 背景场为无效值，跳过
                continue;
            }
            
            // 粗匹配
            lon_left_bound = lons[c] - degress_radius;
            if (lon_left_bound < 0) {  // 经度边界出现小于0
                lon_left_bound += 360;
                is_lon_cross = true
            }
    
            lon_right_bound = lons[c] + degress_radius;
            if (lon_right_bound > 360) {
                lon_right_bound -= 360;
                is_lon_cross= true;
            }
    
            // 经度查找
            if (is_lon_cross) {
        
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
            for (ii=0;ii<M;ii++) {
                if ((lats[ii] >= lat_bottom_bound) && (lats[ii] <= lat_up_bound)) {
                    lat_idx.push_back(ii);
                }
            }
    
            if ((lon_idx.size==0) || (lat_idx==0)) {
                continue;
            }
            
            // 根据粗匹配结果，计算大圆距离，精确距离匹配
            
            
            
        }
    }
    
}



#endif //CPP_CODE_SUCCESSIVE_CORRECTION_H
