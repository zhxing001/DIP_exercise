#include"FastDehaze.h"





int main()
{
	Mat img = imread("1.jpg");
	//imshow("source_img", img);
	double start, end;
	int count = 5;
	while (count--)
	{
		start = static_cast<double>(getTickCount());
		auto mat = FastDehaze(img, 1.3, 15);
		cout << ((double)getTickCount() - start) / getTickFrequency() << endl;
	}
	//imshow("defog", mat);
	waitKey();
	//cout << arctan(1.2, 3.0) << endl;

	return 0;
}