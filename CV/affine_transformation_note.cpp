//
// Created by xie on 2021/11/7.
//
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "affine_transformation_note.h"


using namespace cv;
using namespace std;
// *****************************************************************************
// int main()
// {
//     cout <<"\nStart\n\n";
//
//     string file_path = "E:/my_data/opencv_sample_data/apple.jpg";
//     Mat src = imread(file_path);
//     if (src.empty()) {
//         throw runtime_error("failed to read "+file_path);
//         return -1;
//     }
//
//     Point2f src_tri[3];
//     src_tri[0] = Point2f(0.0, 0.f);
//     src_tri[1] = Point2f(src.cols-1.f, 0.f);
//     src_tri[2] = Point2f(0.f, src.rows - 1.f);
//
//     Point2f dst_tri[3];
//     dst_tri[0] = Point2f( 0.f, src.rows*0.33f );
//     dst_tri[1] = Point2f( src.cols*0.85f, src.rows*0.25f );
//     dst_tri[2] = Point2f( src.cols*0.15f, src.rows*0.7f );
//
//     Mat warp_mat = getAffineTransform(src_tri, dst_tri);
//     Mat warp_dst = Mat::zeros(src.rows, src.cols, src.type());
//     warpAffine(src, warp_dst, warp_mat, warp_dst.size());
//
//     Point center = Point(warp_dst.cols/2, warp_dst.rows/2);
//     double angle = -50.0;
//     double scale = 0.6;
//
//     Mat rot_mat = getRotationMatrix2D(center, angle, scale);
//     Mat warp_rotate_dst;
//     warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());
//
//     imshow("Source image", src);
//     imshow("Warp", warp_dst);
//     imshow("Warp + Rotate", warp_rotate_dst);
//
//     waitKey();
//
//
//     cout<<"\n\nEnd\n";
//     // system("pause");
//     return 0;
// }