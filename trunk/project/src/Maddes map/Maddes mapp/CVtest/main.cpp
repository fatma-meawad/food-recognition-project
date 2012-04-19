
#pragma once

#include <QtCore/QCoreApplication>
#include <opencv-2.3.1/opencv/cv.h>
#include <opencv-2.3.1/opencv/highgui.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    int h = 480;
    int w = 640;

    IplImage * image;
    CvFont text_font;

    image = cvCreateImage(cvSize(h,w),8,3);

    cvNamedWindow("HI",0);
    cvInitFont(&text_font,CV_FONT_HERSHEY_TRIPLEX,1,1,0,1,8);

    cvPutText(image,"Hello World",cvPoint(240,320),&text_font,CV_RGB(150,0,0));

    cvShowImage("HI",image);

    cvWaitKey();


    return 0;

}
