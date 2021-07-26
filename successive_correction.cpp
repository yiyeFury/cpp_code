//
// Created by admin on 2021/7/23.
//

#include "successive_correction.h"

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
