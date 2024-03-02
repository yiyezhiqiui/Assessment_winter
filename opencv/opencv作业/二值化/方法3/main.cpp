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
    cv::MatConstIterator_<cv::Vec3b> it_in=image.begin<cv::Vec3b>();  
    cv::MatConstIterator_<cv::Vec3b> itend_in=image.end<cv::Vec3b>();  
    cv::MatIterator_<cv::Vec3b> it_out=m.begin<cv::Vec3b>();  
    cv::MatIterator_<cv::Vec3b> itend_out=m.end<cv::Vec3b>(); 
    while(it_in!=itend_in)  
    {
        if((*it_in)[0]>=100&&(*it_in)[0]<=124&&(*it_in)[1]>=43&&(*it_in)[1]<=255&&(*it_in)[2]>=46&&(*it_in)[2]<=255){
            (*it_out)[0]=0;
            (*it_out)[1]=0;
            (*it_out)[2]=0;
        }
        else{
            (*it_out)[0]=255;
            (*it_out)[1]=255;
            (*it_out)[2]=255;
        }
        it_in++;  
        it_out++;  
    }  
    cv::imshow("二值化",m);
    cv::imwrite("/home/yiyezhiqiu/桌面/homewor/opencv/二值化/1.png",m);
}