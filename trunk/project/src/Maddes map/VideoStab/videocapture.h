#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H


#include "Includes.h"


class videocapture
{
private:
    CvCapture * capture;

    IplImage * GetFrame();


public:
    IplImage * CurrentFrame;

    videocapture();
    ~videocapture();
    int Init(int camMode);
    int UpdateFrame();

}VC;

#endif // VIDEOCAPTURE_H


