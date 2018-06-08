#include<iostream>
#include<opencv2\highgui\highgui.hpp>
#include"fog_move.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("test.jpg");
	imshow("test", img);
	
	
	/*double max;
	cv::minMaxLoc(img, NULL, &max, NULL, NULL);
	std::cout << max << endl;*/
	/*cv::Mat res = cv::Mat::zeros(cv::Size(400, 400), CV_8UC1);
	res=min_BGR(img);
	imshow("res", res);
	
	
	cout << format( img(Rect(0, 0, 3, 3)), cv::Formatter::FMT_MATLAB) << endl;
	cout << format( res(Rect(0, 0, 3, 3)), cv::Formatter::FMT_MATLAB) << endl;

	Mat img_filter;
	min_filter(res, img_filter, 7);
	imshow("min_filter", img_filter);
	cout << "done!" << endl;*/
	//int r = 81;
	//double eps = 0.001;
	//double w = 0.95;
	//double maxV1 = 0.80;
	//double A;
	
	/*getV1(img,r, eps, w, maxV1,A,V1);
	imshow("V1", V1);*/

	cv::Mat x = deHaze(img);
	imshow("x", x);

	waitKey(0);
	return 0;
}