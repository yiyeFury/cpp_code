//
// Created by xie on 2021/6/3.
//

#ifndef CPP_CODE_NUMERICAL_ANALYSIS_H
#define CPP_CODE_NUMERICAL_ANALYSIS_H

#endif //CPP_CODE_NUMERICAL_ANALYSIS_H

template<typename T1, typename T2, typename T3, int M>
double LagrangeInterpolation(const T1 (&src_x)[M], const T2(&src_y)[M], const T3 dst_x)
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
