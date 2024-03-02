#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string.h>

int main()
{
    cv::Mat src = cv::imread("/home/yiyezhiqiu/桌面/lht/opencv/提取口罩/src.jpg");
    cv::Mat dst, gray;

    // 将图片缩小，并转成灰度图像
    cv::resize(src, src, cv::Size(302, 403), 0, 0, cv::INTER_LINEAR);
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // 开运算，边缘检测
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3), cv::Point(-1, -1));
    cv::morphologyEx(src, dst, cv::MORPH_OPEN, kernel);
    cv::Canny(gray, dst, 80, 240);
    // 凸包检测，获得四个点位
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(dst, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_NONE, cv::Point());
    std::vector<std::vector<cv::Point>> contours_ploy(contours.size());
    size_t i = 0;
    cv::Mat matcontours = cv::Mat::zeros(dst.size(), dst.type());
    for (; i < contours.size(); i++)
    {
        if (contours[i].size() == 4)
        {
            cv::drawContours(matcontours, contours, i, cv::Scalar(190, 162, 25), 1, 8, hierarchy, 0, cv::Point());
            double area = cv::contourArea(contours[i]);
            std::cout << area << std::endl;
            if (area > 50)
            {
                cv::approxPolyDP(contours[i], contours_ploy[i], cv::arcLength(contours[i], true) * 0.2, true);
                break;
            }
        }
    }
    std::cout << contours.size();

    cv::imshow("轮廓", matcontours);
    cv::imshow("边缘检测", dst);
    cv::imshow("灰度图像", gray);
    cv::waitKey(0);
    return 0;
}