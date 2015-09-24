#undef UNICODE
#define MAX_RESULT 1000

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <cstring>

using namespace std;
using namespace cv;

char** EnumFiles(const char *directory, int *count)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	char result[MAX_RESULT][MAX_PATH];
	char **returnresult;
	char pattern[MAX_PATH];
	int i = 0, j;

	// 开始查找
	strcpy(pattern, directory);
	strcat(pattern, "\\*.*");
	hFind = FindFirstFile(pattern, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE) 
	{
		*count = 0;
		return NULL;
	} 
	else 
	{
		do
		{
			strcpy(result[i++], FindFileData.cFileName);
		}
		while (FindNextFile(hFind, &FindFileData) != 0);
	}

	// 查找结束
	FindClose(hFind);

	// 复制到结果中
	returnresult = (char **)calloc(i, sizeof(char *));

	for (j = 0; j < i; j++)
	{
		returnresult[j] = (char *)calloc(MAX_PATH, sizeof(char));
		strcpy(returnresult[j], result[j]);
	}

	*count = i;
	return returnresult;
}

int cmp(const void * a,const void * b)
{
return((*(double*)b-*(double*)a>0)?1:-1);
}

int main( int argc, char** argv )
{
	int i, j, count1, count2;
	string path1, path2;
	char ** result1, ** result2;
	char directory1[MAX_PATH] = "D:\\VIPeR\\111";
	result1 = EnumFiles(directory1, &count1);
	char directory2[MAX_PATH] = "D:\\VIPeR\\222";
	result2 = EnumFiles(directory2, &count2);
	double *half_relativity = new double[count2];
	double *half_ordered_relativity = new double[count2];
 //储存基准图像和另外两张对比图像的矩阵( RGB 和 HSV )
	Mat src_base, hsv_base;
	Mat src_test1, hsv_test1;
	Mat hsv_half_down;
	Mat hsv_half_up;
	Mat hsvbase_half_down;
	Mat hsvbase_half_up;
	/// 对hue通道使用50个bin,对saturatoin通道使用60个bin
	int h_bins = 50; int s_bins = 60;
	int histSize[] = { h_bins, s_bins };
	
	// hue的取值范围从0到256, saturation取值范围从0到180
	float h_ranges[] = { 0, 256 };
	float s_ranges[] = { 0, 180 };
	const float* ranges[] = { h_ranges, s_ranges };

	// 使用第0和第1通道
	int channels[] = { 0, 1 };

	/// 直方图矩阵，二维
	MatND hist_base;
	MatND hist_test1;
	MatND hist_half_down;
	MatND hist_half_up;
	MatND histbase_half_down;
	MatND histbase_half_up;
	
	/// 装载三张背景环境不同的图
	for (i = 0; i < 5; ++i) {
		path1 = "D:\\VIPeR\\111\\" + (string)result1[i+2];
		src_base = imread(path1);
		for (j = 0; j < count2 - 2; ++j) {
			path2 = "D:\\VIPeR\\222\\" + string(result2[j+2]);
			src_test1 = imread(path2);

			/// 转换到 HSV
			cvtColor(src_base, hsv_base, CV_BGR2HSV );
			cvtColor(src_test1, hsv_test1, CV_BGR2HSV );
			hsv_half_down = hsv_test1( Range( hsv_test1.rows/2, hsv_test1.rows - 1 ), Range( 0, hsv_test1.cols - 1 ) );
			hsv_half_up = hsv_test1( Range( 0, hsv_test1.rows/2 - 1 ), Range( 0, hsv_test1.cols - 1 ) );
			hsvbase_half_down = hsv_base( Range( hsv_base.rows/2, hsv_base.rows - 1 ), Range( 0, hsv_base.cols - 1 ) );
			hsvbase_half_up = hsv_base( Range( 0, hsv_base.rows/2 - 1 ), Range( 0, hsv_base.cols - 1 ) );

			//半身基准图像的二维直方图
			calcHist( &hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges, true, false );
			normalize( hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat() );
			calcHist( &hsv_half_up, 1, channels, Mat(), hist_half_up, 2, histSize, ranges, true, false );
			normalize( hist_half_up, hist_half_up, 0, 1, NORM_MINMAX, -1, Mat() );
			calcHist( &hsvbase_half_down, 1, channels, Mat(), histbase_half_down, 2, histSize, ranges, true, false );
			normalize( histbase_half_down, histbase_half_down, 0, 1, NORM_MINMAX, -1, Mat() );
			calcHist( &hsvbase_half_up, 1, channels, Mat(), histbase_half_up, 2, histSize, ranges, true, false );
			normalize( histbase_half_up, histbase_half_up, 0, 1, NORM_MINMAX, -1, Mat() );

			///按顺序使用4种对比标准将基准图像(hist_base)的直方图与其余各直方图进行对比
			double base_half = compareHist( histbase_half_down, hist_half_down, CV_COMP_CORREL);
			double base_half2 = compareHist( histbase_half_up, hist_half_up, CV_COMP_CORREL);
			half_relativity[j] = base_half+base_half2;
			half_ordered_relativity[j] = base_half+base_half2;
		}
		qsort(half_ordered_relativity, count2, sizeof(half_ordered_relativity[0]), cmp);
		cout << "图片" << result1[i+2] << "对应的是" << endl;
		for (int t = 0; t < 5; ++t) {
			for (int k = 0; k < count2 - 2; ++k) {
				if (fabs(half_relativity[k] - half_ordered_relativity[t]) < 1E-10){
					cout << result2[k+2] << endl;
				}
			}
		}
	}
	delete [] half_relativity;
	delete [] half_ordered_relativity;
	return 0;
}