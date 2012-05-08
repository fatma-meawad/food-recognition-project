#include "painting.h"
#include "boost/utility.hpp"

#define WindowName "Graph"

Painting::Painting()
{
}
// Draw haircross
IplImage* Painting::drawHairCross(IplImage* img, CvPoint p){
    cvLine(img,cvPoint(p.x-15,p.y),cvPoint(p.x+15,p.y),cvScalar(100,0,100), 1);
    cvLine(img,cvPoint(p.x,p.y-15),cvPoint(p.x,p.y+15),cvScalar(100,0,100), 1);

    return img;
}

// Draw rectangle
IplImage* Painting::drawRect(IplImage * img, CvRect rect){
    cvRectangleR(img,rect,cvScalar(255,0,0), 5);

    return img;
}

// Draw alla features
IplImage* Painting::drawFullFace(IplImage * img, Facefeatures * ff)
{
    drawRect(img, ff->mFace);
    drawHairCross(img, ff->center(ff->mLeftEye));
    drawHairCross(img, ff->center(ff->mRightEye));

    return img;
}

// Draw circle from point
IplImage* Painting::drawCircle(IplImage * img, CvPoint p, int c)
{
    if(c == 0)
    cvCircle(img,p, 3,cvScalar(0,0,255),1);
    else if(c == 1)
        cvCircle(img,p, 3,cvScalar(0,255,0),1);
    else
       cvCircle(img,p, 3,cvScalar(255,0,0),1);

    return img;
}

// Window init
void Painting::init(void)
{
    namedWindow(WindowName);
    cvMoveWindow(WindowName, 50, 50);
    CvMat image = cvMat(500, 500, CV_8SC3);
    //image = cvScalar(255,255,255);

    cvResizeWindow(WindowName, 500, 500);

    //cv::setMouseCallback("Graph", mouse);
}

// Graphs
void Painting::drawGraph(std::list<Data> ls)
{
    //init();

    // Create a window
    namedWindow(WindowName);
    cvMoveWindow(WindowName, 50, 50);
    IplImage* image = cvCreateImage(cvSize(500,500),IPL_DEPTH_8U,3);
    cvZero( image );
    cvRectangleR(image,cvRect(0,0,500,500),cvScalar(255,255,255), -1);
    cvResizeWindow(WindowName, 500, 500);


    // Iterate list and draw lines and stuff
    int offSet = 250;
    int xScale = 200;
    int yScale = 20;
    list<Data>::iterator it = ls.begin();
    drawCircle(image, cvPoint(it->timeStamp * xScale + offSet, offSet - it->pulsefreq * yScale),0);
    drawCircle(image, cvPoint(it->timeStamp * xScale + offSet, offSet - it->blinkingfreq * yScale),1);
    drawCircle(image, cvPoint(it->timeStamp * xScale + offSet, offSet - it->breathingfreq * yScale),2);

    for (it++; it != ls.end(); it++){
        drawCircle(image, cvPoint(it->timeStamp * xScale + offSet, offSet - it->pulsefreq * yScale),0);
        cvLine(image, cvPoint(it->timeStamp * xScale + offSet, offSet - it->pulsefreq * yScale),
        cvPoint(boost::prior(it)->timeStamp * xScale + offSet,offSet - boost::prior(it)->pulsefreq * yScale), cvScalar(0,0,255));

        drawCircle(image, cvPoint(it->timeStamp * xScale + offSet, offSet - it->blinkingfreq * yScale),1);
        cvLine(image, cvPoint(it->timeStamp * xScale + offSet, offSet - it->blinkingfreq * yScale),
        cvPoint(boost::prior(it)->timeStamp * xScale + offSet,offSet - boost::prior(it)->blinkingfreq * yScale), cvScalar(0,255,0));

        drawCircle(image, cvPoint(it->timeStamp * xScale + offSet, offSet - it->breathingfreq * yScale),2);
        cvLine(image, cvPoint(it->timeStamp * xScale + offSet, offSet - it->breathingfreq * yScale),
        cvPoint(boost::prior(it)->timeStamp * xScale + offSet,offSet - boost::prior(it)->breathingfreq * yScale), cvScalar(255,0,0));

    }

    cvShowImage(WindowName, image);
}


