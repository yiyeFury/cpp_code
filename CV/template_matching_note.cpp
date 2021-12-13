//
// Created by xie on 2021/11/9.
//



// Template Matching
// https://docs.opencv.org/4.x/de/da9/tutorial_template_matching.html

#include <iostream>

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "operations_with_images.h"
#include "template_matching_note.h"

using namespace std;
using namespace cv;

bool use_mask= false;
Mat img, templ, mask, result;
const char* image_window = "Source Image";
const char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;

void MatchingMethod(int, void*);

// int main()
// {
//     cout <<"\nStart\n\n";
//
//     string source_img = "E:/my_data/opencv_sample_data/basketball1.png";
//     img = imread(source_img, IMREAD_COLOR);
//     // imshow( image_window, img);
//
//     Mat rect_img(img, Rect(60, 80, 45, 60));
//
//     templ = rect_img.clone();
//
//     namedWindow( image_window, WINDOW_AUTOSIZE );
//     namedWindow( result_window, WINDOW_AUTOSIZE );
//
//     const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//
//     createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );
//
//     MatchingMethod( 0, 0 );
//     waitKey(0);
//
//     cout<<"\n\nEnd\n";
//     // system("pause");
//     return EXIT_SUCCESS;
// }



void MatchingMethod(int, void*)
{
    Mat img_display;
    img.copyTo(img_display);

    int result_cols = img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;

    result.create(result_rows, result_cols, CV_32FC1);

    bool method_accepts_mask = (TM_SQDIFF == match_method || match_method == TM_CCORR_NORMED);

    if (use_mask && method_accepts_mask) {
        matchTemplate(img, templ, result, match_method, mask);
    } else {
        matchTemplate(img, templ, result, match_method);
    }

    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

    double minVal, maxVal;
    Point minLoc, maxLoc, matchLoc;

    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

    if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
        matchLoc = minLoc;
    else
        matchLoc = maxLoc;

    rectangle(img_display, matchLoc,
              Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows),
              Scalar::all(0), 2, 8, 0);

    rectangle( result, matchLoc,
               Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ),
               Scalar::all(0), 2, 8, 0 );

    imshow( image_window, img_display );
    imshow( result_window, result );

    return;

}
