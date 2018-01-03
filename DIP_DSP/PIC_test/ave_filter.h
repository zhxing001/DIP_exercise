/*
 * mid_filter.h
 *
 *  Created on: 2018-1-3
 *      Author: zhxing
 */

#ifndef AVE_FILTER_H_
#define AVE_FILTER_H_
int coefArray[9]={1,1,1,1,1,1,1,1,1};

void Img_smooth(unsigned char *F,
		unsigned char *G,
		int cols,int rows)
{
	unsigned char *ptr,*pp,*newpp;  //局部变量
	int tmpNum,x,y;
	//-----------处理边界，这里均等于原值
	for(x=0;x<cols;x++)
	{
		G[x]=F[x];      // 第一行不处理，等于原值
	}
	newpp=G+(rows-1)*cols;   //这个是输出最后一行首地址
	pp=F+(rows-1)*cols;      //这也是输入图像最后一行首地址
	for(x=0;x<cols;x++)    //最后一行也等于原值
	  *newpp++=*pp++;

	newpp=G;
	pp=F;   //准备处理左边一列
	for(y=0;y<rows;y++)
	{
		*newpp=*pp;
		newpp+=cols;
		pp+=cols;
		//赋值以后移动到下一行
	}
	newpp=G+cols;
	pp=F+cols;  //准备处理右边一列
	for(y=0;y<rows;y++)
	{
		*newpp=*pp;
		newpp+=cols;
		pp+=cols;
	}
	//-------------处理边界----------------------

	for(y=1;y<rows-1;y++)
		for(x=1;x<cols-1;x++)
		{
			newpp=G+y*cols+x;
			pp=F+y*cols+x;
			//第一排三个元素
			ptr=pp-cols-1;  //左上角
			tmpNum+=(*ptr++)*coefArray[0];
			tmpNum+=(*ptr++)*coefArray[1];
			tmpNum+=(*ptr)*coefArray[2];
			//第二排三个元素
			ptr=pp-1;
			tmpNum+=(*ptr++)*coefArray[3];
			tmpNum+=(*ptr++)*coefArray[4];
			tmpNum+=(*ptr)*coefArray[5];
			//第三排三个元素
			ptr=pp+cols-1;
			tmpNum+=(*ptr++)*coefArray[6];
			tmpNum+=(*ptr++)*coefArray[7];
			tmpNum+=(*ptr)*coefArray[8];

			tmpNum/=9;
			if(tmpNum>255)  //溢出检查
			{
				*newpp=255;
			}
			else
				*newpp=tmpNum;
		}

}




#endif /* AVE_FILTER_H_ */
