[TOC]
# OpenCV 学习笔记
![](./opencv-logo.png)
> 参考教程 opencv [tutorial](https://docs.opencv.org/master/d9/df8/tutorial_root.html) 

## [Introduction](https://docs.opencv.org/master/d1/dfb/intro.html)  
All the OpenCV classes and functions are placed into the `cv` namespace.
    ```
    using namespace cv;
    ```

### [Data types](https://docs.opencv.org/master/d1/d1b/group__core__hal__interface.html)  
|类型|说明|
|:-|:-|
|schar|signed 1 byte integer|
|uchar|unsigned 1 byte integer|
|short|signed 2 byte integer|
|ushort|unsigned 2 byte integer|
|int|signed 4 byte integer|
|uint|unsigned 4 byte integer|
|int64|signed 8 byte integer|
|uint64|unsigned 8 byte integer|

### Color

#### [Color conversions](https://docs.opencv.org/master/de/d25/imgproc_color_conversions.html)  

#### [ColorConversionCodes](https://docs.opencv.org/master/d8/d01/group__imgproc__color__conversions.html#ga4e0972be5de079fed4e3a10e24ef5ef0)  
1. convert between RGB/BGR and grayscale  
    - COLOR_BGR2GRAY  
    - COLOR_RGB2GRAY  
    - COLOR_GRAY2BGR  
    - COLOR_GRAY2RGB  

## [Basic structures](https://docs.opencv.org/master/dc/d84/group__core__basic.html#ga599fe92e910c027be274233eccad7beb)  
### [Mat - The Basic Image Container](https://docs.opencv.org/master/d6/d6d/tutorial_mat_the_basic_image_container.html)  
1. Mat is basically a class with two data parts: 
	- **the matrix header** (containing information such as the size of the matrix, the method used for storing, at which address is the matrix stored, and so on) and 
	- **a pointer to the matrix** containing the pixel values (taking any dimensionality depending on the method chosen for storing) . 
	- The matrix header size is constant, however the size of the matrix itself may vary from image to image and usually is larger by orders of magnitude.  

- cv::Mat::zeros  
- cv::Mat::ones  
- cv::Mat::eye

## [Getting Started with Images](https://docs.opencv.org/master/db/deb/tutorial_display_image.html)  

|模块|说明|
|:-|:-|
|#include <opencv2/core.hpp>|defined the basic building blocks of the library|
|#include <opencv2/imgcodecs.hpp>|provides functions for reading and writing|
|#include <opencv2/highgui.hpp>|contains the functions to show an image in a window|
```
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
```
### image
- [imread()](https://docs.opencv.org/master/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56)  
	
	> file formats  
	> [imread flags](https://docs.opencv.org/master/d8/d6a/group__imgcodecs__flags.html#ga61d9b0126a3e57d9277ac48327799c80)  
	
- [imshow()](https://docs.opencv.org/master/d7/dfc/group__highgui.html#ga453d42fe4cb60e5723281a89973ee563)  

- [imwrite()](https://docs.opencv.org/master/d4/da8/group__imgcodecs.html#gabbc7ef1aa2edfaa87772f1202d67e0ce)  

### window  
- [namedWindow()](https://docs.opencv.org/master/d7/dfc/group__highgui.html#ga5afdf8410934fd099df85c75b2e0888b)
- [waitKey()](https://docs.opencv.org/master/d7/dfc/group__highgui.html#ga5628525ad33f52eab17feebcfba38bd7)  
- [destroyWindow()](https://docs.opencv.org/master/d7/dfc/group__highgui.html#ga851ccdd6961022d1d5b4c4f255dbab34)
- [destroyAllWindows()](https://docs.opencv.org/master/d7/dfc/group__highgui.html#ga6b7fc1c1a8960438156912027b38f481)
