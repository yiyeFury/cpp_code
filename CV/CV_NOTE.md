[TOC]

# OpenCV  

> 参考教程 opencv [tutorial](https://docs.opencv.org/master/d9/df8/tutorial_root.html)   
> > [Getting Started with Images](https://docs.opencv.org/master/db/deb/tutorial_display_image.html)  
> > [Modules](https://docs.opencv.org/4.x/modules.html)  
> > - [Image Processing](https://docs.opencv.org/4.x/d7/dbd/group__imgproc.html)  


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

## [Basic structures](https://docs.opencv.org/master/dc/d84/group__core__basic.html)  

### [cv::Scalar_< _Tp > Class Template Reference](https://docs.opencv.org/4.x/d1/da0/classcv_1_1Scalar__.html)  


### [cv::Point_< _Tp > Class Template Reference](https://docs.opencv.org/4.x/db/d4e/classcv_1_1Point__.html)

### [cv::Mat Class Reference](https://docs.opencv.org/4.x/d3/d63/classcv_1_1Mat.html)  
#### Tutorial: [Mat - The Basic Image Container](https://docs.opencv.org/master/d6/d6d/tutorial_mat_the_basic_image_container.html)    
##### Mat  
- Mat is basically a class with two data parts: 
	- **the matrix header** (containing information such as the size of the matrix, the method used for storing, at which address is the matrix stored, and so on) and 
	- **a pointer to the matrix** containing the pixel values (taking any dimensionality depending on the method chosen for storing) . 
	- The matrix header size is constant, however the size of the matrix itself may vary from image to image and usually is larger by orders of magnitude.  

- OpenCV uses a **reference counting system**.  
	- each Mat object has its own header, however a matrix may be shared between two Mat objects by having their matrix pointers point to the same address.  
	- the copy operators will only copy the headers and the pointer to the large matrix, not the data itself.  
	- *The **assignment operator** and the **copy constructor** only copy the header.*
```C++  
Mat A, C;  // creates just the header parts
A = imread(argv[1], IMREAD_COLOR);

Mat B(A);  // Use the copy constructor
C = A;  // Assignment operator
```
&emsp;&emsp;All the above objects, in the end, point to the same single data matrix and making a modification using any of them will affect all the other ones as well.  
&emsp;&emsp;Nevertheless, their header parts are different.  

- create headers which refer to only a subsection of the full data  
```C++
Mat D (A, Rect(10, 10, 100, 100) );  // using a rectangle
Mat E = A(Range::all(), Range(1,3));  // using row and column boundaries
```

- copy the matrix, OpenCV provides `cv::Mat::clone()` and `cv::Mat::copyTo()` functions.  
```C++
Mat F = A.clone();
Mat G;
A.copyTo(G);
```
&emsp;&emsp;modifying F or G will not affect the matrix pointed to by the A's header.  

##### Storing methods
- To code the transparency of a color sometimes a fourth element, alpha (A), is added.  
- OpenCV standard display system composes colors using the BGR color space (red and blue channels are swapped places).  
- The HSV and HLS decompose colors into their **hue, saturation and value/luminance** components.  

##### Creating a Mat object explicitly  
- see the actual values. 
&emsp;&emsp;using the << operator of Mat. Be aware that this only works for two dimensional matrices.

- cv::Mat::Mat Constructor  
```C++
Mat M(2,2, CV_8UC3, Scalar(0,0,255));
cout << "M = " << endl << " " << M << endl << endl;
```
For two dimensional and multichannel images we first define their size: **row and column** count wise.  
specify the **data type** to use for storing the elements and the **number of channels** per matrix point.  
`CV_[The number of bits per item][Signed or Unsigned][Type Prefix]C[The channel number]`  

- Use C/C++ arrays and initialize via constructor  
```C++
int sz[3] = {2,2,2};
Mat L(3,sz, CV_8UC(1), Scalar::all(0));
```
&emsp;&emsp;Specify its dimension, then pass a pointer containing the size for each dimension.  

- cv::Mat::create function  
```C++
M.create(4,4, CV_8UC(2));
cout << "M = "<< endl << " "  << M << endl << endl;
```
reallocate its matrix data memory if the new size will not fit into the old one.  

- MATLAB style initializer  
```C++
// Specify size and data type to use:
Mat E = Mat::eye(4, 4, CV_64F);
cout << "E = " << endl << " " << E << endl << endl;

Mat O = Mat::ones(2, 2, CV_32F);
cout << "O = " << endl << " " << O << endl << endl;

Mat Z = Mat::zeros(3,3, CV_8UC1);
cout << "Z = " << endl << " " << Z << endl << endl;
```

##### Output formatting  
```C++
Mat R = Mat(3, 2, CV_8UC3);
randu(R, Scalar::all(0), Scalar::all(255));
```
- Default  
`cout << "R (default) = " << endl << R << endl << endl;`  
- Python  
`cout << "R (python)  = " << endl << format(R, Formatter::FMT_PYTHON) << endl << endl;`  
- Numpy  
`cout << "R (numpy) = " << endl << format(R, Formatter::FMT_NUMPY ) << endl << endl;`



## [High-level GUI](https://docs.opencv.org/4.x/d7/dfc/group__highgui.html)  

- [Flags related creating and manipulating HighGUI windows and mouse events](https://docs.opencv.org/4.x/d0/d90/group__highgui__window__flags.html)  

### Functions  
`#include <opencv2/highgui.hpp>`
- [namedWindow()](https://docs.opencv.org/master/d7/dfc/group__highgui.html#ga5afdf8410934fd099df85c75b2e0888b)
- [waitKey()](https://docs.opencv.org/master/d7/dfc/group__highgui.html#ga5628525ad33f52eab17feebcfba38bd7)  
- [destroyWindow()](https://docs.opencv.org/master/d7/dfc/group__highgui.html#ga851ccdd6961022d1d5b4c4f255dbab34)
- [destroyAllWindows()](https://docs.opencv.org/master/d7/dfc/group__highgui.html#ga6b7fc1c1a8960438156912027b38f481)  

## [Image file reading and writing](https://docs.opencv.org/4.x/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56)  
- [Flags used for image file reading and writing](https://docs.opencv.org/4.x/d4/da8/group__imgcodecs.html)  

### Functions  
`#include <opencv2/imgcodecs.hpp>`  

- [imread()](https://docs.opencv.org/master/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56)  
	
	> file formats  
	> [imread flags](https://docs.opencv.org/master/d8/d6a/group__imgcodecs__flags.html#ga61d9b0126a3e57d9277ac48327799c80)  
	
- [imshow()](https://docs.opencv.org/master/d7/dfc/group__highgui.html#ga453d42fe4cb60e5723281a89973ee563)  

- [imwrite()](https://docs.opencv.org/master/d4/da8/group__imgcodecs.html#gabbc7ef1aa2edfaa87772f1202d67e0ce)  


## Color  
- [Color conversions](https://docs.opencv.org/master/de/d25/imgproc_color_conversions.html)  

### [Color Space Conversions](https://docs.opencv.org/4.x/d8/d01/group__imgproc__color__conversions.html)  

#### Function
- [cvtColor()](https://docs.opencv.org/4.x/d8/d01/group__imgproc__color__conversions.html#ga397ae87e1288a81d2363b61574eb8cab)  
Converts an image from one color space to another.  
`#include <opencv2/imgproc.hpp>`  

#### [ColorConversionCodes](https://docs.opencv.org/4.x/d8/d01/group__imgproc__color__conversions.html#ga4e0972be5de079fed4e3a10e24ef5ef0)  
1. convert between RGB/BGR and grayscale  
    - COLOR_BGR2GRAY  
    - COLOR_RGB2GRAY  
    - COLOR_GRAY2BGR  
    - COLOR_GRAY2RGB  

# Color Image  


# Geometric Transformations  
> 2.6 Introduction to the Basic Mathematical Tools Used in Digital Image Processing: Geometric Transformations[^DIP, 4th]   

- Geometric transformations of digital images consist of two basic operations:[^DIP, 4th]  
(1) Spatial transformation of coordinates.  
(2) Intensity interpolation that assigns intensity values to the spatially transformed pixels.  

## Affine Transformations  
> [OpenCV Tutorial](https://docs.opencv.org/4.x/d4/d61/tutorial_warp_affine.html)  

affine transformations, which include **scaling**, **translation**, **rotation**, and **shearing**.[^DIP, 4th]  
### Rotation  
FIGURE 2.41: note the **counterclockwise direction** for a positive angle of rotation.[^DIP, 4th]
坐标系不动，点在坐标系中的位置变动（采用极坐标推导）  
$\theta$，逆时针旋转的角度   
$$
\begin{bmatrix}
x_2 \\
y_2 
\end{bmatrix}

=  

\begin{bmatrix}
cos\theta & -sin\theta \\
sin\theta & cos\theta
\end{bmatrix}

\times

\begin{bmatrix}
x_1 \\
y_1
\end{bmatrix}
$$

### OpenCV Functions  
`#include <opencv2/imgproc.hpp>`

- [cv::getAffineTransform](https://docs.opencv.org/4.x/da/d54/group__imgproc__transform.html#ga8f6d378f9f8eebb5cb55cd3ae295a999)  
- [cv::warpAffine](https://docs.opencv.org/4.x/da/d54/group__imgproc__transform.html#ga0203d9ee5fcd28d40dbc4a1ea4451983)  



## [cv::resize](https://docs.opencv.org/4.x/da/d54/group__imgproc__transform.html#ga47a974309e9102f5f08231edc7e7529d)  
### [InterpolationFlags](https://docs.opencv.org/4.x/da/d54/group__imgproc__transform.html#ga5bb5a1fea74ea38e1a5445ca803ff121)  
`#include <opencv2/imgproc.hpp>`  
|C++|Python||
|:-|:-|:-|
|INTER_NEAREST|cv.INTER_NEAREST|nearest neighbor interpolation|
|INTER_LINEAR|cv.INTER_LINEAR|bilinear interpolation|
|INTER_CUBIC|cv.INTER_CUBIC|bicubic interpolation|
|INTER_AREA|cv.INTER_AREA|resampling using pixel area relation. It may be a preferred method for image decimation, as it gives moire'-free results. But when the image is zoomed, it is similar to the INTER_NEAREST method.|



# Histogram  
[OpenCV--Histogram Calculation](https://docs.opencv.org/master/d8/dbc/tutorial_histogram_calculation.html)  
[OpenCV--Histogram Comparison](https://docs.opencv.org/master/d8/dc8/tutorial_histogram_comparison.html)  
[OpenCV--Back Projection](https://docs.opencv.org/master/da/d7f/tutorial_back_projection.html)  

> 3.3 Histogram Processing[^DIP, 4th]

## Histogram Calculation  

## Histogram Equalization  
[OpenCV: Histogram Equalization](https://docs.opencv.org/master/d4/d1b/tutorial_histogram_equalization.html)  

## Histogram Matching  
[OpenCV: Template Matching](https://docs.opencv.org/master/de/da9/tutorial_template_matching.html)  


# Intensity Transformation  
## Image Negatives  
> 3.2 Some Basic Intensity Transformation Functions[^DIP, 4th]  

The negative of an image with intensity levels in the range $[0, L−1]$  is obtained by using the negative transformation function, which has the form  
$$
s=L−1−r\tag{3-3}
$$

## Log Transformations  
> 3.2 Some Basic Intensity Transformation Functions[^DIP, 4th]  

The general form of the log transformation is  
$$
s=c*log⁡(1+r) \tag{3-4}
$$
where $c$ is a constant and it is assumed that $r≥0$.  

## Gamma correction  
> [UNDERSTANDING GAMMA CORRECTION](https://www.cambridgeincolour.com/tutorials/gamma-correction.htm)

### Power-Law (Gamma) Transformations  
> 3.2 Some Basic Intensity Transformation Functions[^DIP, 4th]  

Power-law transformations have the form
$$
s=c*r^\gamma \tag{3-5}
$$
where $c$ and $\gamma$ are positive constants. Sometimes $Eq. (3-5)$ is written as $s=c*(r+ε)^\gamma$  to account for offsets (that is, a measurable output when the input is zero).  

The response of many devices used for image capture, printing, and display obey a power law. By convention, the exponent in a power-law equation is referred to as gamma [hence our use of this symbol in Eq. (3-5)]. The process used to correct these power-law response phenomena is called **gamma correction** or **gamma encoding**.  


> 5.2 SCALING AND SIMPLE RGBs[^The GOES-R series, 2019]  

A common method of scaling a single image is
$$
C=255\times\left(\frac{V_{obs}-V_{min}}{V_{max}-V_{min}}\right)^\frac{1}{\gamma}
$$

### [OpenCV: Gamma correction](https://docs.opencv.org/master/d3/dc1/tutorial_basic_linear_transform.html)  

[Gamma correction](https://en.wikipedia.org/wiki/Gamma_correction) can be used to correct the brightness of an image by using a non linear transformation between the input values and the mapped output values:  
$$
O=\left(\frac{I}{255}\right)^{\gamma}\times255
$$

When $\gamma<1$, the **original dark regions will be brighter** and the histogram will be shifted to the right whereas it will be the opposite with $\gamma>1$.  

![](./gamma-correction-different values of gamma.png "different values of gamma")  


# Sampling and Quantization  
> 2.4 Image Sampling and Quantization[^DIP, 4th]  

## Representing Digital Images  

![](./dip_coordinate convention used to represent digital images.png)

We define the **origin** of an image at the **top left corner**.  
The **positive x-axis** extends downward and the **positive y-axis** extends to the right (the right-handed Cartesian coordinate system).  
The center of an $M\times{N}$ digital image with origin at $(0, 0)$  and range to $(M−1, N−1)$  is obtained by dividing M and N by 2 and rounding down to the nearest integer.  

The number of **intensity levels**, $L$, is an integer power of two, that is  
$$
L=2^k
$$
&emsp;&emsp;where $k$ is an integer. We assume that the discrete levels area equally spaced and that they are integers in the range $[0, L−1]$.

The number, $b$, of bits required to store a digital image is 
$$
b=M\times{N}\times{k}
$$
as usual, one byte equals 8 bits.

When an image can have $2^k$  possible intensity level, it is common practice to refer to it as a “**k-bit image**”, (e.g., a 256-level image is called an 8-bit image).


# Spatial Filtering  

## Fundamentals of Spatial Filtering  
> 3.4 Fundamentals of Spatial Filtering  

![](./The mechanics of linear spatial filtering.png)  

### Spatial Correlation and Convolution  

### Separable Filter Kernels  

## padding an image  
> 3.5 Smoothing (Lowpass) Spatial Filters[^DIP, 4th]

**zero padding** an image introduces dark borders in the filtered result, with the thickness of the borders depending on the size and type of the filter kernel used. Earlier, when discussing correlation and convolution, we mentioned two other methods of image padding: **mirror (also called symmetric) padding**, in which values outside the boundary of the image are obtained by mirror-reflecting the image across its border; and **replicate padding**, in which values outside the boundary are set equal to the nearest image border value. The latter padding is useful when the areas near the border of the image are constant. Conversely, mirror padding is more applicable when the areas near the border contain image details. In other words, these two types of padding attempt to "extend" the characteristics of an image past its borders.  

## Smoothing (Lowpass) Spatial Filters  
> 3.5 Smoothing (Lowpass) Spatial Filters  


## Sharpening (Highpass) Spatial Filters  
> 3.6 Sharpening (Highpass) Spatial Filters[^DIP, 4th]  



# Template Matching
> [tutorial](https://docs.opencv.org/4.x/de/da9/tutorial_template_matching.html)  


# References  
[^DIP, 4th]: Rafael C Gonzalez,Richard E Woods.Digital Image Processing:4th ed[M].New York:Pearson,2018.  

[^The GOES-R series, 2019]: Steven Goodman, Timothy Schmit, Jaime Daniels, Robert Redmon. The GOES-R series: a new generation of geostationary environmental satellites. Elsevier, 2019.
