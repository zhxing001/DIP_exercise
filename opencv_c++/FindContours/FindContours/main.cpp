//二值图像查找并绘制轮廓

#include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


int main()
{
	Mat srcImage = imread("contour.bmp", 0);   //灰度模式读入
	imshow("原图", srcImage);
	Mat dstImage = Mat::zeros(srcImage.size(), CV_8UC3);
	//在三通道的dstimage上绘出彩色轮廓
	srcImage = srcImage > 128;   //取阈值大于128的一部分
	imshow("阈值之后的图像", srcImage);

	//cout << srcImage(Range(1, 100), Range(1, 20)) << endl;
	//这里想看下取阈值之后的是什么东西，输出全是255和0？也算是2值图像？
	vector<vector<Point>>  contours;
	vector<Vec4i> hierarchy;
	findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	int index = 0;          //很神奇的是release模式下这里会出现内存访问冲突的问题，debug模式下正常。
	for (;index >= 0;index = hierarchy[index][0])
	{
		Scalar color(255,255,255);
		drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);

	}
	imshow("轮廓", dstImage);

	cout << contours[5];
	//自己画图试了一下,contours这个数据的结构是这样的。
	//轮廓1--轮廓2--轮廓3--……，然后每个轮廓都是一个向量，而向量的元素是点，这些点连起来就构成轮廓。
	waitKey(0);
	return 0;
}
