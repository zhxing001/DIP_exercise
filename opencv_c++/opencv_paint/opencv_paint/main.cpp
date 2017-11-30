#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<math.h>

using namespace std;
using namespace cv;

//-----------------【子函数声明】-----------------------------------
void DrawEllipse(Mat img, double angle);   //自定义画椭圆函数,给出图像和角度
void DrawFilledCircle(Mat img, Point center);  //自定义画实心圆，给出圆心和图像
void Drawploy(Mat img);      //画多边形，这里画个正方形吧

//----------------【宏定义】----------------------------------------
#define WINDOW_WIDTH 600


int main() 
{
	Mat img(WINDOW_WIDTH, WINDOW_WIDTH,CV_8UC3,Scalar(120,120,120)); 
	//定义灰色背景图
	DrawEllipse(img, 0);
	DrawEllipse(img, 45);
	DrawEllipse(img, 90);
	DrawEllipse(img,135);
	//画椭圆
	DrawFilledCircle(img, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));
	//画实心圆
	Drawploy(img);
	imshow("ellipse", img);
	waitKey();
	
	return 0;
}


//------------------【自定义绘制椭圆】--------------
//---绘制不同角度的椭圆-----------------------------
//--------------------------------------------------
void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;  //线宽2个像素
	int linetype = 8;   //线型为8（8联通）
	ellipse(img, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),   
		Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16), 
		angle, 0, 360, 
		Scalar(255, 0, 0), thickness);

}

//------------------【自定义绘制圆】--------------
//- 要求给出要画的位置以及图像-----------------------------
//--------------------------------------------------
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;   //线宽-1，画实心
	int linetype = 8;
	circle(img, center, WINDOW_WIDTH / 32, Scalar(0, 255, 0), thickness, linetype);
	//多看函数原型，其实讲的很清楚
}

// ------------------【自定义绘制多边形】--------------
//---这个我随便画吧-----------------------------
//--------------------------------------------------
void Drawploy(Mat img)
{
	int linetype = 8;
	Point rookPoints[1][4];
	rookPoints[0][0] = Point(  WINDOW_WIDTH / 4,  WINDOW_WIDTH / 4);
	rookPoints[0][1] = Point( 3*WINDOW_WIDTH / 4,  WINDOW_WIDTH / 4);
	rookPoints[0][2] = Point(3 * WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 4);
	rookPoints[0][3] = Point(  WINDOW_WIDTH / 4, 3* WINDOW_WIDTH / 4);
	const Point *ppt[1] = {rookPoints[0]};
	int npt[] = { 4 };
	polylines(img, ppt, npt,1,true,Scalar(0,255,0));
	
	//fillPoly(img, ppt, npt, 1, Scalar(0, 255, 0));
    //这个是画实心的


}