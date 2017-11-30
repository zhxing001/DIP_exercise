#include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


int main()
{

	Mat image(600, 600, CV_8UC3);
	RNG &rng = theRNG();
	while (1) 
	{
		char key;
		int count = (unsigned)rng % 100 + 3;
		count = 55;
		
		vector<Point> points;

		for (int i = 0;i < count;i++)
		{
			Point point;
			point.x = rng.uniform(image.cols / 4, image.rows * 3 / 4);
			point.y = rng.uniform(image.cols / 4, image.rows * 3 / 4);
			points.push_back(point);
			//这个函数的作用是在POINTS后追加一个数据，也就是点集的点增加一个。
		}

			
			vector<int> hull;
			convexHull(Mat(points), hull, true);

			//绘制各个点
			image = Scalar::all(255);
			imshow("凸包", image);
			for (int i = 0;i < count;i++)
			{
				circle(image, points[i], 4, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED);

			}

			//绘制凸包的边，竟然是一个一个边绘制的，为毛不打包成一个函数。
			Point point0 = points[hull[(int)hull.size() - 1]];  //最后一个点。
			for (int i = 0;i < (int)hull.size();i++)
			{
				Point point = points[hull[i]];
				line(image, point0, point, Scalar(0, 0, 255), 3);
				point0 = point;
			}
			imshow("凸包", image);
			
			key = (char)waitKey();
			if (key = 'q' || key == 'Q')
				break;
			//这个break不能少，要不就会死循环，就看不到画出啦的凸包了。

		}
	waitKey();
	return 0;

	}
	