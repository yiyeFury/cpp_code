//
// Created by xie on 2021/7/9.
//

#ifndef CPP_CODE_OPENCV_TUTORIAL_H
#define CPP_CODE_OPENCV_TUTORIAL_H

#include <vector>
#include <string>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

void ShowImage(string img_file, string win_title="win_title");
void ImageSegmentationWithDistanceTransformAndWatershedAlgorithm();

#endif //CPP_CODE_OPENCV_TUTORIAL_H
