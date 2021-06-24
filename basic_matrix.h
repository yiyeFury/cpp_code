//
// Created by xie on 2021/5/18.
//

#ifndef CPP_CODE_BASIC_MATRIX_H
#define CPP_CODE_BASIC_MATRIX_H


template <typename T, int M>
void ArrayAdd(const T(&aa)[M], const T(&bb)[M], T(&cc)[M])
{
    // 1d数组相加
    for (int ii = 0; ii < M; ii++)
        cc[ii] = aa[ii] + bb[ii];
}


template <typename T, int M, int N>
void ArrayAdd(const T(&aa)[M][N], const T(&bb)[M][N], T(&cc)[M][N])
{
    // 2d数组相加
    for (int ii = 0; ii < M; ii++)
        for (int jj = 0; jj < N; jj++)
            cc[ii][jj] = aa[ii][jj] + bb[ii][jj];
}


template<typename T, int M, int N, int K>
void MatrixMultiply(const T (&aa)[M][N], const T (&bb)[N][K], T (&cc)[M][K])
{
    T tmp_val = 0;
    for (int ii=0;ii<M;ii++) {
        for (int jj=0;jj<K;jj++) {
            tmp_val =0;
            for (int kk=0;kk<N;kk++) {
                tmp_val += aa[ii][kk]*bb[kk][jj];
            }
            cc[ii][jj] = tmp_val;
        }
    }
}


template<typename T, int M, int N>
void MatrixTranspose(const T (&aa)[M][N], T(&bb)[N][M])
{
    for (int ii=0;ii<M;ii++) {
        for (int jj=0;jj<N;jj++) {
            bb[jj][ii] = aa[ii][jj];
        }
    }
}

#endif //CPP_CODE_BASIC_MATRIX_H