#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

#define WINDOW_NAME "程序窗口"

int g_nThresholdValue=100;        //阈值
int g_nThresholdType = 3;          //阈值化类型
Mat g_srcImage, g_dstImage, g_grayImage;    //图片准备


//void on_Threshold(int, void*);    //回调函数

int main()
{
	g_srcImage = imread("xy.jpg");
	imshow("原图", g_srcImage);
	//cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);  //转换为灰度图
	//imshow("灰度图", g_grayImage);
	Mat img;
	img = g_srcImage;
	//namedWindow(WINDOW_NAME,4);
	//createTrackbar("模式", WINDOW_NAME, &g_nThresholdType, 4, on_Threshold);
	//createTrackbar("阈值", WINDOW_NAME, &g_nThresholdValue, 255, on_Threshold);
	//on_Threshold(0, 0);     //初始化阈值回调函数

	//resize(g_srcImage, g_srcImage, Size(0,0), 0.4, 0.4,INTER_AREA);  
	//resize函数用法实例
	/*imshow("缩小", g_srcImage);
	imwrite("xy1.jpg", g_srcImage);*/
	
	pyrUp(g_srcImage, g_dstImage, Size(g_srcImage.cols * 2, g_srcImage.rows * 2));
	imshow("up", g_dstImage);
	
	pyrDown(img, g_grayImage, Size(img.cols / 2, img.rows / 2));
	imshow("dowm", g_grayImage);
	waitKey();
	return 0;

}


//void on_Threshold(int, void*)
//{
//	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
//	//阈值化并显示
//	imshow(WINDOW_NAME, g_dstImage);
//}
//
