#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
void inrange(cv::Mat&image);
int main(){
    cv::Mat src=cv::imread("/home/yiyezhiqiu/桌面/homewor/opencv/二值化/1.png");
    cv::imshow("原图",src);
    inrange(src);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
void inrange(cv::Mat&image){
    cv::cvtColor(image,image,cv::COLOR_BGR2HSV);
    for(int i=0;i<image.rows;i++)  
    {  
        for(int j=0;j<image.cols;j++)  
        {  
            if(image.at<cv::Vec3b>(i,j)[0]>=100&&image.at<cv::Vec3b>(i,j)[0]<=124&&image.at<cv::Vec3b>(i,j)[1]>=43&&image.at<cv::Vec3b>(i,j)[1]<=255&&image.at<cv::Vec3b>(i,j)[2]>=46&&image.at<cv::Vec3b>(i,j)[2]<=255){
                image.at<cv::Vec3b>(i,j)[0]=0;
                image.at<cv::Vec3b>(i,j)[1]=0;
                image.at<cv::Vec3b>(i,j)[2]=0;
            }
            else{
                image.at<cv::Vec3b>(i,j)[0]=255;
                image.at<cv::Vec3b>(i,j)[1]=255;
                image.at<cv::Vec3b>(i,j)[2]=255;
            }
        }
    }
    cv::imshow("二值化",image);
    cv::imwrite("/home/yiyezhiqiu/桌面/homewor/opencv/二值化/1.png",image);
}