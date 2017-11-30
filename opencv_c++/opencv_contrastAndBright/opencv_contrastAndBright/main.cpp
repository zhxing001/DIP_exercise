#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//-----------【全局变量声明部分】------------------
//          全局变量声明
//-------------------------------------------------
int g_nConstractValue;
int g_nBrightValue;
Mat g_scrImage, g_dstImage;

//------------【全局函数声明部分】-----------------
//		子函数声明
//------------------------------------------------
static void on_ConstractAndBright(int, void *);


//-----------【主函数入口】----------------------
//	函数入口  main（）
//------------------------------------------------

int main()
{
	g_scrImage = imread("C:\\Users\\zh_xing\\Desktop\\opencv\\cx.jpg");
	g_dstImage = Mat::zeros(g_scrImage.size(), g_scrImage.type());
	g_nBrightValue = 50;
	g_nConstractValue = 50;   //设定初始值
	namedWindow("效果图窗口", WINDOW_FREERATIO);
	createTrackbar("对比度", "效果图窗口", &g_nConstractValue, 200, on_ConstractAndBright);
	createTrackbar("亮度", "效果图窗口", &g_nBrightValue, 100, on_ConstractAndBright);

	on_ConstractAndBright(g_nConstractValue, 0);
	on_ConstractAndBright(g_nBrightValue, 0);
	waitKey();
	return 0;

}


//------------【滑动条回调函数】-----------------
//		改变图像对比度和亮度值
//-----------------------------------------------
static void on_ConstractAndBright(int, void *)
{
	namedWindow("原始图", 1);   //创建窗口
	for (int x = 0; x < g_scrImage.rows; x++)
	{
		for (int y = 0; y < g_scrImage.cols; y++)
		{
			for (int z = 0; z < 3; z++)
				g_dstImage.at<Vec3b>(x, y)[z] = saturate_cast<uchar>((g_nConstractValue*0.01)*(g_scrImage.at<Vec3b>(x, y)[z]) + g_nBrightValue);
		}		//遍历每个像素对其对比度和亮度进行调整
	}

	imshow("原始图", g_scrImage);
	imshow("效果图窗口", g_dstImage);
}
