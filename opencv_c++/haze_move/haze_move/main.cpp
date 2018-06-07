#include<iostream>
#include<opencv2\highgui\highgui.hpp>
#include"fog_move.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("test.jpg");
	imshow("test", img);
	
	/*cv::Mat res = cv::Mat::zeros(cv::Size(400, 400), CV_8UC1);
	res=min_BGR(img);
	imshow("res", res);
	
	
	cout << format( img(Rect(0, 0, 3, 3)), cv::Formatter::FMT_MATLAB) << endl;
	cout << format( res(Rect(0, 0, 3, 3)), cv::Formatter::FMT_MATLAB) << endl;

	Mat img_filter;
	min_filter(res, img_filter, 7);
	imshow("min_filter", img_filter);
	cout << "done!" << endl;*/
	int r = 7;
	double eps = 0.001;
	double w = 0.95;
	double maxV1 = 0.80;
	getV1(img,r, eps, w, maxV1);
	

	waitKey(0);
	return 0;
}