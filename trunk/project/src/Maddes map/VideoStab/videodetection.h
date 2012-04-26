#ifndef VIDEODETECTION_H
#define VIDEODETECTION_H

#include "Includes.h"
#include "videocapture.h"

class videodetection
{
    videocapture VC;
    char** cascade_names;
    CvHaarClassifierCascade** cascades;
    int numCascades;
    CvMemStorage * storage;
    CvPoint pt1, pt2;
    CvSeq* FoundCascades;


public:

    IplImage * CurrentImage;

    videodetection();
    int Init(int);
    int InitFace();
    int InitEye();
    int UpdateFrame();
};

#endif // VIDEODETECTION_H
