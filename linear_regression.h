//
// Created by admin on 2021/6/23.
//

#ifndef CPP_CODE_LINEAR_REGRESSION_H
#define CPP_CODE_LINEAR_REGRESSION_H



/*
 * T1 x: design matrix
 * T2 y:
 * T3 theta
 * M : the number of training samples
 * N : the number of features + 1
 */


template<typename T1, typename T2, int M, int N>
double Hypothesis(const T1 (&x)[M], const T2 (&theta)[M])
{
    /*
     * x: expanded, x_0 = 1
     */
    double h = 0.0;
    for (int ii=0;ii<M;ii++) {
        h += theta[ii]*x[ii];
    }
    return h;
}

template<typename T1, typename T2, typename T3, int M, int N>
double CostFunction(const T1 (&x)[M][N], const T2 (&theta)[N], const T3 (&y)[M])
{
    double dst_val, tmp_val=0.0, h;
    for (int ii=0;ii <M;ii++) {
        h = Hypothesis(x[ii], theta);
        tmp_val += pow(h- y[ii], 2);
    }
    dst_val = tmp_val/2/M;
    return dst_val;
}


template<typename T1, typename T2, typename T3, int M, int N>
void GradientDescent(const T1 (&design_matrix)[M][N], const T3 (&y)[M],
                     const T2 (&src_theta)[N], T2 (&dst_theta)[N], float alpha)
{
    /*
     * alpha: learning rate
     */
    T2 tmp_theta[N];
    CopyArray(src_theta, tmp_theta);

    double h, tmp_val;
    double alpha_m = alpha/M;
    while (true) {
        for (int jj=0;jj<N;jj++) {
            tmp_val = 0.0;
            for (int ii=0;ii<M;ii++) {
                h = Hypothesis(design_matrix[ii], tmp_theta);
                tmp_val += (h-y[ii])*design_matrix[ii][jj];
            }
            dst_theta[jj] = tmp_theta[jj] - tmp_val*alpha_m;
        }
        // todo: 设立终止条件

        // 本次 迭代 未终止，准备下一次
        CopyArray(dst_theta, tmp_theta);
    }
}


#endif //CPP_CODE_LINEAR_REGRESSION_H
