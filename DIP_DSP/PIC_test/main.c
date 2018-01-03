#include<stdio.h>
#include<math.h>
#include"ave_filter.h"


unsigned char *img=(unsigned char *)0x0850000;
unsigned char *img_smooth=(unsigned char *)0x0850000+10000;

int main(void) {

	Img_smooth(img,img_smooth,100,100);
	return 0;
}
