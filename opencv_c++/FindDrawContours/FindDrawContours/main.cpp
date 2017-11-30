//查找绘制轮廓的综合示例程序，
#include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


//-----------【宏定义】------------------
#define  WINDOW_NAME1  "原始图像窗口"
#define  WINDOW_NAME2  "轮廓图"
//-----------【全局变量】---------------

Mat g_srcImage;
Mat g_grayImage;
Mat g_dstImage;
int g_nThresh = 80;
int g_nThresh_max = 255;
RNG g_rng;
Mat g_cannyMat_output;
vector<vector<Point>> g_Contours;
vector<Vec4i>  g_Hierarchy;

void on_ThreshChange(int, void*);

int main()
{
	g_srcImage = imread("zx.jpg", 1);  //灰度方式读入图像
	imshow(WINDOW_NAME1, g_srcImage);

	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));
	createTrackbar("canny阈值", WINDOW_NAME1, &g_nThresh, g_nThresh_max, on_ThreshChange);
	on_ThreshChange(0, 0);
	waitKey(0);
	return 0;
}


void on_ThreshChange(int, void*)
{
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2);
	//canny边缘检测	
	findContours(g_cannyMat_output, g_Contours, g_Hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//查找边缘
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (int i = 0;i < g_Contours.size();i++)
	{
		Scalar color(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_Contours, i, color, 2, 8, g_Hierarchy);
	
	}
	imshow(WINDOW_NAME2, drawing);
}



