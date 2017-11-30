#include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "原始图窗口"
#define WINDOW_NAME2 "效果图窗口"

Mat g_srcImage, g_grayImage;
int g_nThresh = 50;
int g_MaxThresh = 255;
RNG g_rng;
Mat g_cannyMat_output;
vector<vector<Point>>  g_contours; //存轮廓
vector<Vec4i>  g_hierarchy;

void on_ThreshChange(int, void*);


int main()
{
	g_srcImage = imread("1.jpg");
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);  //灰度化
	blur(g_grayImage, g_grayImage, Size(3, 3));         //平滑
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	createTrackbar("阈值", WINDOW_NAME1, &g_nThresh, g_MaxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);

	waitKey();
	return 0;
}

void on_ThreshChange(int, void*)
{
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);
	//canny检测边缘
	imshow("canny", g_cannyMat_output);
	findContours(g_cannyMat_output, g_contours, g_hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//找到轮廓 ,在这里debug下正常，release模式下有内存访问的错误。
	vector<Moments>  mu(g_contours.size());   
	//用来存放计算来得矩信息。
	//可以转到定义取看下Monment的值，实际上包含了10个矩，具体为：
	//Moments(double m00, double m10, double m01, double m20, double m11,
    //        double m02, double m30, double m21, double m12, double m03 )


	//遍历每一个区域，计算矩信息
	for (int i = 0;i < g_contours.size();i++)
	{
		mu[i] = moments(g_contours[i]);      //计算矩信息
	}
	
	//计算中心矩
	vector<Point2f>  mc(g_contours.size());  //中心距，分别x方向和y方向的，实际上就是质心
	for (int i = 0;i < g_contours.size();i++)
	{
		mc[i] = Point2f(float(mu[i].m10 / mu[i].m00), float(mu[i].m01 / mu[i].m00));
		//中心距的求法：一阶矩/零阶矩
	}

	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);

	//画图
	for (int i = 0;i < g_contours.size();i++)
	{
		Scalar color(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_contours, i, color, 2, 8, g_hierarchy, 0);         
		//这里的遍历体现在这个i上,绘制边缘
		circle(drawing, mc[i], 5, color);       //这里画的圆表示质心所在的位置
	}
	imshow(WINDOW_NAME2, drawing);
	
	cout << "----输出面积和轮廓长度：-------" << endl;
	cout << "-----当前canny检测阈值为：" << g_nThresh << "-------" << endl;
	for (int i = 0;i < g_contours.size();i++)
	{
		cout << "第" << i << "个轮廓的面积为：" << mu[i].m00 << endl;
	}
	
}
