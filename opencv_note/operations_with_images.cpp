//
// Created by xie on 2021/7/8.
//



#include "operations_with_images.h"
using namespace cv;

/*
 * 图像显示
 * https://docs.opencv.org/master/d5/d98/tutorial_mat_operations.html
 */
void ShowImage(string img_file, string win_title)
{
    Mat img = imread(img_file);

    namedWindow(win_title, WINDOW_AUTOSIZE);
    imshow(win_title, img);
    waitKey(0);
    destroyWindow(win_title);
    // destroyAllWindows();
}


/*
 * Smoothing Images
 * https://docs.opencv.org/master/dc/dd3/tutorial_gausian_median_blur_bilateral_filter.html
 */
void SmoothImage(Mat src)
{
    Mat dst = Mat::zeros( src.size(), src.type() );
    
    // blur
    string blur_win_name = "Blur";
    blur(src, dst, Size(5, 5), Point(-1,-1));
    // namedWindow(blur_win_name, WINDOW_AUTOSIZE);
    imshow(blur_win_name, dst);
    
    // gaussian blur
    string gaussian_win_name = "Gaussian";
    GaussianBlur( src, dst, Size(5, 5), 0, 0 );
    // namedWindow(gaussian_win_name, WINDOW_AUTOSIZE);
    imshow(gaussian_win_name, dst);
    
    // median blur
    string median_img_name = "Median";
    medianBlur(src, dst, 5);
    imshow(median_img_name, dst);
    
    waitKey(0);
    destroyWindow(blur_win_name);
    destroyWindow(gaussian_win_name);
    destroyWindow(median_img_name);
    // destroyAllWindows();
}


/*
 * Image Pyramids
 * https://docs.opencv.org/master/d4/d1f/tutorial_pyramids.html
 */
void ImagePyramid(Mat src)
{
    Mat dst;
    
    string down_name = "Down";
    pyrDown(src, dst, Size(src.cols/2, src.rows/2));
    namedWindow(down_name, WINDOW_AUTOSIZE);
    imshow(down_name, dst);
    
    string up_name = "Up";
    pyrUp(src, dst, Size(src.cols*2, src.rows*2));
    namedWindow(up_name, WINDOW_AUTOSIZE);
    imshow(up_name, dst);
    
    waitKey(0);
    destroyWindow(down_name);
    

}

/*
 * Image Segmentation with Distance Transform and Watershed Algorithm
 * https://docs.opencv.org/master/d2/dbd/tutorial_distance_transform.html
 */
void ImageSegmentationWithDistanceTransformAndWatershedAlgorithm()
{
    string card_png = "";
    Mat src = imread(card_png);
}
