//本程序总结了遍历图像像素的三种方法分别是指针，迭代器和动态地址计算
//2017年5月14测试通过


#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

//-----------【全局变量声明部分】------------------
//          全局变量声明
//-------------------------------------------------


//------------【全局函数声明部分】-----------------
//		子函数声明
//------------------------------------------------

void ColorReduce_C(Mat img_input, Mat &img_output, int div);
void ColorReduce_STL(Mat &img_input, Mat &img_output, int div);
void ColorReduce_AT(Mat &img_input, Mat &img_output, int div);


//-----------【主函数入口】----------------------
//	函数入口  main（）
//------------------------------------------------

int main()
{
	Mat img_input = imread("C:\\Users\\zh_xing\\Desktop\\opencv\\chunxia.jpg");
	Mat img_output(img_input.rows, img_input.cols, img_input.type());
	//原样来一张图片，但是矩阵数没有指定
	imshow("原图", img_input);
	

	ColorReduce_C(img_input, img_output, 10);
	imshow("c访问减色后图像",img_output);
	ColorReduce_STL(img_input, img_output, 50);
	imshow("迭代器访问减色后图像", img_output);
	ColorReduce_AT(img_input, img_output, 100);
	imshow("AT访问减色后图像", img_output);
	waitKey();
	return 0;

}







//------------【子函数原型部分】-----------------
//		子函数原型定义
//-----------------------------------------------



//-----------【用指针访问像素】------------------
void ColorReduce_C(Mat img_input, Mat &img_output, int div)
 //这里的img_output的引用必不可少，因为如果只做形参，就不能够对传入的这个
//	地址的变量做修改，一开始忘记写了就不对，如果要在函数里修改参数的值，必须用引用把地址传进来
{	
	img_output = img_input.clone();  //复制实参到临时变量
	int rowNum = img_output.rows;  //行数
	int colNum = img_output.cols*img_output.channels();  //列*通道=每一行元素数
	cout << rowNum;
	cout << colNum;

	for (int i = 0; i < rowNum; i++)
	{
		uchar*data = img_output.ptr<uchar>(i); //获得每行的首地址
		for (int j = 0; j < colNum; j++)
		{
			data[j] = (data[j] / div)*div;     //逐行处理，颜色缩减
		}
	}
		//处理结束
}


//----------------【用迭代器操作像素】-----------------------
//这个我没怎么看懂，看了STL之后再回来看下吧-----------------
void ColorReduce_STL(Mat &img_input, Mat &img_output, int div)
{
	img_output = img_input.clone();
	Mat_<Vec3b>::iterator it = img_output.begin<Vec3b>();
	//初始位置的迭代器
	Mat_<Vec3b>::iterator itend = img_output.end<Vec3b>();
	//终止位置的迭代器

	for (; it != itend; ++it)
	{
		(*it)[0] = (*it)[0] / div*div;
		(*it)[1] = (*it)[1] / div*div;
		(*it)[2] = (*it)[2] / div*div;

	}
}


//----------------【用“动态地址计算”操作像素】-----------------------
//		简洁明了，符合对像素的认识，通道操作更容易---------------------
void ColorReduce_AT(Mat &img_input, Mat &img_output, int div)
{
	img_output = img_input.clone();     //复制实参到临时变量
	int row_Num = img_output.rows;
	int col_Num = img_output.cols;
	//获得行列
	for (int i = 0; i < row_Num; i++)
	{
		for (int j = 0; j < col_Num; j++)
		{
			img_output.at<Vec3b>(i, j)[0] = img_output.at<Vec3b>(i, j)[0] / div*div;
			img_output.at<Vec3b>(i, j)[1] = img_output.at<Vec3b>(i, j)[1] / div*div;
			img_output.at<Vec3b>(i, j)[2] = img_output.at<Vec3b>(i, j)[2] / div*div;
			//处理三个通道
		}
	}
}