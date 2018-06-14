

#include<opencv2\highgui\highgui.hpp>
#include<iostream>
#include"enhance_and_denoising.h"

using namespace std;
using namespace cv;


VideoCapture video("C:\\Users\\zhxing\\Desktop\\张星\\张星\\图像增强\\红外图像\\整体效果\\1.avi");

//获取帧数，宽和高
int num_frame = video.get(CV_CAP_PROP_FRAME_COUNT);


int main()
{

	Mat frame;
	Mat frame_de;
	Mat enhance_frame;
	for (int i = 1; i < num_frame; i++)
	{
		video.read(frame);
		
		denoise(frame, frame_de);
		enhance(frame_de, enhance_frame, 0.05);
		
		imshow("source_img", frame);
		imshow("enhance", enhance_frame);
		waitKey(10);
	}

	/*Mat img = imread("8.bmp");
	imshow("img", img);
	Mat img_enhance;
	Mat img_8uc1;
	cvtColor(img, img_8uc1,CV_BGR2GRAY);

	enhance1(img, img_enhance, 5, 10);
	Mat img_enhance_UC8;
	img_enhance.convertTo(img_enhance_UC8, CV_8UC1);


	enhance(img, img_enhance, 0.05);
	imshow("enhance", img_enhance);*/

	//Mat img = imread("1_noise.bmp");
	//imshow("source_img", img);
	////img.convertTo(img_8uc1, CV_8UC1);
	////equalizeHist(img_8uc1, img_enhance);
	//Mat img_denoise;
	//denoise(img, img_denoise);
	//imshow("denoise", img_denoise);
	waitKey();
	return 0;
}

