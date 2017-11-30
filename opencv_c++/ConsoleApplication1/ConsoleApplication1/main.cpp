#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("C:/Users/sally/Desktop/xy.jpg");
	imshow(" ",img);
	waitKey(5000);
	return 0;
}
