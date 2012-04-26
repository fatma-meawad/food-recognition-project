#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H

#include "Includes.h"

class Videocapture
{
private:
    CvCapture * capture;
    IplImage * GetFrame();

public:
    IplImage * CurrentFrame;
    Videocapture();
    ~Videocapture();
    int Init(int camMode);
    int UpdateFrame();
};

#endif // VIDEOCAPTURE_H
