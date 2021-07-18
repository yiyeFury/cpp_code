//
// Created by admin on 2021/6/23.
//

#ifndef CPP_CODE_LINEAR_REGRESSION_H
#define CPP_CODE_LINEAR_REGRESSION_H

#include <cmath>
#include "../common.h"

class LinearRegression
{
    /*
     * x: design matrix
     * y:
     * M : no. of training samples
     * N : 1 + no. of features
     */
public:
    LinearRegression();
    ~LinearRegression();

public:
    template<typename T1, typename T2, int N>
    double Hypothesis(const T1 (&x)[N], const T2 (&theta)[N]);
    
    template<typename T1, typename T2, typename T3, int M, int N>
    double CostFunction(const T1 (&x)[M][N], const T2 (&theta)[N], const T3 (&y)[M]);
    
    template<typename T1, typename T2, typename T3, typename T4, int M, int N>
    double CostFunctionR(const T1 (&x)[M][N], const T2 (&theta)[N], const T3 (&y)[M], T4 lam);
    
    template<typename T1, typename T2, typename T3, int M, int N>
    void GradientDescent(const T1 (&design_matrix)[M][N], const T2 (&y)[M],
                         const T3 (&src_theta)[N], T3 (&dst_theta)[N],
                         float alpha);
    
    template<typename T1, typename T2, typename T3, int M, int N>
    void GradientDescentR(const T1 (&design_matrix)[M][N], const T2 (&y)[M],
                          const T3 (&src_theta)[N], T3 (&dst_theta)[N],
                          float alpha, float lam);
};


LinearRegression::LinearRegression() {}

LinearRegression::~LinearRegression() {}

template<typename T1, typename T2, int N>
double LinearRegression::Hypothesis(const T1 (&x)[N], const T2 (&theta)[N])
{
    /*
     * x: expanded, x_0 = 1
     * N: 1 + no. of features
     */
    double h = 0.0;
    for (int ii=0;ii<N;ii++) {
        h += theta[ii]*x[ii];
    }
    return h;
}

template<typename T1, typename T2, typename T3, int M, int N>
double LinearRegression::CostFunction(const T1 (&x)[M][N], const T2 (&theta)[N], const T3 (&y)[M]) {
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

template<typename T1, typename T2, typename T3, typename T4, int M, int N>
double LinearRegression::CostFunctionR(const T1 (&x)[M][N], const T2 (&theta)[N], const T3 (&y)[M], T4 lam)
{
    /*
     * 正则化的代价函数
     * lam: regularization parameter
     */
    
    double item1 = CostFunction(x, theta, y);
    double val=0.0;
    for (int ii=1;ii<N;ii++) {
        val += pow(theta[ii], 2);
    }
    
    val = val *lam/2.0/M;
    val += item1;
    return val;
}

template<typename T1, typename T2, typename T3, int M, int N>
void LinearRegression::GradientDescent(const T1 (&design_matrix)[M][N], const T2 (&y)[M],
                                       const T3 (&src_theta)[N], T3 (&dst_theta)[N],
                                       float alpha) {
    T3 tmp_theta[N];
    CopyArray(src_theta, tmp_theta);
    
    int m;
    int n;
    float alpha_m = alpha/M;
    double h;  // hypothesis 计算结果
    double tmp_val;
    T3 theta_gap;
    while (true) {
        
        for(n=0;n<N;n++) {
            tmp_val = 0.0;
            for (m=0;m<M;m++) {
                h = Hypothesis(design_matrix[m], tmp_theta);
                tmp_val = (h-y[m])*design_matrix[m][n];
            }
            dst_theta[n] = tmp_theta[n] - alpha_m*tmp_val;
        }
        
        // todo: 完善终止条件
        theta_gap = 0.0;
        for(n=0;n<N;n++) {
            theta_gap += abs(dst_theta[n] - tmp_theta[n]);
        }
        if (theta_gap/N < 0.1) break;
        
        CopyArray(dst_theta, tmp_theta);
    }
}


template<typename T1, typename T2, typename T3, int M, int N>
void LinearRegression::GradientDescentR(const T1 (&design_matrix)[M][N], const T2 (&y)[M],
                      const T3 (&src_theta)[N], T3 (&dst_theta)[N],
                      float alpha, float lam) {
    /*
     * 参考 Andrew Ng ML课程 07 Regularization
     * alpha: learning rate
     * lam: regularization parameters
     */
    
    double alpha_m = alpha / M;
    double theta_gap;  // theta 迭代阈值，用于终止 theta迭代
    
    T3 theta_item[N];  // 辅助计算正则项
    double h, tmp_val;
    int ii;  // index of samples
    int jj;  // index of features
    
    T3 tmp_theta[N];  // 辅助更新 theta
    CopyArray(src_theta, tmp_theta);
    while (true) {
        // 计算 theta 正则项
        theta_item[0] = tmp_theta[0];
        for (jj=1;jj<N;jj++) {
            theta_item[jj] = tmp_theta[ii]*(1.0 - alpha_m*lam);
        }
        
        // calculate  theta
        for (jj = 0; jj < N; jj++) {
            tmp_val = 0.0;
            for (ii = 0; ii < M; ii++) {
                h = Hypothesis(design_matrix[ii], tmp_theta);
                tmp_val += (h - y[ii]) * design_matrix[ii][jj];
            }
            dst_theta[jj] = theta_item[jj] - tmp_val * alpha_m;
        }
        
        // todo: 完善终止条件
        theta_gap = 0.0;
        for (jj = 0; jj < N; jj++) {
            theta_gap += abs(dst_theta[jj] - tmp_theta[jj]);
        }
        if (theta_gap / N < 0.1) break;
        
        // 本次 迭代 未终止，准备下一次
        CopyArray(dst_theta, tmp_theta);
    }
}


#endif //CPP_CODE_LINEAR_REGRESSION_H
