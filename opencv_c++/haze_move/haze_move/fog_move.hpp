#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<algorithm>
#include<vector>

//最小值滤波，用腐蚀来做的
void min_filter(cv::Mat &src_img, cv::Mat &res_img, int kernel_size);

//BGR通道的最小值
cv::Mat min_BGR(cv::Mat &src_img);

//我自己写的导向滤波
cv::Mat guide_filter(cv::Mat &img, cv::Mat p, int r, double eps);


//下面这个是两个导向滤波的函数，opencv contrib里的，有快速版本，我没有下载库是在网上找的：
//https://blog.csdn.net/wds555/article/details/23176313

cv::Mat GuidedFilter(cv::Mat I, cv::Mat p, int r, double eps);
cv::Mat fastGuidedFilter(cv::Mat I_org, cv::Mat p_org, int r, double eps, int s);

//计算大气遮罩图像V1和光照值A及A的位置。
void getV1(cv::Mat &m, int r, double eps, double w, double maxV1,double &A,cv::Point &A_loc, cv::Mat &V1_);

//最终的去雾函数，输入原始图像，返回去雾之后的图像
cv::Mat deHaze(cv::Mat &img, bool Gamma = false, double r = 42, double eps = 0.001, double w = 0.99, double maxV1 = 0.80);

//自使用对比度增强
void enhance(cv::Mat src, cv::Mat &out_img, double compress);