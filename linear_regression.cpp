//
// Created by admin on 2021/6/23.
//

# include <cmath>
#include "linear_regression.h"
#include "common.h"

T LinearRegression<T>::Hypothesis(const T (&x)[M], const T (&theta)[M])
{
    /*
     * x: expanded, x_0 = 1
     */
    T h = T(0);
    for (int ii=0;ii<M;ii++) {
        h += theta[ii]*x[ii];
    }
    return h;
}


T LinearRegression<T>::CostFunction(const T (&x)[M][N], const T (&theta)[N], const T (&y)[M])
{
    T dst_val, tmp_val=0, h;
    for (int ii=0;ii <M;ii++) {
        h = Hypothesis(x[ii], theta);
        tmp_val += pow(h- y[ii], 2)
    }
    dst_val = tmp_val/2/M;
    return dst_val;
}


LinearRegression<T>::GradientDescent(const T (&design_matrix)[M][N], const T (&y)[M],
                                     const T (&src_theta)[N], T (&dst_theta)[N],
                                     const T alpha)
{
    /*
     * M : the number of examples
     * N : the number of features + 1
     * alpha: learning rate
     */
    T tmp_theta[N];
    CopyArray(src_theta, tmp_theta);

    T h;
    for (int ii=0;ii<M;ii++) {


        dst_theta[ii];
    }


}