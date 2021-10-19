//
// Created by xie on 2021/10/16.
//

#ifndef CPP_CODE_GEOMETRY_H
#define CPP_CODE_GEOMETRY_H

#include <vector>
#include <cmath>
using namespace std;

template<class T>
struct Point
{
    T x;  // x 坐标
    T y;  // y 坐标
    Point(T xx ,T yy): x(xx), y(yy){}
};

template<typename T>
float PolygonArea(vector<Point<T>> vec_point)
{
    int num_point = vec_point.size();
    float area = T(0);  // 多边形面积
    for(int ii=0;ii<num_point-1;ii++) {
        area += vec_point[ii].x * vec_point[ii+1].y - vec_point[ii+1].x*vec_point[ii].y;
    }
    area += vec_point[num_point-1].x * vec_point[0].y - vec_point[0].x * vec_point[num_point-1].y;
    
    area = 0.5*abs(area);
    return area;
}



#endif //CPP_CODE_GEOMETRY_H
