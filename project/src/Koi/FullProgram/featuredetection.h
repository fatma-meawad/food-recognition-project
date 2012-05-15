#ifndef FEATUREDETECTION_H
#define FEATUREDETECTION_H

#include "Includes.h"

class Facefeatures;

class Featuredetection
{
private:

    CvHaarClassifierCascade* cascade;
    CvHaarClassifierCascade* cascadeEye;
    CvMemStorage * storage;
    CvMemStorage * storage2;

public:
    Featuredetection();
    Facefeatures* detectfeatures(IplImage* img, Facefeatures* oldFace);                  //oldFace.face.x==-1 när oldface inte har någon info
    int detectface (IplImage* img, CvRect* face, CvRect* oldFace);
    CvSeq * GetFaces(IplImage* img, CvRect* oldFace);
};

#endif // FEATUREDETECTION_H
