//
// Created by xie on 2021/4/18.
//

#ifndef CPP_CODE_MY_MATHMATICS_H
#define CPP_CODE_MY_MATHMATICS_H

#endif //CPP_CODE_MY_MATHMATICS_H

#include<iostream>
#include <cmath>

using namespace std;

int Factorial(int n);

template<int M>
void FibonacciSequence(int (&fib)[M])
{
    for(int ii=0;ii<M;ii++) {
        if (ii == 0)
            fib[ii] = 0;
        else if (ii==1)
            fib[ii] = 1;
        else
            fib[ii] = fib[ii-1] + fib[ii-2];
    }
}

template<typename T1>
double degree_to_radiance(T1 deg)
{
    // 将 角度 计算为 弧度
    double rad = M_PI*deg/180.0;
    return rad;
}

template<typename T1>
double radiance_to_degree(T1 rad)
{
    // 由弧度 计算 角度
    double deg = rad*180.0/M_PI;
    return deg;
}


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

template<typename T, int N>
double sample_covariance(const T (&arr1)[N], const T (&arr2)[N])
{
    double m1, m2;
    m1 = sample_mean(arr1);
    m2 = sample_mean(arr2);
    double tmp_val, dst;
    for (int ii=0;ii<N;ii++) {
        tmp_val += (arr1[ii] - m1)*(arr2[ii] - m2);
    }

    dst = tmp_val / (N-1);
    return dst;
}

template<typename T, int M, int N>
void CovarianceMatrix(const T (&sample_data)[M][N], double (&cov_mat)[N][N])
{
    double tmp_val;
    double tmp_mean[N];

    // 计算 每个特征下的 所有样本均值
    for(int cc=0;cc<N;cc++) {
        tmp_val = 0;
        for (int rr=0; rr<M;rr++)
            tmp_val += sample_data[rr][cc];
        tmp_mean[cc] = tmp_val/M;
    }

//    for(int ii=0;ii<N;ii++) {
//        cout<<tmp_mean[ii]<<"          ";
//    }
//    cout<<endl<<endl;

    // 计算协方差矩阵
    for (int rr = 0; rr < N; rr++) {
        for (int cc = 0; cc < N; cc++) {
            tmp_val = 0;
            // 计算协方差
            for (int ii = 0; ii < M; ii++)
                tmp_val += (sample_data[ii][rr] - tmp_mean[rr]) * (sample_data[ii][cc] - tmp_mean[cc]);
            cov_mat[rr][cc] = tmp_val / (M - 1);
        }
    }

}
