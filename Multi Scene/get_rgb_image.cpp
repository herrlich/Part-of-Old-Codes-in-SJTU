#include "highgui.h"  //恩，这个程序生成的rgb图像中，越往右边表示亮度越大。
#include "cv.h"  
#include "cxcore.h"  
#include <iostream>  
  
//#include <math.h>   
  
using namespace std;  
  
void main(int argc,char** argv)  
{  
    IplImage *src = cvLoadImage("012.jpg",1);  
      
    //IplImage *hsv= cvCreateImage(cvGetSize(src),8,3);  
    //cvCvtColor(src,hsv,CV_RGB2HSV);  
  
    IplImage* r_plane = cvCreateImage(cvGetSize(src),8,1);  
    IplImage* g_plane = cvCreateImage(cvGetSize(src),8,1);  
    IplImage* b_plane = cvCreateImage(cvGetSize(src),8,1);  
    //IplImage* planes[] = {h_plane,s_plane};  
    cvCvtPixToPlane(src,b_plane,g_plane,r_plane,0);//openCV里面的一个函数,可以看作cvSplit是他的宏:#define cvCvtPixToPlane cvSplit   
                                                   //注意顺序为BGR,OpenCV中不管是Windows中Load的还是摄像头取得的都是BGR顺序排列的  
  
    //计算直方图  
    //int h_bins = 100,s_bins = 32;  
    int hist_size = 100;  
    int hist_height = 100;  
    float range[] = {0,255};  
    float* ranges[] = {range};  
    CvHistogram* r_hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);  
    CvHistogram* g_hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);  
    CvHistogram* b_hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);  
  
    cvCalcHist(&r_plane,r_hist,0,0);  
    cvNormalizeHist(r_hist,1.0);  
    cvCalcHist(&g_plane,g_hist,0,0);  
    cvNormalizeHist(g_hist,1.0);  
    cvCalcHist(&b_plane,b_hist,0,0);  
    cvNormalizeHist(b_hist,1.0);  
  
    //创建图像绘制直方图  
    int scale = 2;  
    IplImage* hist_img = cvCreateImage(cvSize(hist_size*scale,hist_height*3),8,3);  
    cvZero(hist_img);  
  
    //绘制矩形表示直方图  
    float max_valr = 0,max_valg = 0,max_valb = 0;  
    cvGetMinMaxHistValue(r_hist,0,&max_valr,0,0);  
    cvGetMinMaxHistValue(g_hist,0,&max_valg,0,0);  
    cvGetMinMaxHistValue(b_hist,0,&max_valb,0,0);  
  
    for(int i = 0;i<hist_size;i++)  
    {  
        float bin_val = cvQueryHistValue_1D(r_hist,i);  
        int intensity = cvRound(bin_val*hist_height/max_valr);  //int cvRound (double value)对一个double型的数进行四舍五入，并返回一个整型数！  
        cvRectangle(hist_img,cvPoint(i*scale,hist_height),cvPoint((i+1)*scale-1,hist_height-intensity),CV_RGB(255,0,0));  
    }  
    for(int i = 0;i<hist_size;i++)  
    {  
        float bin_val = cvQueryHistValue_1D(g_hist,i);  
        int intensity = cvRound(bin_val*hist_height/max_valg);  //int cvRound (double value)对一个double型的数进行四舍五入，并返回一个整型数！  
        cvRectangle(hist_img,cvPoint(i*scale,2*hist_height),cvPoint((i+1)*scale-1,2*hist_height-intensity),CV_RGB(0,255,0));  
    }  
    for(int i = 0;i<hist_size;i++)  
    {  
        float bin_val = cvQueryHistValue_1D(b_hist,i);  
        int intensity = cvRound(bin_val*hist_height/max_valb);  //int cvRound (double value)对一个double型的数进行四舍五入，并返回一个整型数！  
        cvRectangle(hist_img,cvPoint(i*scale,3*hist_height),cvPoint((i+1)*scale-1,3*hist_height-intensity),CV_RGB(0,0,255));  
    }  
  
    cvNamedWindow("histogram",1);  
    cvShowImage("histogram",hist_img);  
  
    cvNamedWindow("src",1);  
    cvShowImage("src",src);  
    //cvNamedWindow("hsv",1);  
    //cvShowImage("hsv",hsv);  
      
    cvWaitKey(0);  
  
        cvDestroyWindow("src");  
    cvReleaseImage(&src);  
        cvDestroyWindow("r_plane");  
    cvReleaseImage(&r_plane);  
        cvDestroyWindow("g_plane");  
    cvReleaseImage(&r_plane);  
        cvDestroyWindow("g_plane");  
    cvReleaseImage(&b_plane);  
        cvDestroyWindow("b_plane");  
    cvReleaseImage(&src);  
        cvDestroyWindow("histogram");
	cvReleaseImage(&hist_img);
}
