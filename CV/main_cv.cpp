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
    cout <<"\nStart\n\n";
    
    string file_path = "E:/my_data/opencv_sample_data/opencv-logo.png";
    
    ShowImage(file_path, "Logo");

    cout<<"\n\nEnd\n";
    // system("pause");
    return 0;
}