#include "painting.h"
#include "boost/utility.hpp"

#define WindowName "Graph"

Painting* paint;

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
    drawRect(img, ff->mLeftEye);
    drawRect(img,ff->mRightEye);
    drawHairCross(img, ff->center(ff->mLeftEye));
    drawHairCross(img, ff->center(ff->mRightEye));

    return img;
}

// Draw circle from point
IplImage* Painting::drawCircle(IplImage * img, CvPoint p, int c, int t)
{
    if(c == 0)
        cvCircle(img,p, 3,cvScalar(0,0,255),t);
    else if(c == 1)
        cvCircle(img,p, 3,cvScalar(0,255,0),t);
    else
        cvCircle(img,p, 3,cvScalar(255,0,0),t);

    return img;
}

void Painting::update(int x, int y)
{
    if(x<100 && y<100 && mSelect>0){
        mSelect--;
        drawGraph();
    }
    else if(x>400 && y<100 && (unsigned)mSelect<mData.size()-1){
        mSelect++;
        drawGraph();
    }
}

// Mouse callback to capture button clicks and similar
void mouse( int event, int x, int y, int flags, void* param )
{

    switch( event ){

    case CV_EVENT_LBUTTONDOWN:
        paint->update(x,y);
        break;
    }
}

// Initialize window and variables
void Painting::drawInit(Painting* p)
{
    paint = p;

    // Create a window
    namedWindow(WindowName);
    cvSetMouseCallback(WindowName, mouse, NULL);
    cvMoveWindow(WindowName, 50, 50);
    IplImage* image = cvCreateImage(cvSize(500,500),IPL_DEPTH_8U,3);
    cvZero( image );
    cvRectangleR(image,cvRect(0,0,500,500),cvScalar(255,255,255), -1);
    cvResizeWindow(WindowName, 500, 500);

    mImage = image;
    mSelect = 0;

    mLeftButton = cvRect(10, 10, 100, 100);
    mRightButton = cvRect(490, 10, 100, 100);
}

// Graphs 2
void Painting::drawGraph()
{
    cvZero(mImage);
    cvRectangleR(mImage,cvRect(0,0,500,500),cvScalar(255,255,255), -1);

    CvFont font;
    double hScale=0.5;
    double vScale=0.5;
    int    lineWidth=1;
    cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);

    cvPutText (mImage,"Left",cvPoint(20,50), &font, cvScalar(200,0,0));
    cvPutText (mImage,"Right",cvPoint(420,50), &font, cvScalar(0,200,0));

    if(mData.size())
    {
        int xScale = 200;
        int yScale = 20;
        int xOffSet = 250 - mData[mSelect].timeStamp * xScale;
        int yOffSet1 = 240 + mData[mSelect].pulsefreq * yScale;
        int yOffSet2 = 250 + mData[mSelect].blinkingfreq * yScale;
        int yOffSet3 = 260 + mData[mSelect].breathingfreq * yScale;
        int t = 1; //thick

        if(mSelect == 0)
            t = -1;

        drawCircle(mImage,cvPoint(mData[0].timeStamp * xScale + xOffSet,yOffSet1 - mData[0].pulsefreq * yScale),0,t);
        drawCircle(mImage,cvPoint(mData[0].timeStamp * xScale + xOffSet,yOffSet2 - mData[0].blinkingfreq * yScale),0,t);
        drawCircle(mImage,cvPoint(mData[0].timeStamp * xScale + xOffSet,yOffSet3 - mData[0].breathingfreq * yScale),0,t);

        for(unsigned int i = 1; i<mData.size(); i++)
        {
            int thick = 1;
            if((unsigned)mSelect == i)
                thick = -1;
            // Pulse
            drawCircle(mImage,cvPoint(mData[i].timeStamp * xScale + xOffSet, yOffSet1 - mData[i].pulsefreq * yScale),0,thick);
            cvLine(mImage,cvPoint(mData[i].timeStamp * xScale + xOffSet, yOffSet1 - mData[i].pulsefreq * yScale),
                   cvPoint(mData[i-1].timeStamp * xScale + xOffSet, yOffSet1 - mData[i-1].pulsefreq * yScale),cvScalar(0,0,255));
            // Blinking
            drawCircle(mImage,cvPoint(mData[i].timeStamp * xScale + xOffSet, yOffSet2 - mData[i].blinkingfreq * yScale),1,thick);
            cvLine(mImage,cvPoint(mData[i].timeStamp * xScale + xOffSet, yOffSet2 - mData[i].blinkingfreq * yScale),
                   cvPoint(mData[i-1].timeStamp * xScale + xOffSet, yOffSet2 - mData[i-1].blinkingfreq * yScale),cvScalar(0,255,0));
            // Breathing
            drawCircle(mImage,cvPoint(mData[i].timeStamp * xScale + xOffSet, yOffSet3 - mData[i].breathingfreq * yScale),2,thick);
            cvLine(mImage,cvPoint(mData[i].timeStamp * xScale + xOffSet, yOffSet3 - mData[i].breathingfreq * yScale),
                   cvPoint(mData[i-1].timeStamp * xScale + xOffSet, yOffSet3 - mData[i-1].breathingfreq * yScale),cvScalar(255,0,0));
        }
    }

    cvShowImage(WindowName, mImage);

}


