#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\core\core.hpp>
#include<iostream>
#include"template_match.hpp"

using namespace std;
using namespace cv;




VideoCapture video("C:\\Users\\zhxing\\OneDrive\\文档\\2018\\6_left.avi");

//获取帧数，宽和高
int num_frame = video.get(CV_CAP_PROP_FRAME_COUNT);
int width = video.get(CV_CAP_PROP_FRAME_WIDTH);
int height = video.get(CV_CAP_PROP_FRAME_HEIGHT);
//int type=video.get(CV_CAP_FRAME)

Point max_drift = Point(15, 10);       //最大偏移量
Rect template_ = Rect(85, 295, 80, 60);
Mat current_img;
Mat template_img;
Mat tem_img;
Point drift = Point(0, 0);


double start, time_cost,all_time_cost=0;

int main()
{
	for (int i = 0; i < num_frame; i++)
	{
		
		video.read(current_img);
		Mat display_img = Mat::zeros(Size(width + 100, height + 100), current_img.type());
		if (i == 0)
		{
			template_img = current_img(template_);
			cvtColor(template_img, tem_img, CV_BGR2GRAY);
			continue;
		}
		start = static_cast<double>(getTickCount());
		template_matching(current_img, tem_img, template_,drift);
		
		time_cost = ((double)getTickCount() - start) / getTickFrequency();
		all_time_cost += time_cost;

		

		current_img.copyTo(display_img(Rect(49 - drift.x, 49 - drift.y, width, height)));

		//rectangle(current_img, template_, Scalar(255, 0, 0));
		    //全部清零，下一张图片来了再说
		imshow("test", current_img);
		imshow("stabilization", display_img);
		display_img.setTo(Scalar(0, 0, 0));
		waitKey(10);
	}

	cout << "AVE_FPS:\t" << num_frame / all_time_cost << endl;
	
	waitKey();
	return 0;
}