//测试下ROI操作
//zhxing


#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

//-----------【全局变量声明部分】------------------
//          全局变量声明
//-------------------------------------------------


//------------【全局函数声明部分】-----------------
//		子函数声明
//------------------------------------------------




//-----------【主函数入口】----------------------
//	函数入口  main（）
//------------------------------------------------

int main()
{
	Mat img = imread("C:\\Users\\zh_xing\\Desktop\\opencv\\chunxia.jpg");
	Mat logo= imread("C:\\Users\\zh_xing\\Desktop\\opencv\\logo.jpg");
	Mat img_roi = img(Rect(100, 100, logo.cols, logo.rows));
	//Mat img_roi = img(Rect(100, 100, logo.cols, logo.rows)).clone();
	//利用Rect创建感兴趣区域,这样直接创建的感兴趣区域是和原图相关的.
	//如果利用clone函数，则就建立了一个新的矩阵，修改这个矩阵不会改变原图的。
	
	img_roi=Mat::zeros(img_roi.rows, img_roi.cols, CV_8UC3);   
	//这句测试了下直接操作img_roi也会对原图像造成影响
	imshow("roi", img_roi);
	Mat mask = imread("C:\\Users\\zh_xing\\Desktop\\opencv\\logo.jpg",0);
	//Mat mask = Mat::ones(img_roi.rows, img_roi.cols, CV_8UC1);
	//这里的掩模矩阵只要是非零的就可以了,主要是copyto函数的用法决定的
	cout << format(mask,Formatter::FMT_MATLAB);
	//创建掩模
	logo.copyTo(img_roi, mask);
	//拷贝过去
	imshow("12", img);


	
	waitKey();
	return 0;

}


//------------【子函数原型部分】-----------------
//		子函数原型定义
//-----------------------------------------------



