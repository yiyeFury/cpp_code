//
// Created by xie on 2021/5/18.
//

#ifndef CPP_CODE_MATRIX_COMMON_H
#define CPP_CODE_MATRIX_COMMON_H


/*
 * *****************************************************************************
 * ---------------------   1d-array 相加   --------------------------------------
 * *****************************************************************************
 */
template <typename T1, typename T2, typename T3, int M>
void ArrayAdd(const T1(&aa)[M], const T2(&bb)[M], T3(&cc)[M])
{
    // 1d数组相加
    for (int ii = 0; ii < M; ii++)
        cc[ii] = aa[ii] + bb[ii];
}


/*
 * *****************************************************************************
 * ---------------------------   2d-array 相加   --------------------------------
 * *****************************************************************************
 */
template <typename T1, typename T2, typename T3, int M, int N>
void ArrayAdd(const T1(&aa)[M][N], const T2(&bb)[M][N], T3(&cc)[M][N])
{
    // 2d数组相加
    for (int ii = 0; ii < M; ii++)
        for (int jj = 0; jj < N; jj++)
            cc[ii][jj] = aa[ii][jj] + bb[ii][jj];
}


/* *****************************************************************************
 * -----------------------------   矩阵乘法   -----------------------------------
 ******************************************************************************/
template<typename T1, typename T2, typename T3, int M, int N, int K>
void MatrixMultiply(const T1 (&aa)[M][N], const T2 (&bb)[N][K], T3 (&cc)[M][K])
{
    T3 tmp_val;
    for (int ii=0;ii<M;ii++) {
        for (int jj=0;jj<K;jj++) {
            tmp_val =T3(0);
            for (int kk=0;kk<N;kk++) {
                tmp_val += aa[ii][kk]*bb[kk][jj];
            }
            cc[ii][jj] = tmp_val;
        }
    }
}


/* *****************************************************************************
 * ---------------------------   矩阵转置   -------------------------------------
 ******************************************************************************/
template<typename T, int M, int N>
void MatrixTranspose(const T (&aa)[M][N], T(&bb)[N][M])
{
    for (int ii=0;ii<M;ii++) {
        for (int jj=0;jj<N;jj++) {
            bb[jj][ii] = aa[ii][jj];
        }
    }
}

#endif //CPP_CODE_MATRIX_COMMON_H