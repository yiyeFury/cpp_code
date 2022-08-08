//
// Created by xie on 2022/7/3.
//

#ifndef CPP_CODE_GEO_COMMON_H
#define CPP_CODE_GEO_COMMON_H

float LonLimit180(float src_lon)
{
    float val=src_lon;
    while (val < - 180)
        val += 360;

    while (val > 180)
        val -= 360;
    return val;
}


float LonLimit360(float src_lon)
{
    // 将经度范围限制在 0 ~ 360

    float ff, tmp_val;

    tmp_val = src_lon/360.0;
    ff = tmp_val - int(tmp_val);

    return src_lon >= 0 ? 360*ff: 360*(1+ff);

}

#endif //CPP_CODE_GEO_COMMON_H
