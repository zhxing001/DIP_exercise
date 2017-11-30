//#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
//#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;


void creattable(Mat &table, uchar val);

int main()
{
	Mat table;
	creattable(table, 10);
	cout << table;
	
	Mat img = imread("C:\\Users\\zh_xing\\Desktop\\opencv\\chunxia.jpg");
	//读入图像
	Mat img_out;
	//创建存储图像
	double time0 = static_cast<double>(getTickCount()); //记录起始时间
	LUT(img, table, img_out);
	//look up table
	imshow("缩减颜色空间后", img_out);
	time0 = (double(getTickCount())-time0)/getTickFrequency(); //除以频率可以算出秒
	cout << "LUT的时间是：" << time0 << "秒" << endl;
	waitKey();
	return 0;
}


//------------【创建查找表】--------------
//  这里是常见256阶查找表，步长为val-----
void creattable(Mat &table, uchar val)
{
	table.create(1, 256, CV_8UC1);
	uchar *p = table.data;
	//指针遍历比较快
	for(int i=0;i<256;i++)
	{
		p[i] = i / val * val;   
	}
}


