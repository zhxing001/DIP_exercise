//线性滤波综合测试程序
//author  zhxing
//2017-06-01 10:24:43

#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//---------------------【全局变量】-------------------
Mat g_inputImage, g_outImage1, g_outImage2, g_outImage3, g_outImage4, g_outImage5;
//输入及输出图像
int g_nBoxFilterValue = 3;
int g_nMeanBlurValue = 3;
int g_nGaussianBlurValue = 3;
int g_nMedianBlurValue = 3;
int g_nBilateralValue = 5;
//滤波的滤波核初始大小

//--------------------【全局函数声明】--------------------
static void on_BoxFilter(int, void*);
static void on_MeanBlur(int, void*);
static void on_GaussianBlur(int, void*);
static void on_MidianBlur(int, void*);      //中值滤波
static void on_BilateralFilter(int, void*);  //双边滤波
//回调函数声明，最后做成轨迹条可以改变轨迹条的大小


int main()
{
	
	g_inputImage = imread("C:/Users/zh_xing/Desktop/opencv/xyjy.jpg");
	if (!g_inputImage.data)
	{
		cout << "图片路径有问题，确认图片路径正确再运行程序！" << endl;
		return 0;
	}

	g_outImage1 = g_inputImage.clone();
	g_outImage2 = g_inputImage.clone();
	g_outImage3 = g_inputImage.clone();
	g_outImage4 = g_inputImage.clone();
	g_outImage5 = g_inputImage.clone();

	namedWindow("原图窗口");
	imshow("原图窗口", g_inputImage);
	
	
	
	//创建窗口
	namedWindow("方框滤波");
	createTrackbar("内核值", "方框滤波", &g_nBoxFilterValue, 30, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);
	

	namedWindow("均值滤波");
	createTrackbar("内核值", "均值滤波", &g_nMeanBlurValue, 30, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue, 0);
	

	namedWindow("高斯滤波");
	createTrackbar("内核值", "高斯滤波", &g_nGaussianBlurValue, 30, on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue, 0);
	
	namedWindow("中值滤波");
	createTrackbar("邻域大小", "中值滤波", &g_nMedianBlurValue, 40, on_MidianBlur);
	on_MidianBlur(g_nMedianBlurValue, 0);

	namedWindow("双边滤波");
	createTrackbar("邻域大小", "双边滤波", &g_nBilateralValue, 30, on_BilateralFilter);
	on_BilateralFilter(g_nBilateralValue, 0);      //调试的时候这句话会出现内存访问出错，回调函数的问题？
	namedWindow("双边");
	bilateralFilter(g_inputImage, g_outImage5, 10, 20, 5);
	imshow("双边", g_outImage5);
	cout << "请滑动滚动条以观察滤波结果" << endl;

	//用双线性滤波这个函数就会出现错误，单独用也会出现内存访问错误，不知道什么原因

	waitKey();
	return 0;

		

}


//---------------------【子函数声明】------------------------

//-----------------【方框滤波】------------------------------
static void on_BoxFilter(int, void*)
{
	boxFilter(g_inputImage, g_outImage1, -1,Size(g_nBoxFilterValue+1,g_nBoxFilterValue+1));
	imshow("方框滤波", g_outImage1);
}

//-----------------【均值滤波】-----------------------------
static void on_MeanBlur(int, void*)
{
	blur(g_inputImage, g_outImage2, Size(g_nMeanBlurValue+1, g_nMeanBlurValue+1));
	imshow("均值滤波", g_outImage2);  //这两个Size都加了个1，加1的原因是卷积核尺寸不能是0，会引起内存访问错误
}

//--------------- -【高斯滤波】---------------------------------------
static void on_GaussianBlur(int, void*)
{
	GaussianBlur(g_inputImage, g_outImage3, Size(g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1), 0, 0);
	imshow("高斯滤波", g_outImage3);
}

//--------------【中值滤波】------------------------------------------
static void on_MidianBlur(int, void*)
{
	medianBlur(g_inputImage, g_outImage4, g_nMedianBlurValue*2+1);
	imshow("中值滤波", g_outImage4);
}

static void on_BilateralFilter(int, void*)
{
	bilateralFilter(g_inputImage, g_outImage5, g_nBilateralValue, g_nBilateralValue * 2, g_nBilateralValue / 2);
	imshow("双边滤波", g_outImage5);

}