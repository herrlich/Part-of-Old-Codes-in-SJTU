#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/video/background_segm.hpp"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iostream>

using namespace cv;
using namespace std;

const char* keys = 
{
	"{c |camera   |false    | use camera or not}"
	"{fn|file_name|camera_1.mp4 | movie file             }"
};

//this is a sample for foreground detection functions
int main(int argc, const char** argv)
{

	CommandLineParser parser(argc, argv, keys);
	bool useCamera = parser.get<bool>("camera");
	string file = parser.get<string>("file_name");
    VideoCapture cap;
    bool update_bg_model = true;
    if( useCamera )
        cap.open(0);
    else
		cap.open(file.c_str());
	parser.printParams();

    if( !cap.isOpened() )
    {
        printf("can not open camera or video file\n");
        return -1;
    }
    
    namedWindow("image", CV_WINDOW_NORMAL);
    namedWindow("foreground mask", CV_WINDOW_NORMAL);
    namedWindow("foreground image", CV_WINDOW_NORMAL);
    namedWindow("mean background image", CV_WINDOW_NORMAL);

    BackgroundSubtractorMOG2 bg_model;
    Mat img, fgmask, fgimg;

	char s[50];
	size_t frameNum = 0;

    for(;;)
    {
        cap >> img;

		//GaussianBlur(img, img, Size(3,3), 0, 0);
        
        if( img.empty() )
            break;
        
        if( fgimg.empty() )
          fgimg.create(img.size(), img.type());

        //update the model
        bg_model(img, fgmask, update_bg_model ? -1 : 0);

        fgimg = Scalar::all(0);
        img.copyTo(fgimg, fgmask);

        Mat bgimg;
        bg_model.getBackgroundImage(bgimg);

        imshow("image", img);
        imshow("foreground mask", fgmask);
        imshow("foreground image", fgimg);
		sprintf(s, "D:\\lab\\exp.jpg", frameNum++);
		imwrite(s, fgimg);
        if(!bgimg.empty())
          imshow("mean background image", bgimg );
		Mat newimg;
		FILE* f = 0;
		char _filename[1024];

		newimg = imread(s);

		if( newimg.data )
		{
			strcpy(_filename, s);
		}
		else
		{
			f = fopen(argv[1], "rt");
			if(!f)
			{
				fprintf( stderr, "ERROR: the specified file could not be loaded\n");
				return -1;
			}
		}

		HOGDescriptor hog;
		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
		namedWindow("people detector", 1);

		for(;;)
		{
			char* filename = _filename;
			if(f)
			{
				if(!fgets(filename, (int)sizeof(_filename)-2, f))
					break;
				//while(*filename && isspace(*filename))
				//	++filename;
				if(filename[0] == '#')
					continue;
				int l = strlen(filename);
				while(l > 0 && isspace(filename[l-1]))
					--l;
				filename[l] = '\0';
				newimg = imread(filename);
			}
			printf("%s:\n", filename);
			if(!newimg.data)
				continue;
		
			fflush(stdout);
			vector<Rect> found, found_filtered;
			double t = (double)getTickCount();
			// run the detector with default parameters. to get a higher hit-rate
			// (and more false alarms, respectively), decrease the hitThreshold and
			// groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
			hog.detectMultiScale(newimg, found, 0, Size(8,8), Size(32,32), 1.05, 2);
			t = (double)getTickCount() - t;
			printf("tdetection time = %gms\n", t*1000./cv::getTickFrequency());
			size_t i, j;
			for( i = 0; i < found.size(); i++ )
			{
				Rect r = found[i];
				for( j = 0; j < found.size(); j++ )
					if( j != i && (r & found[j]) == r)
						break;
				if( j == found.size() )
					found_filtered.push_back(r);
			}
			for( i = 0; i < found_filtered.size(); i++ )
			{
				Rect r = found_filtered[i];
				// the HOG detector returns slightly larger rectangles than the real objects.
				// so we slightly shrink the rectangles to get a nicer output.
				r.x += cvRound(r.width*0.1);
				r.width = cvRound(r.width*0.8);
				r.y += cvRound(r.height*0.07);
				r.height = cvRound(r.height*0.8);
				rectangle(newimg, r.tl(), r.br(), cv::Scalar(0,255,0), 3);
			}
			imshow("people detector", newimg);
			char save_path[50];
			string save_name;
			string name1 = "D:\\lab\\", name2 = ".jpg";
			char num[5];
			sprintf(num, "%d", frameNum - 1);
			save_name = name1 + num + name2;
			sprintf(save_path, save_name.c_str());
			if (frameNum != 1) imwrite(save_path, newimg);
			int c = waitKey(50) & 255;

			if( c == 'q' || c == 'Q' || !f)
				break;
		}
		if(f)
			fclose(f);
        char k = (char)waitKey(30);
        if( k == 27 ) break;

        if( k == ' ' )
        {
			printf("hello\n");
            update_bg_model = !update_bg_model;
            if(update_bg_model)
            	printf("Background update is on\n");
            else
            	printf("Background update is off\n");
        }
    }

	
    return 0;
}