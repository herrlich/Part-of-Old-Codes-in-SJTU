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
	char directory1[MAX_PATH] = "D:\\VIPeR\\cam_a";
	result1 = EnumFiles(directory1, &count1);
	char directory2[MAX_PATH] = "D:\\VIPeR\\cam_b";
	result2 = EnumFiles(directory2, &count2);
	double *relativity = new double[count2];
	double *ordered_relativity = new double[count2];
 //储存基准图像和另外两张对比图像的矩阵( RGB 和 HSV )
	Mat src_base, hsv_base;
	Mat src_test1, hsv_test1;
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
	
	/// 装载三张背景环境不同的图
	for (i = 0; i < 5; ++i) {
		path1 = "D:\\VIPeR\\cam_a\\" + (string)result1[i+2];
		src_base = imread(path1);
		for (j = 0; j < 25; ++j) {
			path2 = "D:\\VIPeR\\cam_b\\" + string(result2[j+2]);
			src_test1 = imread(path2);

			/// 转换到 HSV
			cvtColor(src_base, hsv_base, CV_BGR2HSV );
			cvtColor(src_test1, hsv_test1, CV_BGR2HSV );
			/// 计算基准HSV图像的二维直方图
			calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
			normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );
			//测试图像1的二维直方图
			calcHist( &hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false );
			normalize( hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat() );

			///按顺序使用4种对比标准将基准图像(hist_base)的直方图与其余各直方图进行对比
			double base_test1 = compareHist( hist_base, hist_test1, CV_COMP_CORREL);
			relativity[j] = base_test1;
			ordered_relativity[j] = base_test1;
		}
		qsort(ordered_relativity, count2, sizeof(ordered_relativity[0]), cmp);
		cout << "图片" << result1[i+2] << "对应的是" << endl;
		for (int t = 0; t < 5; ++t) {
			for (int k = 0; k < count2 - 2; ++k) {
				if (fabs(relativity[k] - ordered_relativity[t]) < 1E-10) cout << result2[k+2] << endl;
			}
		}
	}
	delete [] relativity;
	delete [] ordered_relativity;
	return 0;
}