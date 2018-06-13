#pragma once
#include<opencv2\opencv.hpp>

using namespace cv;

void template_matching(Mat frame, Mat &model, Rect &template_, Point &drift);