//
// Created by xie on 2021/7/9.
//


#include <iostream>

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "operations_with_images.h"

using namespace std;
using namespace cv;

int main()
{
    string img_file = "E:/my_data/opencv_sample_data/box_in_scene.png";
    ShowImage(img_file);

    Mat src;
    src = imread(img_file);
    ImagePyramid(src);
    
    cout<<endl;
    // system("pause");
    return 0;
}