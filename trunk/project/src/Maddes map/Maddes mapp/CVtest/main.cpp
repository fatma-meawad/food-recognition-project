
#pragma once

#include <QtCore/QCoreApplication>
#include <opencv-2.3.1/opencv/cv.h>
#include <opencv-2.3.1/opencv/highgui.h>
#include <opencv-2.3.1/opencv2/imgproc/imgproc_c.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
using namespace cv;

IplImage* GetImage(char* filename)
{
    IplImage * image = 0;

    image = cvLoadImage( filename , CV_LOAD_IMAGE_COLOR);

    return image;
}

IplImage* GetImageGray(char* filename)
{
    IplImage * image = 0;

    image = cvLoadImage( filename , CV_LOAD_IMAGE_GRAYSCALE);

    return image;
}

IplImage * SmoothImage(IplImage * image, int iterations)
{
    IplImage * returnImage = new IplImage(*image);
    for(int i = 0; i < iterations; i++)
    {
        cvSmooth(returnImage, returnImage, CV_GAUSSIAN, 5, 5 );

    }

    return returnImage;
}

IplImage * HoughCircleDetect(IplImage * image, int iterations)
{
    IplImage * returnImage = 0;
    CvMemStorage* storage = cvCreateMemStorage(0);
    float* seqelement;

    returnImage = new IplImage(*image);

    returnImage = SmoothImage(returnImage,iterations);


    CvSeq* results = cvHoughCircles(
                returnImage,
                storage,
                CV_HOUGH_GRADIENT,
                4,
                returnImage->width/10
                );

    for(int i = 0; i < results->total; i++)
    {
        seqelement = (float*)cvGetSeqElem(results,i);
        CvPoint point = cvPoint(cvRound(seqelement[0]),cvRound(seqelement[1]));
        cvCircle(returnImage,point,cvRound(seqelement[2]),CV_RGB(0xff,0,0) );
    }

    return returnImage;
}



IplImage * AddTextToImage(IplImage * image, char * text, int Font_Face)
{
    CvFont text_font;
    IplImage * returnImage = new IplImage(*image);

    cvInitFont(&text_font,Font_Face,1,1,0,1,8);

    cvPutText(returnImage,text,cvPoint(240,320),&text_font,CV_RGB(150,0,0));

    return returnImage;
}

IplImage * HoughLineDetect(IplImage * image, int iterations)
{
    IplImage * returnImage = 0;
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvPoint* line;

    returnImage = new IplImage(*image);

    cvSmooth(returnImage,returnImage,CV_GAUSSIAN,9,9);

    CvSeq* results = cvHoughLines2(
                returnImage,
                storage,
                CV_HOUGH_PROBABILISTIC,1,CV_PI/180,50,100,50);

    for(int i = 0; i < results->total; i++)
    {
        line = (CvPoint*)cvGetSeqElem(results,i);
        cvLine(returnImage,line[0],line[1],CV_RGB(0xff,0,0),2 );
    }

    return returnImage;
}



int main(int argc, char *argv[])
{
    int h = 480;
    int w = 640;
    int smoothiterations;
    const char* windowname;


    IplImage * image = 0;
    IplImage * inputimage = 0;
    IplImage* images[20];
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvPoint* line;





    //    if(argc < 2)
    //        inputimage = cvCreateImage(cvSize(h,w),8,3);
    //    else
    inputimage = GetImage(argv[1]);


    image = cvCreateImage(cvSize(inputimage->width,inputimage->height),IPL_DEPTH_8U,1);




    cvCvtColor(inputimage,image,CV_RGB2GRAY);


    cvCanny(image,image,100,150,3);

    cvSmooth(image,image,CV_GAUSSIAN,9,9);

 //   cvCvtColor(image,image,CV_GRAY2RGB);


    CvSeq* results = cvHoughLines2(
                image,
                storage,
                CV_HOUGH_PROBABILISTIC,1,CV_PI/180,50,100,50);

    for(int i = 0; i < results->total; i++)
    {
        line = (CvPoint*)cvGetSeqElem(results,i);
        cvLine(inputimage,line[0],line[1],CV_RGB(0xff,0,0),2 );
    }



    //    cout << "Smoothing iterations: ";
    //    cin >> smoothiterations;

    //    for(int i = 0; i < smoothiterations; i++)
    //    {
    //        images[i] = new IplImage(*HoughLineDetect(image,i));
    //    }


    //    for(int i = 0; i < smoothiterations; i++)
    //    {
    //        images[i] = AddTextToImage(images[i],"HEJ HEJ HEJ",CV_FONT_HERSHEY_TRIPLEX);
    //    }


    //   for(int i = 0; i < smoothiterations; i++)
    //  {
    windowname = "window";
    cvNamedWindow(windowname,0);
    cvShowImage(windowname,inputimage);
    // }


    cvWaitKey();


    return 0;

}


