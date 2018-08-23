#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>
#include<algorithm>

using namespace std;
using namespace cv;

#define PI 3.1415926

int main()
{
	//采用的是后向映射的方式来写
	Mat img = imread("2.jpg");
	cout << "原图尺寸：" << img.size() << endl;
	imshow("source_img", img);
 
	double angle =-10/180.0f*PI;         //这里就是除的180少写个f，以至于两个int相除肯定是不对的
	int height = img.rows;
	int width = img.cols;	

	//四个定点在旋转坐标系中的位置
	//  1  2
	//  3  4
	int SrcX1 = -width / 2;
	int SrcY1 = height / 2;
	int SrcX2 = width / 2;
	int SrcY2 = height / 2;
	int SrcX3 = -width / 2;
	int SrcY3 = -height / 2;
	int SrcX4 = width / 2;
	int SrcY4 = -height / 2;
	
	double cosAn = std::cos(angle);
	double sinAn = std::sin(angle);

	cout << "余弦" << cosAn << endl;
	cout << "正弦" << sinAn << endl;

	


	int DstX1 = (int)(SrcX1*cosAn - SrcY1*sinAn +0.5);
	int DstY1 = (int)(SrcX1*sinAn + SrcY1*cosAn +0.5);

	int DstX2 = (int)(SrcX2*cosAn - SrcY2*sinAn +0.5);
	int DstY2 = (int)(SrcX2*sinAn + SrcY2*cosAn +0.5);

	int DstX3 = (int)(SrcX3*cosAn - SrcY3*sin(angle)+0.5);
	int DstY3 = (int)(SrcX3*sinAn + SrcY3*cosAn +0.5);

	int DstX4 = (int)(SrcX4*cosAn - SrcY4*sinAn + 0.5);
	int DstY4 = (int)(SrcX4*sinAn + SrcY4*cosAn + 0.5);

	int DstWidth = max(abs(DstX1 - DstX4), abs(DstX2 - DstX3))+1;
	int DstHeight = max(abs(DstY1 - DstY4), abs(DstY2 - DstY3))+1;
	
	//旋转后的最合适的宽度和高度

	Mat Dst=Mat::zeros(DstHeight,DstWidth, img.type());
	
	//Dst.create(DstHeight, DstWidth, img.type());    //创建DST图像
	


	//映射回去的原图中的坐标
	int D2S_x=0;     
	int D2S_y=0;

	for (int i = 0; i < DstWidth; i++)
	{
		for (int j = 0; j < DstHeight; j++)
		{
			D2S_x = round(double(i - DstWidth / 2.0f)* cosAn  +  double(j - DstHeight / 2.0f)*sinAn + width / 2.0f);
			D2S_y = round(-double(i - DstWidth / 2.0f)*sinAn  +  double(j - DstHeight / 2.0f)* cosAn + height / 2.0f);
		

			if (Dst.channels() == 1)
			{
				if (D2S_x < 0 || D2S_x >= width || D2S_y < 0 || D2S_y >= height)
					Dst.at<uchar>(j, i) = 0;
				else
					Dst.at<uchar>(j, i) = img.at<uchar>(D2S_y,D2S_x);
			}
			else if (Dst.channels() == 3)
			{
				if (D2S_x < 0 || D2S_x >= width || D2S_y < 0 || D2S_y >= height)
					Dst.at<Vec3b>(j, i) = Vec3b(0, 0, 0);
				else
					Dst.at<Vec3b>(j, i) = img.at<Vec3b>(D2S_y,D2S_x);
			}
		}
	}

	imshow("rotate", Dst);

	waitKey();
	return 0;

}
