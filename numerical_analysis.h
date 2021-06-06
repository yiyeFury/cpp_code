//
// Created by xie on 2021/6/3.
//

#ifndef CPP_CODE_NUMERICAL_ANALYSIS_H
#define CPP_CODE_NUMERICAL_ANALYSIS_H

#endif //CPP_CODE_NUMERICAL_ANALYSIS_H

template<typename T1, typename T2, typename T3, int M>
double LagrangeInterp(const T1 (&src_x)[M], const T2(&src_y)[M], const T3 dst_x)
{
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
 *
 */
template<typename T1, typename T2, typename T3, int M>
void NewtonDividedDiff(const T1 (&src_x)[M], const T2 (&src_y)[M], T3 (&f)[M])
{
    // Newton’s divided differences
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