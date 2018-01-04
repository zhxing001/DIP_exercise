#include<stdio.h>
#include<math.h>
#include"ave_filter.h"
#include"windows.h"

unsigned char *img=(unsigned char *)0x0850000;
unsigned char *img_smooth;
float  *img_with_window;
int main(void) {
	add_coswindow(img,cos_window_64_64,img_with_window,4096);
	int i=0;
	for(i=0;i<4096;i++)
	{
		*img_smooth++=(unsigned char)(*img_with_window++);
	}

	//Img_smooth(img,img_smooth,64,64);
	return 0;
}
