//
// Created by xie on 2021/7/15.
//

#ifndef CPP_CODE_ML_COMMON_H
#define CPP_CODE_ML_COMMON_H

#include <cmath>
using namespace std;

class ML
{
    /*
     * machine learning base class
     */
public:
    ML();
    ~ML();

public:
    template<typename T1, typename T2, typename T3, int M, int N>
    double CostFunction(const T1 (&x)[M][N], const T2 (&theta)[N], const T3 (&y)[M]);
    
    template<typename T1, typename T2, typename T3, int M>
    void FeatureScaling(const T1 (&x)[M], double (&dst_x)[M],  T2 mu, T3 s);
    
    template<typename T1, typename T2>
    float SigmoidFunction(const T1 z);
};

ML::ML() {}

ML::~ML() {}

template<typename T1, typename T2, typename T3, int M, int N>
double ML::CostFunction(const T1 (&x)[M][N], const T2 (&theta)[N], const T3 (&y)[M])
{
    /*
     * 代价函数
     * M: no. of samples
     * N: 1 + no. of features
     */
    double dst_val, tmp_val=0.0, h;
    for (int ii=0;ii <M;ii++) {
        h = Hypothesis(x[ii], theta);
        tmp_val += pow(h- y[ii], 2);
    }
    dst_val = tmp_val/2/M;
    return dst_val;
}

template<typename T1, typename T2, typename T3, int M>
void ML::FeatureScaling(const T1 (&x)[M], double (&dst_x)[M],  T2 mu, T3 s)
{
    /*
     * M: no. of samples
     * mu: average value of training set of ith feature
     * s:  range (max-min) or standard deviation
     */
    dst_x[0] = x[0];
    int ii=0;
    for(ii++;ii<M) {
        dst_x[ii] = (x[ii] - mu)/s;
    }
}

template<typename T1, typename T2>
float ML::SigmoidFunction(const T1 z) {
    return 1.0/(1.0+exp(-z));
}

template<<typename T1, typename T2>
void ML::SigmoidFunction(const T1 (&z)[M], T2 (&g)[M]) {
    for (int ii=0;ii<M;ii++) {
        g[ii] = 1.0/(1.0+z[ii]);
    }
    
}

#endif //CPP_CODE_ML_COMMON_H
