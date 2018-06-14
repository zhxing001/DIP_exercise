

#include<opencv2\highgui\highgui.hpp>
#include<iostream>
#include"enhance_and_denoising.h"

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("4.tiff");
	imshow("img", img);
	Mat img_enhance;
	Mat img_8uc1;
	cvtColor(img, img_8uc1,CV_BGR2GRAY);

	/*enhance1(img_8uc1, img_enhance, 30, 60);
	Mat img_enhance_UC8;
	img_enhance.convertTo(img_enhance_UC8, CV_8UC1);*/


	enhance(img, img_enhance, 0.01);
	imshow("enhance", img_enhance);


	img.convertTo(img_8uc1, CV_8UC1);
	//equalizeHist(img_8uc1, img_enhance);
	//imshow("enhance", img_enhance_UC8);
	waitKey();
	return 0;
}

