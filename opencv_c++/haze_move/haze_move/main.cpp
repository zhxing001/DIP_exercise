#include<iostream>
#include<opencv2\highgui\highgui.hpp>
#include"fog_move.hpp"
#include<algorithm>


using namespace std;
using namespace cv;

int main()
{
	/*Mat img1= imread("test.jpg");
	imshow("原图", img1);*/
	
	//cout << log(10);
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
	/*int r = 81;
	double eps = 0.001;
	double w = 0.95;
	double maxV1 = 0.80;
	double A;
	cv::Mat V1;*/


	double start, time_cost;
	const double r_ratio = 0.01;
	cv::VideoCapture Video("C:\\Users\\zhxing\\Desktop\\张星\\去雾\\8.avi");
	unsigned video_num = Video.get(CV_CAP_PROP_FRAME_COUNT);
	unsigned height = Video.get(CV_CAP_PROP_FRAME_HEIGHT);
	unsigned width = Video.get(CV_CAP_PROP_FRAME_WIDTH);
	cout << height << "  " << width << endl;
	double r_= max(height*r_ratio, width*r_ratio);
	int r = max(r_, 3.0) * 4 / 2;
	cout << r << endl;

	Mat img;
	Mat img_remove_fog;

	for (unsigned frame = 0; frame < video_num; frame++)
	{
		Video.read(img);
		start = static_cast<double>(getTickCount());
		img_remove_fog = deHaze(img,r);
		time_cost = ((double)getTickCount() - start) / getTickFrequency();
	
		
		cout << "Time_cost:\t" << time_cost << endl;
		imshow("source_img", img);
		imshow("fog_remove", img_remove_fog);
		waitKey(10);
	}


	//double start = static_cast<double>(getTickCount());
	/*start = static_cast<double>(getTickCount());
	cv::Mat x = deHaze(img1);
	time_cost = ((double)getTickCount() - start) / getTickFrequency();
	cout << "Time_cost:\t" << time_cost << endl;
	
	imshow("去雾", x);*/

	waitKey(0);
	return 0;
}