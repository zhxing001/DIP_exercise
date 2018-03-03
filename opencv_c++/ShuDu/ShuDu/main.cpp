//这个项目主要是来练手的，从读研以来接触图像处理也有一年半了，以前也用opencv，写的都是些小脚本。
//
//这个项目的主要功能在于对9*9的数独提供解，为什么之所以写这个是因为网上有一些参考资料，中间遇到的问题就只能慢慢解决了！
//2018/3/1


#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<string>
#include<vector>

using namespace cv;
using namespace std;

void getTrainImg(vector<vector<Mat>>  &TrainImgMat);

int main()
{
	//Mat srcImg;
	//Mat Img;
	//Mat Img_gray; 
	//Mat Img_g;
	//
	//srcImg = imread("2.jpg");
	//srcImg.copyTo(Img);
	//cvtColor(Img, Img_gray,COLOR_BGR2GRAY);
	//
	//Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	//filter2D(Img_gray, Img_g, -1, kernel);
	//threshold(Img_g, Img_g, 150, 255, THRESH_BINARY_INV);         //二值阈值化，这个阈值自己选,这里是反着的，因为一般是白纸黑字

	//imshow("阈值化", Img_g);

	//auto kernel_dilate = getStructuringElement(MORPH_CROSS, Size(3, 3));    //膨胀核
	//
	//dilate(Img_g, Img_g, kernel_dilate);           //膨胀，防止有断线
	//dilate(Img_g, Img_g, kernel_dilate);

	//vector<vector<Point>> contours;           
	//vector<Vec4i> hierarchy;
	//imshow("thres", Img_g);
	//findContours(Img_g,contours, hierarchy, RETR_TREE,CHAIN_APPROX_SIMPLE);     

	//cout <<"共检测到轮廓的个数\t"<<contours.size() << endl;

	///*for (auto h : hierarchy)
	//	cout << h << endl;*/

	//drawContours(Img, contours, -1, Scalar(0, 0, 255), 1);
	//

	////vector<vector<Point>>  rec_contours;
	////for (int i = 0; i < hierarchy.size(); i++)
	////{
	////	if (hierarchy[i][3] == 0)     //父轮廓是0号轮廓的话，就是小矩形
	////	{
	////		rec_contours.push_back(contours[i]);	
	////	}
	////}

	//vector<vector<Point>> num_contours;
	//vector<Rect>  RecOfNum;
	//Rect tmp;
	//vector<pair<Point, Rect>>  IndexAndPos;
	//auto Round = boundingRect(contours[0]);     //外边缘

	///*cout << "宽度\t" << Round.width << endl;
	//cout << "高度\t" << Round.height << endl;*/

	//rectangle(Img, Round, Scalar(255, 0, 255));
	//namedWindow("co", 2);
	//imshow("co", Img);

	//int index_x;
	//int index_y;
	//Point index_xy;
	//Mat ImgROI;

	//for (int i = 0; i < hierarchy.size(); i++)
	//{
	//	if (hierarchy[i][3] == 0&&hierarchy[i][2]!=-1)    
	//	//父轮廓是0号轮廓的话，就是小矩形，存在子轮廓，则子轮廓是数字
	//	{
	//		
	//		num_contours.push_back(contours[hierarchy[i][2]]);
	//		tmp = boundingRect(contours[hierarchy[i][2]]);
	//		
	//		//每个数字的质心,转换为坐标，具体方法是一种算比例的方法，还不知道凑效不
	//		index_x = double((tmp.x + tmp.width / 2))/Round.width*9;
	//		index_y = double((tmp.y + tmp.height / 2)) / Round.height * 9;
	//		index_xy.x = index_x;
	//		index_xy.y = index_y;
	//		cout << index_x << "--" << index_y << endl;

	//		IndexAndPos.push_back(make_pair(index_xy, tmp));    //坐标和对应的矩形
	//		
	//		resize(srcImg(tmp), ImgROI, Size(20, 20));
	//		
	//		//imwrite("C:\\Users\\zhxing\\Desktop\\DIP_exercise\\opencv_c++\\ShuDu\\ShuDu\\img\\"+to_string(index_xy.x) + "_"+to_string(index_xy.y)+".jpg", ImgROI);
	//		//测试用，这里确实可以得到位置对应的图像

	//		rectangle(srcImg, tmp, Scalar(255, 255, 0));
	//		RecOfNum.push_back(tmp);
	//	}
	//}

	//


	////namedWindow("co", 2);
	//imshow("co", srcImg);

	//cout << "检测到的数字的数目是：\t" << num_contours.size() << endl;
	
	
	vector<vector<Mat>>  TrainImgMat(10,vector<Mat>());
	getTrainImg(TrainImgMat);
	

	Mat TrainImg=Mat::zeros(Size(200,200), TrainImgMat[0][0].type());
	Mat img20x20;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			resize(TrainImgMat[i][j], img20x20, Size(20, 20));
			img20x20.copyTo(TrainImg(Rect(i*20,j*20,20,20)));
		}
	}
	imshow("test", TrainImg);

	waitKey();
	
	return 0;
}



//把文件夹中的图像，逐一提取为可用的数据格式
void getTrainImg(vector<vector<Mat>>  &TrainImgMat)
{
	Mat tmp_srcImg;
	Mat tmp_Img_thresh;
	vector<vector<Point>> cons;
	vector<Vec4i>  hies;

	vector<Rect>  img0_9;
	for (int i = 0; i < 10; i++)
	{
		//读入，阈值化
		tmp_srcImg = imread(".\\TrainImg\\" + to_string(i) + ".jpg");
		cvtColor(tmp_srcImg, tmp_Img_thresh, CV_BGR2GRAY);
		threshold(tmp_Img_thresh, tmp_Img_thresh, 150, 255, CV_THRESH_BINARY_INV);
		//3*3十字膨胀
		auto kernel=getStructuringElement(CV_SHAPE_CROSS, Size(3, 3));
		dilate(tmp_Img_thresh, tmp_Img_thresh, kernel);
		//查找轮廓
		findContours(tmp_Img_thresh, cons, hies, RETR_TREE, CHAIN_APPROX_SIMPLE);
		
		//筛选没有父轮廓的轮廓为数字，并求其最小包围矩形
		for (int j = 0; j < hies.size(); j++)
		{
			if (hies[j][3] == -1)
			{
				img0_9.push_back(boundingRect(cons[j]));
			}
		}
		cons.clear();
		hies.clear();

		//排序，按照矩形包围圈的x坐标排序
		sort(img0_9.begin(), img0_9.end(), [](Rect &a, Rect &b)->bool {return a.x < b.x; });     
		
		for (int k = 0; k < img0_9.size(); k++)
		{
			TrainImgMat[i].push_back(tmp_srcImg(img0_9[k]));	
		}
		//清除内存空间，下次用
		cons.clear();
		hies.clear();
		img0_9.clear();	
	}
}