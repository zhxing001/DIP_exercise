#include<iostream>
#include<opencv2\highgui\highgui.hpp>
#include"fog_move.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("test.jpg");
	imshow("test", img);
	
	cv::Mat res = cv::Mat::zeros(cv::Size(400, 400), CV_8UC1);
	res=min_BGR(img);
	imshow("res", res);

	Mat img_filter;
	min_filter(res, img_filter, 6);
	imshow("min_filter", img_filter);
	
	waitKey(0);
	return 0;
}