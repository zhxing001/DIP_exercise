//漫水填充测试程序
//zhxing
//2017-06-03 16:03:05    调试还算顺利，因为都是自己敲的，大概花了三个小时的时间。
//中间cvtcolor的函数又出现了一些问题，和上次双边滤波的问题一样，现在也不知道具体问题出在哪里
//重新配置了一下属性表现在没什么问题了，说起来被这个东西也搞了好几个小时，


#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

//--------------【全局变量声明】--------------------
Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;  //原图，效果图，灰度图，掩模图
int g_nFillMode = 1;      //漫水填充的模式
int g_nlow = 20, g_nUp = 20;  //正负差的最大值
int g_nConnectivity = 4;     //floodFill函数标识符第八位的联通值
int g_bIsColor = true;			 //是否为彩色图的标识符
bool g_bUserMask = false;   //是否显示掩膜窗口的标识符
int g_nNewMaskVal = 255;    //新的重新绘制的像素值

//----------------【鼠标回调函数】--------------------
static void onMouse(int event, int x, int y, int, void *)
{
	if (event != EVENT_LBUTTONDOWN)    //左键没有被按下
	{
		return;
	}
	Point seed = Point(x, y);
	int low = (g_nFillMode == 0 )? 0 : g_nlow;  
	int up = (g_nFillMode == 0 )? 0 : g_nUp;
	//空范围的漫水填充这里选择0相当于不填充
	int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
	//标识符0-7为g_nConnectivity，8-15位为g_nNewMaskVal向左移8为的值，16-23位为 FLOODFILL_FIXED_RANGE或者0，（这一位有fiilmode选择）

	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;   //随机生成一个颜色值
	cout << "color:"<<r << g << b<<endl;
	Rect ccomp;   //定义重绘区域的最小矩形边界
	Scalar newVal = (g_bIsColor==1) ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + b*0.114);
	//看图的模式，彩色模式则选择Scalar(b, g, r),灰度模式选择Scalar(r*0.299 + g*0.587 + b*0.114)
	Mat dst = (g_bIsColor==1) ? g_dstImage : g_grayImage;
	//目标图赋值，到底是彩色还是灰度取决于g_bIsColor

	int area;     //统计被填充的像素个数，FLOODFILL的返回值就是这个,这个数有点小吧,int才多少位
	if (g_bUserMask)   //使用掩膜
	{
		threshold(g_maskImage, g_maskImage, 1, 128, THRESH_BINARY);
		area = floodFill(dst, g_maskImage, seed, newVal, &ccomp, Scalar(low, low, low), Scalar(up, up, up), flags);
		imshow("mask", g_maskImage);
	}
	
	else      //不适用掩膜
	{
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(low, low, low), Scalar(up, up, up), flags);
	}
	imshow("效果图", dst);
	cout <<area << "个像素被重新绘制" << endl;
}


int main()
{
	g_srcImage = imread("xyjy.jpg");
	imshow("原图", g_srcImage);
	g_srcImage.copyTo(g_dstImage);     //原图赋值到目标图，连同数据也一并复制。
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);    //转换灰度图
	imshow("", g_grayImage);
	g_maskImage.create(g_srcImage.rows + 2, g_srcImage.cols + 2, CV_8UC1);
	//利用原始图像的尺寸创建掩膜图像
	namedWindow("效果图", WINDOW_AUTOSIZE);
	
	createTrackbar("负差最大值", "效果图", &g_nlow, 255, 0);
	createTrackbar("正差最大值", "效果图", &g_nUp, 255, 0);
	//创建滑动条
	setMouseCallback("效果图", onMouse, 0);
	//鼠标回调函数

	while (1)
	{
		imshow("效果图", g_bIsColor ? g_dstImage : g_grayImage);
		int c = waitKey(0);
		if ((c & 255) == 27)
		{
			cout << "程序退出" << endl;
			break;
		}
		switch (char(c))
		{
		case '1':
			if (g_bIsColor)   //若原图为彩色，则转换成灰度图，并将掩膜所有元素置0
			{
				cout << "键盘“1”被按下，切换彩色灰度模式，当前操作将彩色切换成灰度模式" << endl;
				cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
				g_maskImage = Scalar::all(0);
				g_bIsColor = false;   //标识符置0，表示当前为灰度图像
			}
			else
			{
				cout << "键盘1被按下，当前从灰度彩色转换为灰度" << endl;
				g_srcImage.copyTo(g_dstImage);
				g_maskImage = Scalar::all(0);
				g_bIsColor = true;      

			}
			break;
		case '2':
			if (g_bUserMask)
			{
				destroyWindow("mask");
				g_bUserMask = 0;
			}
			else
			{
				namedWindow("mask", 0);
				g_maskImage = Scalar::all(0);
				imshow("mask", g_maskImage);
				g_bUserMask = 1;
			}
			break;
		case '3':
			cout << "键盘3被按下，灰度原始图像" << endl;
			g_srcImage.copyTo(g_dstImage);
			cvtColor(g_dstImage, g_grayImage, COLOR_RGB2GRAY);
			g_maskImage = Scalar::all(0);
			break;
		case '4':
			cout << "按键4被按下，使用渐变，固定填充范围填充" << endl;
			g_nFillMode = 1;
			break;
		case '5':
			cout << "按键5被按下，使用渐变，浮动范围进行漫水填充" << endl;
			g_nFillMode = 2;
			break;
		case '7':
			cout << "按键7被按下，操作标识符低八位采用4邻域" << endl;
			g_nConnectivity = 4;
			break;
		case '8':
			cout<< "按键7被按下，操作标识符低八位采用8邻域" << endl;
			g_nConnectivity = 8;
			break;
		}
	}

	return 0;
	
}