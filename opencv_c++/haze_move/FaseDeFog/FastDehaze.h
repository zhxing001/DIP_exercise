#pragma once


#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<algorithm>

#include<vector>


using namespace cv;
using std::cout;
using std::endl;
using std::vector;

void min_filter(cv::Mat &src_img, cv::Mat &res_img, int kernel_size);
cv::Mat min_BGR(cv::Mat &src_img);
cv::Mat max_BGR(cv::Mat &src_img);
Mat getLx_A(Mat &M_min, Mat &img, float p, int kernel_size, float &A);
Mat FastDehaze(Mat &Img, const double p,const int kernel_size,float eps=0.0001);


//最小值滤波，
void min_filter(cv::Mat &src_img, cv::Mat &res_img, int kernel_size)
{
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * kernel_size - 1, 2 * kernel_size - 1));
	cv::erode(src_img, res_img, element);
	//cv::imshow("dark_channel", res_img);
}


//获取通道的最小值，暗通道
cv::Mat min_BGR(cv::Mat &src_img)
{
	int rows = src_img.rows;
	int cols = src_img.cols;

	cv::Mat res = cv::Mat::zeros(cv::Size(cols, rows), CV_8UC1);
	//creat one channel image to save min_rgb
	int channel_num = src_img.channels();
	/*std::cout << channel_num << std::endl;*/
	if (channel_num <= 1)
	{
		std::cout << "channel is just 1, return zeros matrix!" << std::endl;
		return res;
	}


	for (int i = 0; i < rows; i++)
	{
		uchar *img_adress = src_img.ptr<uchar>(i);   //当前行的地址
		uchar *res_adress = res.ptr<uchar>(i);       //当前行的地址
		for (int j_i = 0, j_r = 0; j_r < cols, j_i<cols*channel_num; j_i += channel_num, j_r++)
		{
			res_adress[j_r] = std::min(std::min(img_adress[j_i], img_adress[j_i + 1]), img_adress[j_i + 2]);
		}

	}
	//std::cout << "done!"<<std::endl;
	return res;
}

//cv::Mat  min_BRG_32F(cv::Mat &img_32F)
//{
//	int rows = img_32F.rows;
//	int cols = img_32F.cols;
//
//	Mat res = Mat::zeros(Size(cols,rows), CV_32FC1);
//	//cout << img_32F.size()<<endl;
//	//cout << res.size() << endl;
//
//	for (int i = 0; i < rows; i++)
//	{
//		for (int j = 0; j < cols; j++)
//		{
//	
//			res.at<float>(i, j) = std::min(img_32F.at<Vec2f>(i, j)[0], img_32F.at<Vec2f>(i, j)[1]);
//		}
//	}
//	return res;
//}

//获取通道的最大值，亮通道？
cv::Mat max_BGR(cv::Mat &src_img)
{
	int rows = src_img.rows;
	int cols = src_img.cols;

	cv::Mat res = cv::Mat::zeros(cv::Size(cols, rows), CV_8UC1);
	//creat one channel image to save min_rgb
	int channel_num = src_img.channels();
	/*std::cout << channel_num << std::endl;*/
	if (channel_num <= 1)
	{
		std::cout << "channel is just 1, return zeros matrix!" << std::endl;
		return res;
	}

	for (int i = 0; i < rows; i++)
	{
		uchar *img_adress = src_img.ptr<uchar>(i);   //当前行的地址
		uchar *res_adress = res.ptr<uchar>(i);       //当前行的地址
		for (int j_i = 0, j_r = 0; j_r < cols, j_i<cols*channel_num; j_i += channel_num, j_r++)
		{
			res_adress[j_r] = std::max(std::max(img_adress[j_i], img_adress[j_i + 1]), img_adress[j_i + 2]);
		}

	}
	//std::cout << "done!"<<std::endl;
	return res;
}

Mat getLx_A(Mat &M_min,Mat &img, float p,int kernel_size,float &A)
{
	Mat M_minfilter;

	blur(M_min, M_minfilter, Size(kernel_size, kernel_size));    //均值滤波
	Scalar m_av = cv::mean(M_min);              //暗通道的均值，这里应该是对的

	float m_ave = m_av[0]/255.0;                 //均值出来是一个Scalar,取第一个出来
	float m = std::min(m_ave*p, float(0.9));         //取两个数的最小值
	//cout << "m" <<m<< endl;             //这里没问题，测试过了
	//下面的计算牵扯到许多浮点运算，所以这里转换成32F来计算
	
	Mat M_minfilter_32f, M_min_32f;
	M_min.convertTo(M_min_32f, CV_32FC1);
	M_minfilter.convertTo(M_minfilter_32f, CV_32F);
	//改成32F才能去乘以上面0.9和p*m_av的最小值
	
	//cout <<"最小值滤波：" <<M_minfilter_32f(Range(0, 9), Range(0, 9));
	//cout << "最小值波：" << M_min_32f(Range(0, 9), Range(0, 9));
	//cout << M_minfilter_32f(Range(0, 9), Range(0, 9))*m;
	
	//vector<Mat> M_vector = { M_minfilter_32f*m,M_min_32f };

	////M_vector.push_back(M_minfilter_32f*m);
	////M_vector.push_back(M_min_32f);


	//Mat M_merge;
	//merge(M_vector, M_merge);
	//Mat res = min_BRG_32F(M_merge);     //专门来做浮点矩阵取最小值
	
	//因为只算一次，所以这里不用vector了，速度有一点点提升。
	M_minfilter_32f = M_minfilter_32f*m;

	int rows = M_minfilter_32f.rows;
	int cols = M_minfilter_32f.cols;
	Mat res = Mat::zeros(Size(cols,rows), CV_32FC1);
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{

			res.at<float>(i, j) = std::min(M_minfilter_32f.at<float>(i,j), M_min_32f.at<float>(i, j));
		}
	}

	Mat max_img = max_BGR(img);
	double max_max_img, max_ave_img;
	minMaxLoc(max_img, NULL, &max_max_img, NULL, NULL);
	minMaxLoc(M_minfilter, NULL, &max_ave_img, NULL, NULL);
	A = 0.5*(max_max_img + max_ave_img);
	return res;
}



//建立一个查找表，大小是255*255，用[0-255][0-255]来索引。
//查找方式为：  Table[(H[X]<<8)+L(X)]   左移是乘法
vector<vector<uchar>> Function7_table(const float &A)      
{
	vector<vector<uchar>> Table = vector<vector<uchar>>(256, vector<uchar>(256, 0));
	cout << Table.size() << endl;
	double Value=0;
	for (int Y = 0; Y < 256; Y++)
	{
		for (int X = 0; X < 256; X++)
		{
			Value = (Y - X) / (1 - X/A);       //function_7
			if (Value > 255)
				Value = 255;
			else if (Value < 0)
				Value = 0;
			
			Table[Y][X] = Value;
			//printf("%d\t", Table[Y][X]);  这是个大坑，cout输出uchar的时候是按照ascii码输出的
		}
	}
	return Table;
}

Mat FastDehaze(Mat &Img, const double p,const int kernel_size,float eps)
{
	Mat Lx, ImgDark;
	ImgDark = min_BGR(Img);
	Mat ImgDark_32f,Img_32F;
	//Img.convertTo(Img_32F, CV_32F);
	ImgDark.convertTo(ImgDark_32f, CV_32F);
	float A;
	Lx = getLx_A(ImgDark, Img, p, kernel_size, A);
	
	//cout <<"A:" <<A << endl;
	//cout << Lx(Range(0,9),Range(0,9)) << endl;

	vector<vector<uchar>> Table;
	Table = Function7_table(A);
	
	Mat ImgDefog = Img.clone();

	int row_Num = ImgDark_32f.rows;
	int col_Num = ImgDark_32f.cols;
	//获得行列
	for (int i = 0; i < row_Num; i++)
	{
		for (int j = 0; j < col_Num; j++)
		{
			ImgDefog.at<Vec3b>(i, j)[0] = Table[Img.at<Vec3b>(i, j)[0]][int(Lx.at<float>(i, j))];
			ImgDefog.at<Vec3b>(i, j)[1] = Table[Img.at<Vec3b>(i, j)[1]][int(Lx.at<float>(i, j))];
			ImgDefog.at<Vec3b>(i, j)[2] = Table[Img.at<Vec3b>(i, j)[2]][int(Lx.at<float>(i, j))];
			//处理三个通道
		}
	}
	return ImgDefog;

	//------------【用了查表来做下面的就先不要了】--------------------
	//vector<Mat> Img_split;
	//if (Img_32F.channels() != 3)
	//	cout << "必须是彩色图像" << endl;
	//else 
	//	split(Img_32F, Img_split);
	//
	//
	//

	//Mat fenmu = 1 - Lx / (A+eps);

	//vector<Mat> Fenzi;
	//Fenzi.push_back(Img_split[0] - Lx);
	//Fenzi.push_back(Img_split[1] - Lx);
	//Fenzi.push_back(Img_split[2] - Lx);

	//

	//vector<Mat> Img_split_dehaze;
	//Mat div_tmp;

	//for (int i = 0; i < 3; i++)
	//{
	//	/*cv::divide(Fenzi[i], fenmu, div_tmp);
	//	cout<<div_tmp;
	//	Img_split_dehaze.push_back(div_tmp);*/        
	//	
	//	//一开始是注释的这里错了，从最前面一点一点检查才发现，不过不知道哪里有问题，改成new对象就可以了，神奇！

	//	Mat *tmp = new Mat;
	//	cv::divide(Fenzi[i], fenmu, *tmp);
	//	Img_split_dehaze.push_back(*tmp);
	//	delete tmp;
	//}
	//
	//Mat res_32f, res;
	//merge(Img_split_dehaze, res_32f);
	//res_32f.convertTo(res, CV_8UC3);
	//-----------------------------------【以上】------------------------
	
}



