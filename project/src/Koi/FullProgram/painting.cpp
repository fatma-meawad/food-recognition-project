#include "painting.h"

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
IplImage* Painting::drawCircle(IplImage * img, CvPoint p)
{
    cvCircle(img,p, 2,cvScalar(0,0,255),-1);

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


    // Iterate list
    for (list<Data>::iterator it = ls.begin(); it != ls.end(); it++){
        std::cout << it->pulsefreq << std::endl;
        drawCircle(image, cvPoint(it->timeStamp * 50 + 250, 250 - it->pulsefreq * 10));
    }

    cvShowImage(WindowName, image);
}


