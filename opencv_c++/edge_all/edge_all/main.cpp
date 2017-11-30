#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat g_srcImage, g_srcGrayImage, g_dstImage;
//原图  灰度图 目标图

Mat g_cannyDetectedEdges;
int g_cannyLowThreshold = 1;    //滑动条位置参数
//canny相关参数

Mat g_Sobel_x, g_Sobel_y;
Mat g_Sobel_xAbs, g_Sobel_yAbs;
int g_sobelSize = 1;
//Sobel相关变量

Mat g_Scharr_x, g_Scharr_y;
Mat g_Scharr_xAbs, g_Scharr_yAbs;
//scharr相关变量

static void on_Canny(int, void*);
static void on_Sobel(int, void*);  
void Scharr();


int main()
{
	g_srcImage = imread("zx.jpg");
	imshow("原图", g_srcImage);
	cvtColor(g_srcImage, g_srcGrayImage, COLOR_BGR2GRAY);
	imshow("灰度图", g_srcGrayImage);

	//g_dstImage.create(g_srcImage.size(), g_srcImage.type()); 
	//这句可有可无，可能在用到的时候会自动分配内存空间。

	namedWindow("canny");
	namedWindow("sobel");

	createTrackbar("canny_size", "canny", &g_cannyLowThreshold, 50, on_Canny);
	createTrackbar("sobel_size", "sobel", &g_sobelSize, 3, on_Sobel);
	on_Canny(0, 0);
	on_Sobel(0, 0);

	Scharr();
	

	waitKey();
	return 0;
}


static void on_Canny(int, void *)
{	
	blur(g_srcGrayImage, g_cannyDetectedEdges, Size(3, 3));  //先降噪
	Canny(g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold*2.5);
	//边缘检测得到灰度图。
	g_dstImage = Scalar::all(0);   //先全给0，因为待会要掩码拷贝
	g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);  
	//以canny边缘为掩码拷贝数据到原图，得到的是彩色的边缘。
	imshow("canny", g_dstImage);  //显示图像
}

static void on_Sobel(int, void*)
{
	Sobel(g_srcImage, g_Sobel_x, g_srcImage.depth(), 1, 0,g_sobelSize*2+1);
	convertScaleAbs(g_Sobel_x, g_Sobel_xAbs);   //取绝对值并归一化到0-255
	//x方向
	Sobel(g_srcImage, g_Sobel_y, g_srcImage.depth(), 1, 0, g_sobelSize * 2 + 1);
	convertScaleAbs(g_Sobel_y, g_Sobel_yAbs); //取绝对值并归一化到0-255
	//y方向

	addWeighted(g_Sobel_xAbs,0.5, g_Sobel_yAbs,0.5,0, g_dstImage);
	imshow("sobel", g_dstImage);
	//合并梯度并显示结果
}


void Scharr()
{
	Scharr(g_srcImage, g_Scharr_x,g_srcImage.depth(), 1, 0);   //x方向梯度
	convertScaleAbs(g_Scharr_x, g_Scharr_xAbs);

	Scharr(g_srcImage, g_Scharr_y, g_srcImage.depth(), 1, 0);   //y方向梯度
	convertScaleAbs(g_Scharr_y, g_Scharr_yAbs);

	addWeighted(g_Scharr_xAbs, 0.5, g_Scharr_yAbs, 0.5,0,g_dstImage);  //合并梯度
	imshow("scharr", g_dstImage);
}