#include"FastDehaze.h"





int main()
{
	Mat img = imread("3.jpg");
	cout << img.size() << endl;
	namedWindow("source_img", 2);
	namedWindow("defog", 2);
	imshow("source_img", img);
	double start, end;
	int count = 5;
	while (count--)
	{
		start = static_cast<double>(getTickCount());
		auto mat = FastDehaze(img, 1.3, 15);
		cout << ((double)getTickCount() - start) / getTickFrequency() << endl;
		imshow("defog", mat);
		waitKey(100);
	}
	//imshow("defog", mat);
	
	//cout << arctan(1.2, 3.0) << endl;

	//auto p=Function7_table(242);
	waitKey();
	return 0;
}