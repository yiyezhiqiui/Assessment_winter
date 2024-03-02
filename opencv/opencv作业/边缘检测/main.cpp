#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
int main(){
    cv::Mat edges;
	cv::Mat src = cv::imread("/home/yiyezhiqiu/桌面/homewor/opencv/边缘检测/1.jpg",0);
	cv::Canny(src, edges, 75, 80, 3, false);
	cv::imshow("边缘检测", edges);
	cv::waitKey(0);
    cv::imwrite("/home/yiyezhiqiu/桌面/homewor/opencv/边缘检测/result.jpg",edges);
    return 0;
}
