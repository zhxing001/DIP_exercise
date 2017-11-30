//dft测试程序
//zhxing  2017-05-30 17:42:48


#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<math.h>          

using namespace cv;
using namespace std;



//-----------【主函数入口】----------------------
//	函数入口  main（）
//------------------------------------------------

int main()
{
	Mat srcImage = imread("C:/Users/zh_xing/Desktop/opencv/cx.jpg",0);  //以灰度读入
	if (!srcImage.data) {
		cout << "读取错误，请检查图片路径是否正确" << endl;
		return false;
	}
	imshow("", srcImage);

	//扩充边界，扩充的目的是提升dft运算的速度
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);
	Mat padded;   //定义矩阵存放扩充后的图像
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));
	//全0填充
	//两页，第一页是double后的原灰度图，第二页是全零矩阵
	Mat planes[] = { Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F) };   //size（）获得的是一个size型的数据
	
	
	//为DFT的结果开辟内存空间，两个通道分别存放实数和虚数
	/*Mat x;
	planes[0].convertTo(x, CV_8U);*/    //这里是测试下，imshow默认显示的是uint8型的，如果是double的话imshow只显示归一化的结果
									   //如果只是转换成double的话，要归一化之后用imshow显示，如果直接显示则会出现全白的结果
	
	Mat complexI;
	merge(planes, 2, complexI);    //合并成一个通道

	dft(complexI, complexI);   //原位FFT
	
	//将复数转换为幅值
	split(complexI, planes);   //分离通道
	magnitude(planes[0], planes[1], planes[0]);   //求幅值，放在实数的通道里
	Mat magnitudeImage = planes[0];            //把幅值图像单独拿出来

	//傅里叶变换的值很大，大到不适合直接显示，所以我们把这种线性转化成对数，会好很多
	magnitudeImage += Scalar::all(1);     //加1？？  应该是为log做准备，要所有的数大于0
	log(magnitudeImage, magnitudeImage);        //求对数

	
	
	//频谱中心化
	magnitudeImage = magnitudeImage(Rect(0, 0, srcImage.cols, srcImage.rows));  
	//原始图像扩展后进行的傅里叶变换，这里变回来。
	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);
	//归一化

	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	//cx是行，反而是y的坐标，opencv是以左上角为坐标系原点，左手系
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));    //ROI左上区域
	Mat q1(magnitudeImage, Rect(cx,0, cx, cy));    //右上
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));   //左下
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));  //右下
	//交换象限
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	//左上与右下
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	//右上与左下


	namedWindow("频谱", WINDOW_FREERATIO);
	imshow("频谱", magnitudeImage);




	waitKey();
	return 0;

}


