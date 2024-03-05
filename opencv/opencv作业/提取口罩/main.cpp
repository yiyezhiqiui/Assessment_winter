#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string.h>

int main()
{
    cv::Mat src = cv::imread("/home/yiyezhiqiu/桌面/lht/opencv/提取口罩/src.jpg");
    cv::Mat dst, gray, copy;
    // 将图片缩小，并转成灰度图像
    cv::resize(src, src, cv::Size(302, 403), 0, 0, cv::INTER_LINEAR);
    src.copyTo(copy);
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // 开运算，边缘检测
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5), cv::Point(-1, -1));
    cv::morphologyEx(src, dst, cv::MORPH_OPEN, kernel);
    cv::threshold(gray, dst, 210, 255, cv::THRESH_BINARY);

    // 轮廓提取
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(dst, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, cv::Point());
    std::vector<cv::Point> contours_ploy;
    size_t i = 0, j = 0;
    for (; i < contours.size(); i++)
    {
        double area = cv::contourArea(contours[i]);
        std::cout << area << std::endl;
        if (area > 50)
        {
            cv::approxPolyDP(contours[i], contours_ploy, cv::arcLength(contours[i], true) * 0.02, true);
            break;
        }
    }

    // 凸包检测
    cv::convexHull(cv::Mat(contours[i]), contours_ploy, false);

    //透视变换
    cv::Point2f AffinePoints0[4] = {cv::Point2f(97,112), cv::Point2f(172,120), cv::Point2f(219,247), cv::Point2f(123,252) };
    cv::Point2f AffinePoints1[4] = {cv::Point2f(0,0), cv::Point2f(360,0),cv::Point2f(360,680),cv::Point2f(0,680) };
 
    cv::Mat Trans =cv::getPerspectiveTransform(AffinePoints0, AffinePoints1);
    cv::Mat dst_perspective;
    cv::warpPerspective(copy, dst_perspective, Trans,cv::Size(360,680));


    cv::imshow("result",dst_perspective);
    cv::imwrite("/home/yiyezhiqiu/桌面/lht/opencv/提取口罩/result.jpg",dst_perspective);
    cv::waitKey(0);
    return 0;
}