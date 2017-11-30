
#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
using namespace cv;   //类名空间包含，本程序下的类名就可以不包含cv::前缀可以直接使用。
using namespace std;


//--------------------【变量声明】------------------------
Mat	img, img_after;
int on_TrackerBarChose = 0;    //选择膨胀或者腐蚀
int on_ElementSize = 3;       //选择内核尺寸

//-------------------【函数声明】------------------------
void process();
void on_TrackBarChose(int, void*);
void on_ElementSizechange(int, void*);

int main()
{
	img = imread("chunxia.jpg");   
	//Mat img = imread("C:\\Users\\zh_xing\\Desktop\\opencv\\a.jpg"); 
	//这里不能重新定义Mat,否则会出现内存错误，c++里变量不能重新被定义，所以这个Mat不能加，另外这个Mat必须定义
	//成全局变量，是因为回调函数定义在主函数外。
	namedWindow("原图");
	imshow("原图", img);
	
	
	namedWindow("【效果图】");
	Mat element=getStructuringElement(MORPH_RECT, Size(on_ElementSize+1, on_ElementSize+1));
	//这个element和回调函数的element不存在重新定义的情况，因为各自的生存期并不冲突。
	erode(img, img_after, element);
	imshow("【效果图】", img_after);

	createTrackbar("erode(0)_or_dilate(1)", "【效果图】", &on_TrackerBarChose, 1, on_TrackBarChose);
	createTrackbar("ElementSize", "【效果图】", &on_ElementSize, 25, on_ElementSizechange);
	
	while(char(waitKey(1))!='q'){}
	return 0;
}

void process()
{
	Mat element = getStructuringElement(MORPH_RECT, Size(on_ElementSize+1, on_ElementSize+1));
	if (on_TrackerBarChose ==0)
	{
		erode(img, img_after, element);
	}
	else
	{
		dilate(img, img_after, element);
	}
	imshow("【效果图】", img_after);
}

void on_TrackBarChose(int, void*)
{
	process();
}

void on_ElementSizechange(int, void*)
{
	process();
}