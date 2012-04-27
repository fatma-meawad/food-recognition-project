#ifndef FEATUREDETECTION_H
#define FEATUREDETECTION_H

#include "Includes.h"

class Facefeatures;

class Featuredetection
{
private:
    bool lock;

public:
    Featuredetection();
    Facefeatures detectfeatures(IplImage* img);
    int detectface (IplImage* img, CvRect* face);
    int detectEye (IplImage* img,CvPoint roi, CvRect* eyes);
};

#endif // FEATUREDETECTION_H
