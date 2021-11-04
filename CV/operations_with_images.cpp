//
// Created by xie on 2021/7/8.
//

#include <string>

#include "operations_with_images.h"

using namespace std;
using namespace cv;


void ShowImage(string img_file, string win_title)
{
    Mat img = imread(img_file);
    if (img.empty()) {
        throw runtime_error("Failed to read: "+img_file);
    }

    namedWindow(win_title, WINDOW_AUTOSIZE);
    imshow(win_title, img);
    waitKey(0);
    destroyWindow(win_title);

    // destroyAllWindows();
}


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


void ImagePyramid(string file_path)
{
    Mat src = imread(file_path);
    Mat dst;

    string origin_name = "Original";
    namedWindow(origin_name, WINDOW_AUTOSIZE);
    imshow(origin_name, src);

    string down_name = "Down";
    pyrDown(src, dst, Size(src.cols/2, src.rows/2));
    namedWindow(down_name, WINDOW_AUTOSIZE);
    imshow(down_name, dst);
    
    string up_name = "Up";
    pyrUp(src, dst, Size(src.cols*2, src.rows*2));
    namedWindow(up_name, WINDOW_AUTOSIZE);
    imshow(up_name, dst);
    
    waitKey(0);
    // destroyWindow(down_name);
    destroyAllWindows();

}

/*
 * Image Segmentation with Distance Transform and Watershed Algorithm
 * https://docs.opencv.org/master/d2/dbd/tutorial_distance_transform.html
 */
void ImageSegmentationWithDistanceTransformAndWatershedAlgorithm()
{
    string card_png = "E:/my_data/opencv_sample_data/cards.png";
    Mat src = imread(card_png);
    if (src.empty()) {
        cout<<"Could not open or find the image!\n";
        return;
    }

    imshow("Source Image", src);

    // Change the background from white to black
    Mat mask;
    inRange(src, Scalar(255, 255, 255), Scalar(255, 255, 255), mask);
    src.setTo(Scalar(0, 0, 0), mask);
    
    imshow("Black Background Image", src);
    
    // Create a kernel that we will use to sharpen our image
    Mat kernel = (Mat_<float>(3, 3)<<
            1, 1, 1,
            1, -8, 1,
            1, 1, 1);
    
    // do the laplacian filtering as it is
    // well, we need to convert everything in something more deeper then CV_8U
    // because the kernel has some negative values,
    // and we can expect in general to have a Laplacian image with negative values
    // BUT a 8bits unsigned int (the one we are working with) can contain values from 0 to 255
    // so the possible negative number will be truncated
    Mat imgLaplacian;
    filter2D(src, imgLaplacian, CV_32F, kernel);
    
    Mat sharp;
    src.convertTo(sharp, CV_32F);
    Mat imgResult = sharp - imgLaplacian;
    
    // convert back to 8bits gray scale
    imgResult.convertTo(imgResult, CV_8UC3);
    imgLaplacian.convertTo(imgLaplacian, CV_8UC3);
    
    imshow( "Laplace Filtered Image", imgLaplacian );
    imshow( "New Sharped Image", imgResult );
    
    // Create binary image from source image
    Mat bw;
    cvtColor(imgResult, bw, COLOR_BGR2GRAY);
    threshold(bw, bw, 40, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("Binary Image", bw);
    
    // Perform the distance transform algorithm
    cout<<"Perform the distance transform algorithm\n";
    Mat dist;
    distanceTransform(bw, dist, DIST_L2, 3);
    
    // Normalize the distance image for range = {0.0, 1.0}
    normalize(dist, dist, 0, 1.0, NORM_MINMAX);
    imshow("Distance Transform Image", dist);
    
    // Threshold to obtain the peaks
    // This will be the markers for the foreground objects
    threshold(dist, dist, 0.4, 1.0, THRESH_BINARY);
    
    // Dilate a bit the dist image
    Mat kernel1 = Mat::ones(3, 3, CV_8U);
    dilate(dist, dist, kernel1);
    imshow("Peaks", dist);
    
    // Create the CV_8U version of the distance image
    // It is needed for findContours()
    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);
    
    // Find total markers
    vector<vector<Point>> contours;
    findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    // Create the marker image for the watershed algorithm
    Mat markers = Mat::zeros(dist.size(), CV_32S);
    
    // Draw the foreground markers
    for (size_t ii=0; ii< contours.size(); ii++) {
        drawContours(markers, contours, static_cast<int>(ii), Scalar(static_cast<int>(ii)+1), -1);
    }
    
    // Draw the background marker
    circle(markers, Point(5, 5), 3, Scalar(255), -1);
    Mat markers8u;
    markers.convertTo(markers8u, CV_8U, 10);
    imshow("Markers", markers8u);
    
    // Perform the watershed algorithm
    cout<<"Perform the watershed algorithm\n";
    watershed(imgResult, markers);
    
    Mat mark;
    markers.convertTo(mark, CV_8U);
    bitwise_not(mark, mark);
    imshow("Markers_v2", mark);
    
    // Generate random colors
    vector<Vec3b> colors;
    for (size_t ii=0;ii<contours.size(); ii++) {
        int b = theRNG().uniform(0, 256);
        int g = theRNG().uniform(0, 256);
        int r = theRNG().uniform(0, 256);
        
        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }
    
    // Create the result image
    Mat dst = Mat::zeros(markers.size(), CV_8UC3);
    
    // Fill labeled objects with random colors
    for (int ii=0; ii<markers.rows;ii++) {
        for (int jj=0;jj<markers.cols;jj++) {
            int index = markers.at<int>(ii, jj);
            if (index > 0 && index <= static_cast<int>(contours.size())) {
                dst.at<Vec3b>(ii, jj)=colors[index-1];
            }
        }
    }
    
    // Visualize the final image
    imshow("Final Result", dst);
    
    waitKey(0);
}
