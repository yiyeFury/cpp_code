//
// Created by admin on 2021/6/23.
//

#ifndef CPP_CODE_LINEAR_REGRESSION_H
#define CPP_CODE_LINEAR_REGRESSION_H


template<typename T1, typename T2, typename T3, int M, int N>
class LinearRegression
{
    /*
     * T1 x: design matrix
     * T2 y:
     * T3 theta
     * M : the number of training samples
     * N : the number of features + 1
     */
public:
    double Hypothesis(const T1 (&x)[M], const T2 (&theta)[M]);

    double CostFunction(const T1 (&x)[M][N], const T2 (&theta)[N],
                        const T3 (&y)[M]);

    void GradientDescent(const T1 (&design_matrix)[M][N], const T3 (&y)[M],
                         const T2 (&src_theta)[N], T2 (&dst_theta)[N],
                         float alpha);
};

#endif //CPP_CODE_LINEAR_REGRESSION_H
