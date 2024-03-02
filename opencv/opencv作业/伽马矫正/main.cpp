#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
 
using namespace cv;
using namespace std;
 
int main() {
    cv::Mat image = imread("/home/yiyezhiqiu/桌面/homewor/opencv/伽马矫正/2.jpeg");
    double gamma = 1/2.2;
    cv::Mat gamma_image = Mat::zeros(image.size(), image.type());
 
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            for (int c = 0; c<3; c++) {
                double pixel_value = image.at<Vec3b>(i,j)[c] / 255.0;
                double corrected_value = pow(pixel_value, gamma) * 255.0;
                gamma_image.at<Vec3b>(i,j)[c] =cv::saturate_cast<uchar>(corrected_value);
            }
        }
    }
 
    cv::imshow("原始图像", image);
    cv::imshow("伽马校正后的图像", gamma_image);
    cv::imwrite("/home/yiyezhiqiu/桌面/homewor/opencv/伽马矫正/result/1.jpeg",gamma_image);
    cv::waitKey(0);
 
    return 0;
}