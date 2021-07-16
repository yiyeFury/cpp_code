//
// Created by admin on 2021/7/16.
//

#ifndef CPP_CODE_LOGISTIC_REGRESSION_H
#define CPP_CODE_LOGISTIC_REGRESSION_H
#include <cmath>

// #include "common.h"
#include "ML/linear_regression.h"

class LogisticRegression //: public LinearRegression
        {
public:
    LogisticRegression();
    ~LogisticRegression();
public:
    template<typename T1, typename T2, int N>
    double Hypothesis(const T1 (&x)[N], const T2 (&theta)[N]);
    
    template<typename T1, typename T2, typename T3, int M, int N>
    double CostFunction(const T1 (&design_matrix)[M][N],
                        const T2 (&theta)[N],
                        const T3 (&y)[M]);
    
    template<typename T1, typename T2, typename T3, typename T4, int M, int N>
    double CostFunctionR(const T1 (&x)[M][N], const T2 (&theta)[N], const T3 (&y)[M], T4 lam);
    
    
    
};

LogisticRegression::LogisticRegression() {}
LogisticRegression::~LogisticRegression() {}

template<typename T1, typename T2, int N>
double LogisticRegression::Hypothesis(const T1 (&x)[N], const T2 (&theta)[N]) {
    double h;  // 返回结果
    double tmp_val=0.0;
    int n=0;
    for (;n<N;n++) {
        tmp_val += x[n]*theta[n];
    }
    tmp_val *= -1;
    h = 1.0 / (1.0 + exp(tmp_val));
    return h;
}

template<typename T1, typename T2, typename T3, int M, int N>
double LogisticRegression::CostFunction(const T1 (&design_matrix)[M][N],
                                        const T2 (&theta)[N],
                                        const T3 (&y)[M]) {
    double dst_val; // 函数返回结果
    
    double tmp_val=0.0;
    double h;
    int m;
    for(m=0;m<M;m++) {
        h = Hypothesis(design_matrix[m], theta);
        tmp_val += y[m]*log(h) + (1-y[m])*log(1-h);
    }
    dst_val = -1.0/M*tmp_val;
    return dst_val;
}

template<typename T1, typename T2, typename T3, typename T4, int M, int N>
double LogisticRegression::CostFunctionR(const T1 (&x)[M][N],
                                         const T2 (&theta)[N],
                                         const T3 (&y)[M],
                                         T4 lam)
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



#endif //CPP_CODE_LOGISTIC_REGRESSION_H
