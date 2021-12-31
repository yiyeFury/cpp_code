//
// Created by xie on 2021/6/1.
//

#ifndef CPP_CODE_SOLAR_POSITION_H
#define CPP_CODE_SOLAR_POSITION_H



/*
*/

template<typename T1, typename T2, typename T3>
void CrossProduct(const T1 (&a)[3], const T2 (&b)[3], T3 (&c)[3])
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = -a[0] * b[2] + a[2] * b[0];
    c[2] = a[0] * b[1] - a[1] * b[0];
}



#endif //CPP_CODE_SOLAR_POSITION_H