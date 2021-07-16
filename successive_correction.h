//
// Created by admin on 2021/7/16.
//

#ifndef CPP_CODE_SUCCESSIVE_CORRECTION_H
#define CPP_CODE_SUCCESSIVE_CORRECTION_H

// successive correction method (SCM)
#include <cmath>

template<typename T, int M, int N, int D>
void SuccessiveCorrection(const T (&bkg_data)[M][N], const T (&obs_data)[M][N], T (&dst_data)[M][N]
                          T error_limit, iterate_range)
{

}

float WeightFunction(float R, float r)
{
    /*
     * 经验权重函数
     */
    float w;
    double R2 = pow(R, 2);
    double r2 = pow(r, 2);
    
    w = max(0.0, (R2-r2)/(R2+r2));
    return w;
}

#endif //CPP_CODE_SUCCESSIVE_CORRECTION_H
