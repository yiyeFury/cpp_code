//
// Created by xie on 2021/7/8.
//

/*
 * 参考信息位于
 * https://docs.opencv.org/master/d5/d98/tutorial_mat_operations.html
 */

//#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void ShowImage(string img_file, string win_title="win_title")
{
    Mat img = imread(img_file);

    namedWindow(win_title, WINDOW_AUTOSIZE);
    imshow(win_title, img);
    waitKey(0);
    destroyAllWindows();
}



int main()
{
//    string img_file = "C:/Users/xie/Desktop/curry.jpg";
    string img_file = "C:/Users/admin/Desktop/curry.jpg";
    cout<<"show"<<endl;

    ShowImage(img_file);

    cout<<"show done"<<endl;
    cout<<endl;
	system("pause");
    return 0;
}