#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;


int main()
{
	Mat img = imread("2.jpg", 0);
	imshow("source_img", img);

	const double angle = 10/180*CV_PI;
	const double cosAngle = cos(angle);
	const double sinAngle = sin(angle);




	waitKey();
	return 0;

}
