#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<algorithm>
#include<vector>
//最小值滤波，用腐蚀来做的
void min_filter(cv::Mat &src_img, cv::Mat &res_img, int kernel_size);

//BGR通道的最小值
cv::Mat min_BGR(cv::Mat &src_img);

//导向滤波
cv::Mat guide_filter(cv::Mat &img, cv::Mat &p, int r, double eps);

//计算大气遮罩图像V1和光照值
void getV1(cv::Mat &m, int r, double eps, double w, double maxV1);