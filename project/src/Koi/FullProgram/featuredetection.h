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
    Facefeatures* detectfeatures(IplImage* img, Facefeatures* old_face);                  //old_face.face.x==-1 när oldface inte har någon info
    int detectface (IplImage* img, CvRect* face, CvRect* old_face);                      //face.x==-1 -||-
    int detectEye (IplImage* img,CvPoint roi, CvRect* eyes, Facefeatures* old_face);
};

#endif // FEATUREDETECTION_H
