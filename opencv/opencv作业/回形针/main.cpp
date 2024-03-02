#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
int main(){
	cv::Mat src = cv::imread("/home/yiyezhiqiu/桌面/homewor/opencv/回形针/1.png", 0);
    cv::Mat dst,dst_not,dst_sign,Matstate,center;
	cv::threshold(src, dst, 100, 255,cv::THRESH_OTSU);
	cv::bitwise_not(dst,dst_not);
    int sum=connectedComponentsWithStats(dst_not, dst_sign, Matstate, center, 8, CV_32S);
    std::cout<<sum-1<<::std::endl;
    cv::imshow("p1",center);
    cv::waitKey(0);
    return 0;
}
