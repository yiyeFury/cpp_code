//
// Created by xie on 2021/4/18.
//

#ifndef CPP_CODE_BASIC_MATH_H
#define CPP_CODE_BASIC_MATH_H



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
double CalculateMean(const T (&arr)[N], const int dof=N)
{
    /*
     * dof: degree of freedom
     */
    // 计算均值
    double m, tmp_val=0.0;
    for (int ii=0;ii<N;ii++)
        tmp_val += arr[ii];
    m = tmp_val / dof;
    return m;
}

template<typename T, int N>
double CalculateVariance(const T (&arr)[N], const int dof=N-1)
{
    // 计算样本方差
    double v, m, tmp_val=0.0;
    m = CalculateMean(arr, dof);
    for (int ii=0;ii<N;ii++)
        tmp_val += pow(arr[ii]-m, 2);
    v = tmp_val/dof;
    return v;
}

template<typename T, int N>
double CalculateCovariance(const T (&arr1)[N], const T (&arr2)[N], const int dof=N-1)
{
    double m1, m2;
    m1 = CalculateMean(arr1);
    m2 = CalculateMean(arr2);
    double tmp_val, dst;
    for (int ii=0;ii<N;ii++) {
        tmp_val += (arr1[ii] - m1)*(arr2[ii] - m2);
    }

    dst = tmp_val / dof;
    return dst;
}

template<typename T1, typename T2, typename T3, int N>
double CorrelationCoefficient(const T1 (&arr1)[N], const T2 (&arr2)[N], const T3 dof)
{
    /*
     * 计算相关系数
     */
    double cov;  // 计算协方差
    cov = CalculateCovariance(arr1, arr2, dof);

    double var1, var2;  // 计算方差
    var1 = CalculateVariance(arr1, dof);
    var2 = CalculateVariance(arr2, dof);

    double cor;
    cor = cov/sqrt(var1*var2);
    return cor;
}

template<typename T, int M, int N>
void CovarianceMatrix(const T (&sample_data)[M][N], double (&cov_mat)[N][N], const int dof=M-1)
{
    /*
     * 计算协方差矩阵
     * M, 样本数
     * N，特征数
     */
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
            cov_mat[rr][cc] = tmp_val / dof;
        }
    }

}

#endif //CPP_CODE_BASIC_MATH_H