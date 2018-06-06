#include"fog_move.hpp"


//最小值滤波，实际上就是一个腐蚀的过程，直接借助opencv的腐蚀函数来做
void min_filter(cv::Mat &src_img, cv::Mat &res_img, int kernel_size)
{
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernel_size, kernel_size));
	cv::erode(src_img, res_img, element);
}

//获取通道的最小值，好像只能自己遍历做了
cv::Mat min_BGR(cv::Mat &src_img)
{
	int rows = src_img.rows;
	int cols = src_img.cols;
	cv::Mat res = cv::Mat::zeros(cv::Size(cols, rows), CV_8UC1);
	//creat one channel image to save min_rgb
	int channel_num = src_img.channels();
	std::cout << channel_num << std::endl;
	if (channel_num <= 1)
	{
		std::cout << "channel is just 1, return zeros matrix!" << std::endl;
		return res;
	}
	
	for (int i = 0; i < rows; i++)
	{
		uchar *img_adress = src_img.ptr<uchar>(i);   //当前行的地址
		uchar *res_adress = res.ptr<uchar>(i);       //当前行的地址
		for (int j_i = 0,j_r=0; j_r < cols,j_i<cols*channel_num; j_i+=3,j_r++)
		{
			res_adress[j_r] =std::min(std::min(img_adress[j_i],img_adress[j_i+1]),img_adress[j_i+2]);
		}
		
	}
	std::cout << "done!";
	return res;

}
