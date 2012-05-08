#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H

#include "Includes.h"

class Videocapture
{
private:
    CvCapture * capture;
    IplImage * GetFrame();
    int fps;
    bool AVI;

public:
    IplImage * CurrentFrame;
    Videocapture();
    ~Videocapture();
    int Init(int camMode);
    int InitAVI(char *);
    int UpdateFrame();
};

#endif // VIDEOCAPTURE_H
