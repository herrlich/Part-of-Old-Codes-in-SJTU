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

	// ��ʼ����
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

	// ���ҽ���
	FindClose(hFind);

	// ���Ƶ������
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
 //�����׼ͼ����������ŶԱ�ͼ��ľ���( RGB �� HSV )
	Mat src_base, hsv_base;
	Mat src_test1, hsv_test1;
	Mat hsv_half_down;
	Mat hsv_half_up;
	Mat hsvbase_half_down;
	Mat hsvbase_half_up;
	/// ��hueͨ��ʹ��50��bin,��saturatoinͨ��ʹ��60��bin
	int h_bins = 50; int s_bins = 60;
	int histSize[] = { h_bins, s_bins };
	
	// hue��ȡֵ��Χ��0��256, saturationȡֵ��Χ��0��180
	float h_ranges[] = { 0, 256 };
	float s_ranges[] = { 0, 180 };
	const float* ranges[] = { h_ranges, s_ranges };

	// ʹ�õ�0�͵�1ͨ��
	int channels[] = { 0, 1 };

	/// ֱ��ͼ���󣬶�ά
	MatND hist_base;
	MatND hist_test1;
	MatND hist_half_down;
	MatND hist_half_up;
	MatND histbase_half_down;
	MatND histbase_half_up;
	
	/// װ�����ű���������ͬ��ͼ
	for (i = 0; i < 5; ++i) {
		path1 = "D:\\VIPeR\\111\\" + (string)result1[i+2];
		src_base = imread(path1);
		for (j = 0; j < count2 - 2; ++j) {
			path2 = "D:\\VIPeR\\222\\" + string(result2[j+2]);
			src_test1 = imread(path2);

			/// ת���� HSV
			cvtColor(src_base, hsv_base, CV_BGR2HSV );
			cvtColor(src_test1, hsv_test1, CV_BGR2HSV );
			hsv_half_down = hsv_test1( Range( hsv_test1.rows/2, hsv_test1.rows - 1 ), Range( 0, hsv_test1.cols - 1 ) );
			hsv_half_up = hsv_test1( Range( 0, hsv_test1.rows/2 - 1 ), Range( 0, hsv_test1.cols - 1 ) );
			hsvbase_half_down = hsv_base( Range( hsv_base.rows/2, hsv_base.rows - 1 ), Range( 0, hsv_base.cols - 1 ) );
			hsvbase_half_up = hsv_base( Range( 0, hsv_base.rows/2 - 1 ), Range( 0, hsv_base.cols - 1 ) );

			//�����׼ͼ��Ķ�άֱ��ͼ
			calcHist( &hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges, true, false );
			normalize( hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat() );
			calcHist( &hsv_half_up, 1, channels, Mat(), hist_half_up, 2, histSize, ranges, true, false );
			normalize( hist_half_up, hist_half_up, 0, 1, NORM_MINMAX, -1, Mat() );
			calcHist( &hsvbase_half_down, 1, channels, Mat(), histbase_half_down, 2, histSize, ranges, true, false );
			normalize( histbase_half_down, histbase_half_down, 0, 1, NORM_MINMAX, -1, Mat() );
			calcHist( &hsvbase_half_up, 1, channels, Mat(), histbase_half_up, 2, histSize, ranges, true, false );
			normalize( histbase_half_up, histbase_half_up, 0, 1, NORM_MINMAX, -1, Mat() );

			///��˳��ʹ��4�ֶԱȱ�׼����׼ͼ��(hist_base)��ֱ��ͼ�������ֱ��ͼ���жԱ�
			double base_half = compareHist( histbase_half_down, hist_half_down, CV_COMP_CORREL);
			double base_half2 = compareHist( histbase_half_up, hist_half_up, CV_COMP_CORREL);
			half_relativity[j] = base_half+base_half2;
			half_ordered_relativity[j] = base_half+base_half2;
		}
		qsort(half_ordered_relativity, count2, sizeof(half_ordered_relativity[0]), cmp);
		cout << "ͼƬ" << result1[i+2] << "��Ӧ����" << endl;
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