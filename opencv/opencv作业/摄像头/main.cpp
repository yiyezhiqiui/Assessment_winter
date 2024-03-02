#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int width = 640;
int heigth = 480;
cv::VideoCapture cap;
int main()
{
	cap.open(0);
	cap.set(cv::CAP_PROP_FRAME_WIDTH, width); 
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, heigth); 
	cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
	cap.set(cv::CAP_PROP_FPS, 30);

	cv::Mat frame;
	cv::namedWindow("frame");
	while (1)
	{
		cap>>frame;
		if (frame.empty()) break;
		cv::imshow("frame", frame);
		if (27 == cv::waitKey(33))
			break;
	}
	cv::destroyWindow("frame");
	cap.release();
	return 0;
}
