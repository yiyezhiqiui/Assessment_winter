#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
int main(){
    cv::Mat src=cv::imread("/home/yiyezhiqiu/桌面/homewor/opencv/图片进行腐蚀、膨胀/1.png");
    cv::Mat dst;
    cv::Mat kernel =cv::getStructuringElement(cv::MORPH_ELLIPSE,cv::Size(3, 3), cv::Point(-1, -1));
    cv::imshow("原图",src);
    //膨胀
    cv::dilate(src,dst,kernel);
    cv::imshow("膨胀",dst);


    //腐蚀
    cv::erode(src,dst,kernel);
    cv::imshow("腐蚀",dst);
    
    //开运算
    cv::morphologyEx(src,dst,cv::MORPH_OPEN, kernel);
    cv::imshow("开运算",dst);


    //闭运算
    cv::morphologyEx(src,dst,cv::MORPH_ELLIPSE, kernel);
    cv::imshow("闭运算",dst);
    cv::waitKey(0);
    return 0;
}
