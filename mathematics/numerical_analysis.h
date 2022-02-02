//
// Created by xie on 2021/6/3.
//

#ifndef CPP_CODE_NUMERICAL_ANALYSIS_H
#define CPP_CODE_NUMERICAL_ANALYSIS_H

#include <stdexcept>
#include <string>

/*
 * *****************************************************************************
 * ---------------------   解线性方程组的直接方法   --------------------------------
 * *****************************************************************************
 */

// SYSTEM_OF_LINEAR_EQUATIONS

/*
 * -----------------------   高斯消去法   ----------------------------------------
 */
template<typename T1, typename T2, typename T3, int num>
void GaussElimination(const T1 (&src_a)[num][num], const T2 (&src_b)[num], T3 (&dst)[num])
{

    int ii, jj, kk, ll;
    auto zero_val = T3(0);
    T3 tmp;

    // 复制数据
    T1 arr[num][num];
    for (ii=0;ii<num;ii++) {
        dst[ii] = src_b[ii];
        for (jj=0;jj<num;jj++) {
            arr[ii][jj] = src_a[ii][jj];
        }
    }

    // 消元过程
    for (kk=0;kk<num - 1;kk++) {
        // 主元为 0，异常处理
        if (arr[kk][kk] == 0)
            throw runtime_error("zero pivot encountered at " + to_string(kk));

        for (ii=kk+1;ii<num;ii++) {
            arr[ii][kk] = arr[ii][kk] / arr[kk][kk];
            dst[ii] = dst[ii] - arr[ii][kk] * dst[kk];
            for (jj=kk+1;jj<num;jj++) {
                arr[ii][jj] = arr[ii][jj] - arr[ii][kk] * arr[kk][jj];
            }
        }
    }

    // 回代过程
    if (arr[kk][kk] == 0)
        throw runtime_error("zero pivot encountered at " + to_string(kk));

    dst[kk] = dst[kk] / arr[kk][kk];

    for (kk=num-2;kk>=0;kk--) {
        tmp = zero_val;
        for (ll=kk+1;ll<num;ll++) {
            tmp += arr[kk][ll] * dst[ll];
        }
        dst[kk] = (dst[kk] - tmp) / arr[kk][kk];
    }

}

/*
 * --------------------   列主元素法   -------------------------------------------
 */

/*
 * -----------------   Doolittle分解，即LU分解   ---------------------------------
 */
template<typename T1, typename T2, int num>
void FactorizationLU(T1 (&arr)[num][num], T2 (&arrL)[num][num], T2 (&arrU)[num][num])
{

    int ii, jj, kk, rr;
    T2 tmp1, tmp2;
    auto zero_val = T2(0);
    auto one_val = T2(1);
    // U 的下三角 位置 填充 0
    for (ii=0;ii<num;ii++) {
        for (jj=0;jj<ii;jj++) {
            arrU[ii][jj] = zero_val;
        }
    }

    // L 的上三角位置 填充 0
    for (ii=0;ii<num;ii++) {
        arrL[ii][ii] = one_val;
        for(jj=ii+1;jj<num;jj++) {
            arrL[ii][jj] = zero_val;
        }
    }

    // 计算U的第一行，L的第一列
    for (ii=0;ii<num;ii++) arrU[0][ii] = arr[0][ii];
    for (ii=1;ii<num;ii++) arrL[ii][0] = arr[ii][0] / arrU[0][0];

    // 计算 U的 第r行，L的第r列（r=1, ..., num-1）
    for (rr = 1; rr < num; rr++) {
        // 计算 U 矩阵
        for (jj = rr; jj < num; jj++) {
            tmp1 = zero_val;
            for (kk = 0; kk < rr; kk++) {
                tmp1 += arrL[rr][kk] * arrU[kk][jj];
            }
            arrU[rr][jj] = arr[rr][jj] - tmp1;
        }

        // 计算 L 矩阵
        for (ii = rr+1; ii < num; ii++) {
            tmp2 = zero_val;
            for (int kk = 0; kk < rr; kk++) {
                tmp2 += arrL[ii][kk] * arrU[kk][rr];
            }
            arrL[ii][rr] = (arr[ii][rr] - tmp2) / arrU[rr][rr];

        }
    }
}


/*
 * *****************************************************************************
 * ------------------------   插值法   ------------------------------------------
 * *****************************************************************************
 */

/*
 * ---------------------------   拉格朗日插值   ----------------------------------
 */
template<typename T1, typename T2, typename T3, int M>
double LagrangeInterp(const T1 (&src_x)[M], const T2(&src_y)[M], const T3 dst_x)
{
    /*
     * 拉格朗日插值
     * dst_x: 待插值位置
     */
    const int N= M-1;
    double dst_y=0.0;
    for (int ii=0;ii<=N;ii++) {
        double tmp = 1.0;
        for (int jj=0;jj<=N;jj++) {
            if (jj!= ii) {
                tmp *= (dst_x - double(src_x[jj]))/(double(src_x[ii]) - src_x[jj]);
            }
        }
        dst_y += tmp*src_y[ii];
    }
    return dst_y;
}


/*
 * ------------------------   牛顿插值   ----------------------------------------
 */
template<typename T1, typename T2, typename T3, int M>
void NewtonDividedDiff(const T1 (&src_x)[M], const T2 (&src_y)[M], T3 (&f)[M])
{
    /*
     * Newton’s divided differences
     * 计算 1阶 至 M-1阶牛顿差商
     */
    int N=M-1;
    for (int ii=0;ii<=N;ii++)
        f[ii] = src_y[ii];

    for (int ii=1;ii<=N;ii++) {
        for (int kk=N;kk>=ii;kk--) {
            f[kk] = double(f[kk-1] - f[kk])/double(src_x[kk-ii] - src_x[kk]);
        }
    }
}


template<typename T1, typename T2, typename T3, int M>
double NewtonInterp(const T1 (&src_x)[M], const T2 (&src_y)[M], const T3 dst_x)
{
    int N = M - 1;
    T2 f[M];

    NewtonDividedDiff(src_x, src_y, f);

    double dst_y=0.0, tmp;
    for (int kk=0;kk<=N;kk++) {
        tmp = 1.0;
        for (int jj=0;jj<=kk-1;jj++) {
            tmp*=(dst_x - src_x[jj]);
        }
        dst_y += f[kk]*tmp;  // kk=0时，相当于 +f0
    }
    return dst_y;
}

#endif //CPP_CODE_NUMERICAL_ANALYSIS_H