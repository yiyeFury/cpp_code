//
// Created by xie on 2021/7/8.
//


#include <string>

#include "opencv_tutorial.h"

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

void TemplateMatching(string src_file)
{
    /*
     * src_file
     * templ
     */

    // string src_file = "E:/my_data/opencv_sample_data/box_in_scene.png";

    Mat img, templ, mask, result;

    string image_window = "Image";
    char* templ_window = "Template";
    char* result_window = "Result";

    img = imread(src_file, IMREAD_COLOR);
    // templ = imread(temp_file, IMREAD_COLOR);

    templ = img(Range(160, 280), Range(100, 180));

    namedWindow( image_window, WINDOW_AUTOSIZE );
    namedWindow(templ_window, WINDOW_KEEPRATIO);
    namedWindow( result_window, WINDOW_AUTOSIZE );

    imshow(templ_window, templ);

    Mat img_display;
    img.copyTo(img_display);

    int result_cols = img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;

    result.create( result_rows, result_cols, CV_32FC1 );

    int match_method = TM_SQDIFF;
    matchTemplate( img, templ, result, match_method, mask);

    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

    double minVal, maxVal;
    Point minLoc, maxLoc, matchLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    matchLoc = minLoc;

    rectangle(img_display, matchLoc,
              Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows),
              Scalar::all(0), 2, 8, 0);
    imshow(image_window, img_display);

    rectangle(result, matchLoc,
              Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows),
              Scalar::all(0), 2, 8, 0);
    imshow(result_window, result);

    waitKey(0);
    destroyAllWindows();
}

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


// int main()
// {
//
//     cout <<"\nStart\n\n";
//
//     Mat src, src_gray, dst;
//     string img_file("E:/my_data/dip_data/lena.jpg");
//     src = imread(img_file);
//     imshow("src", src);
//
//     // Reduce noise by blurring with a Gaussian filter ( kernel size = 3 )
//     GaussianBlur( src, src, Size(3, 3), 0, 0, BORDER_DEFAULT );
//     cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to grayscale
//
//     int kernel_size = 3, scale = 1, delta = 0, ddepth = CV_16S;
//     Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
//
//     // converting back to CV_8U
//     Mat abs_dst;
//     convertScaleAbs( dst, abs_dst );
//     imshow( "dst", abs_dst );
//     waitKey(0);
//
//     cout<<"\n\nEnd\n";
//     // system("pause");
//     return 0;
// }


