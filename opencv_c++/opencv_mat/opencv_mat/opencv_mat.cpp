//----------opencv数据结构学习测试程序-------------
// zhxing
// 2017/5/13


#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;


int main()
{
	//------------【1.利用构造函数】----------------------------------
	Mat m(2, 2, CV_8UC3, Scalar(0, 0, 255));  //利用构造函数创建mat
	
	//------------【2.利用成员函数】---------------------------------
	Mat m1;
	m1.create(2,2,CV_8UC3);         //利用create函数，这是一个成员函数

	//------------【3.利用静态成员函数】-------------------------------
	Mat E = Mat::eye(3, 3, CV_8UC1);    //利用类的静态成员函数，这个是单位阵
	//Mat E = Mat::ones(3, 3, CV_8UC1);       //这种定义方式和matlab有些相似定义一些简单的矩阵
	//Mat E = Mat::zeros(3, 3, CV_8UC1);
	
	//------------【4.直接对小矩阵进行定义】---------------------------
	Mat c = (Mat_<double>(3, 3) << 2, 3, 4, 5, 6, 7, 8, 9, 1);   
	// 这里的写法参照上面即可，写明数据类型和行列数
	
	//-------------【5.为已存在的对象创建信息头】---------------------
	Mat c_row1 = c.row(1).clone();       //把已存在矩阵的一部分拿来重新构成一个矩阵
	//--------------构造矩阵的函数也不止这么几种，具体用到再查-------------
	
	//-------------------【opencv里格式化输出矩阵的方法】-------------------
	Mat r(5, 5, CV_8UC3);
	randu(r, Scalar::all(0), Scalar::all(255));       //先初始化一个矩阵
	//opencv里提供了许多格式化输出的方法
	cout << "默认风格：" << endl << r << endl;
	cout << "python风格：" << endl << format(r, Formatter::FMT_PYTHON) << endl;
	cout << "逗号风格：" << endl << format(r, Formatter::FMT_CSV) << endl;
	cout << "NUMPY风格：" << endl << format(r, Formatter::FMT_NUMPY) << endl;
	cout << "matlab风格：" << endl << format(r, Formatter::FMT_MATLAB) << endl;
	cout << "c语言风格：" << endl << format(r, Formatter::FMT_C) << endl;
	//远不止这几种风格，比较来看python和matlab还是比较好看的，matlab是因为看惯了吧
	

	//二维点的定义
	Point2d p1(5, 5);    //利用构造函数之间定义
	//三维点的定义         
	Point3f p2(3, 3, 3); //利用构造函数
	//这里其实还有很多类可以定义，具体用到的时候再查吧，比如f改成i或者d就可以代表不同的数据类型
	//高于三维的点就用mat去定义吧
	
	cout << p1 << endl << p2 << endl;

	Size s(1, 3);
	cout << s.area() << "," << s.height << s.width << endl;
	//size类里有成员函数可以算出其面积，也有内部数据成员宽和高

	
	return 0;            //这里很神奇，加上return 0控制台也是一闪而过，用Ctrl+F5直接运行还可以。
}