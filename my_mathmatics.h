//
// Created by xie on 2021/4/18.
//

#ifndef CPP_CODE_MY_MATHMATICS_H
#define CPP_CODE_MY_MATHMATICS_H

#endif //CPP_CODE_MY_MATHMATICS_H

#include <math.h>

template<typename T, int N>
double sample_mean(const T (&arr)[N])
{
    // 计算样本均值
    double m, tmp_val=0.0;
    for (int ii=0;ii<N;ii++)
        tmp_val += arr[ii];
    m = tmp_val / N;
    return m;
}

template<typename T, int N>
double sample_variance(const T (&arr)[N])
{
    // 计算样本方差
    double v, m, tmp_val=0.0;
    m = sample_mean(arr);
    for (int ii=0;ii<N;ii++)
        tmp_val += pow(arr[ii]-m, 2);
    v = tmp_val/(N-1);
    return v;
}
