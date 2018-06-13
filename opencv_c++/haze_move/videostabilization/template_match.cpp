#include"template_match.hpp"




//模板匹配，drift是计算漂移量
void template_matching(Mat frame, Mat &model, Rect &template_,Point &drift) 
{
	Mat gray;
	cvtColor(frame, gray, CV_BGR2GRAY);


	Rect searchWindow;
	searchWindow.width = template_.width * 3;
	searchWindow.height = template_.height * 3;
	searchWindow.x = template_.x + template_.width * 0.5 - searchWindow.width * 0.5;
	searchWindow.y = template_.y + template_.height * 0.5 - searchWindow.height * 0.5;
	searchWindow &= Rect(0, 0, gray.cols, gray.rows);
	//这是取交集，防止搜索范围出界

	Mat similarity;
	matchTemplate(gray(searchWindow), model, similarity, CV_TM_CCOEFF_NORMED);

	double mag_r;
	Point point;
	minMaxLoc(similarity, 0, &mag_r, 0, &point);
	drift.x=point.x + searchWindow.x- template_.x;
	drift.y=point.y + searchWindow.y - template_.y;
	

	//template_.x = point.x + searchWindow.x;
	//template_.y = point.y + searchWindow.y;
}