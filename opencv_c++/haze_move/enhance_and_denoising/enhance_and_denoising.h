//图像灰度线性拉伸算法表达式为：
//
//  Y(i,j)=(X(i,j)-Xmin)/Xmax-Xmin*Zmax 
//
//式中：i是图像数据行号；j是图像数据列号；Y(i，J)是拉伸后输出图像灰度值；X(i，j)是输入原始图像灰度值，
//为14 b二进制数；Xmin是输入图像数据的最小灰度值；Xmax是输入图像数据的最大灰度值；Zmax表明输出图像的最
//大灰度值，设计中拉伸后的图像灰度值用8 b二进制数表示，故Zmax = 255。
//
//首先对红外图像做灰度直方图统计，低信噪比条件下，选取压缩因子为5％，将盲元和噪声的影响降到最低。分别
//搜索5％最大灰度值中的最小值作为Xmax，5％最小灰度值里的最大值作为Xmin。拉伸转换时，将大于Xmax的像素灰
//度置为Zmax，小于Xmin的像素灰度置为O。此算法将线性拉伸区间自适应地分为[O，Xmin)，[Xmin，Xmax]和(Xmax，255]
//	三个部分。其中，[O，Xmin)和(Xmax，255]两个灰度区间的像素灰度分别被压缩为O和255。若图像中目标较小，且
//目标正好位于两个被压缩的区间内，就有可能被抑制。为避免这种情况发生，可视情况适当调整压缩因子5％的大小。
//这种方法效果一般感觉


#pragma once

#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>   //主要是调试用

void enhance(cv::Mat src_img, cv::Mat &out_img, double compress);

void enhance1(cv::Mat src_img, cv::Mat &out_img, double Gphi, double Iphi);
//Gphi调整对比度
//		>1				   增加对比度
//		0<Gphi<1		   较小对比度
//		<0                 明暗翻转

//Iphi  调整亮度      >0  增加亮度
//                    <0  较少亮度