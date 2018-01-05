/*
 * algor.h
 *
 *  Created on: 2018-1-5
 *      Author: zhxing
 *      一些要用到的算法。
 */

#ifndef ALGOR_H_
#define ALGOR_H_

//-------------【1】找最大响应值及其索引---------------------------------
struct max_index{
	float max_num;
	int max_index;
};

struct max_index  max(float *p,int nums)   //一遍遍历，找出最大值得索引
{
	int i=0;

	float max=0;
	int index=0;

	struct max_index  max_response;

	for(i=0;i<nums;i++)
	{
		if(p[i]>max)
		{
			max=p[i];       //真正要运行CSK算法的时候可以不要这个幅值，因为我们只需要找到索引就行
			index=i;
		}
	}
	max_response.max_num=max;
	max_response.max_index=index;

	return max_response;
}
//-------------【1】找最大响应值及其索引---------------------------------


//-------------【2】float->uchar---------------------------------
void floar2uchar(float *f,unsigned char *u,int nums)
{
	int i=0;
	for(i=0;i<nums;i++)
	{
		u[i]=f[i];   //直接赋值就可以
	}
}
//-------------【2】float->uchar---------------------------------



#endif /* ALGOR_H_ */
