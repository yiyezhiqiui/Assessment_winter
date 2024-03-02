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
    cv::Mat m=cv::Mat::zeros(image.size(),image.type());
    for(int i=0;i<image.rows;i++){
        uchar *pimage=image.ptr<uchar>(i);
        uchar *pm=m.ptr<uchar>(i);
        for(int j=0;j<image.cols*3;j+=3){
            if(pimage[j]>=100&&pimage[j]<=124&&pimage[j+1]>=43&&pimage[j+1]<=255&&pimage[j+2]>=46&&pimage[j+2]<=255){
                pm[j]=0;
                pm[j+1]=0;
                pm[j+2]=0;
            }
            else{
                pm[j]=255;
                pm[j+1]=255;
                pm[j+2]=255;
            }
        }
    }
    cv::imshow("二值化",m);
    cv::imwrite("/home/yiyezhiqiu/桌面/homewor/opencv/二值化/1.png",m);
}