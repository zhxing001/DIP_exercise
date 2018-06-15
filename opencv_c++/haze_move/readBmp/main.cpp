#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("00014.bmp");
	imshow("img", img);

	waitKey();
	return 0;
}