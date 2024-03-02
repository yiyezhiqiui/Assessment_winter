#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
int main(){
	cv::Mat src = cv::imread("/home/yiyezhiqiu/桌面/homewor/opencv/边缘检测/1.jpg");
    cv::Mat hsv;
    cv::cvtColor(src,hsv,cv::COLOR_RGB2HSV);
    cv::imshow("原图",src);
    cv::imshow("hsv",hsv);



    std::vector<cv::Mat>mv1,mv2,mv3;
    cv::split(hsv,mv1);
    cv::split(hsv,mv2);
    cv::split(hsv,mv3);
    cv::Mat blue,red,green;

    mv1[1]=0;
    mv1[2]=0;
    cv::merge(mv1,blue);
    cv::imshow("蓝色",blue);

    mv2[0]=0;
    mv2[2]=0;
    cv::merge(mv2,green);
    cv::imshow("绿色",green);

    mv3[0]=0;
    mv3[1]=0;
    cv::merge(mv3,red);
    cv::imshow("红色",red);
    cv::waitKey(0);

    cv::imwrite("/home/yiyezhiqiu/桌面/homewor/opencv/RGB转HSV/result/hsv.jpg",hsv);
    cv::imwrite("/home/yiyezhiqiu/桌面/homewor/opencv/RGB转HSV/result/蓝色.jpg",blue);
    cv::imwrite("/home/yiyezhiqiu/桌面/homewor/opencv/RGB转HSV/result/绿色.jpg",green);
    cv::imwrite("/home/yiyezhiqiu/桌面/homewor/opencv/RGB转HSV/result/红色.jpg",red);
    return 0;
}
