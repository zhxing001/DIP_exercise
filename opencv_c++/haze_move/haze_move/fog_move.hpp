#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<algorithm>

void min_filter(cv::Mat &src_img, cv::Mat &res_img, int kernel_size);

cv::Mat min_BGR(cv::Mat &src_img);
