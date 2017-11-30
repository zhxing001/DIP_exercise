#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


int main()
{
	Mat srcImage = imread("1.jpg");   
	imshow("原图", srcImage);
	Mat midImage, dstImage;    //临时变量和目标图

	//Canny(srcImage, midImage, 40, 120, 3);
	//imshow("canny", midImage);
	//cvtColor(midImage, dstImage,COLOR_GRAY2BGR);   //这里是把单通道的转换为三通道的，但是R=G=B，所以还是灰色。
	//vector<Vec2f> lines;
	
	//---------------------------------------------------------------------

	//HoughLines(midImage, lines, 1, CV_PI / 180, 150,0,0);   //注意这里要输入的是8位二进制图像，只有0和255两种值
	////另外，hough变换对后面这个阈值非常敏感，非常容易误检，所以选择阈值的时候要试。所以标准霍夫变换不是很实用。
	////cout<<format(lines,Formatter::FMT_MATLAB);    //存的分别是r和theta，这里输出看下
	//
	//imshow("dstImage", dstImage);

	//for (int i = 0; i < lines.size(); i++)
	//{
	//	float rho = lines[i][0];
	//	float theta = lines[i][1];
	//	Point pt1, pt2;
	//	double a = cos(theta), b = sin(theta);
	//	double x0 = a*rho, y0 = b*rho;
	//	pt1.x = cvRound(x0 + 1000 * (-b));
	//	pt1.y = cvRound(y0 + 1000 * (a));
	//	pt2.x = cvRound(x0 - 1000 * (-b));
	//	pt2.y = cvRound(y0 - 1000 * (a));

	//	line(dstImage, pt1, pt2, Scalar(0, 0, 255),1,LINE_AA);

	//	
	//}

	//以上是标准霍夫变换的使用-----------------------------------------------------------

	//---------------------------------------------------------
	//vector<Vec4i> lines1;

	//HoughLinesP(midImage, lines1, 1, CV_PI / 180, 80, 20, 5);
	//for (int i = 0; i < lines1.size(); i++)
	//{
	//	Point pt1, pt2;
	//	pt1.x = lines1[i][0];
	//	pt1.y = lines1[i][1];
	//	pt2.x = lines1[i][2];
	//	pt2.y = lines1[i][3];

	//	line(dstImage, pt1, pt2, Scalar(0, 0, 255));
	//}
	//--------------------以上是累计概率霍夫变换，这个更好用些

	cvtColor(srcImage, midImage, COLOR_BGR2GRAY);
	
	imshow("gray", midImage);
	GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);
	//为什么一定要加一个高斯？
	vector<Vec3f> circles;
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 2, 20, 100, 200, 0, 0);  //梯度法
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center;
		center = Point(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(srcImage, center, 3, Scalar(0, 0, 255), -1);   //画实心圆心，三像素宽
		circle(srcImage, center, radius, Scalar(0, 0, 255), 3);  //画圆，3像素宽
	}

	imshow("HoughCircle", srcImage);
	imwrite("c.jpg", srcImage);
	waitKey();
	return 0;
}