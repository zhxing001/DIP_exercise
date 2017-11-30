


#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;



//-----------【主函数入口】----------------------
//	函数入口  main（）
//------------------------------------------------

int main()
{
	Mat srcImage, dstImage, gray;
	srcImage = imread("1.jpg");   
	imshow("原图",srcImage);
	cvtColor(srcImage, gray, COLOR_RGB2GRAY);
	imshow("灰度图", gray);        //灰度图
	Mat edge;
	blur(gray, edge, Size(3, 3));   //降噪
	Canny(edge, edge, 3, 9, 3);
	imshow("edge", edge);
	dstImage = Scalar::all(0);      //目标图像设置为0
	srcImage.copyTo(dstImage, edge);
	imshow("彩色边缘", dstImage);         //掩膜就是把非零的拷贝过去
	waitKey();
	return 0;

}







//------------【子函数原型部分】-----------------
//		子函数原型定义
//-----------------------------------------------



