#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include "Includes.h"

#define Tolerance 20

class Preprocessing
{
    CvPoint CurrentP;
    CvRect CurrentCrop;

public:
    Preprocessing();

    static IplImage * MakeGrayscale(IplImage *);
    static IplImage * Crop(CvRect,IplImage*);

    IplImage * Stabilize(IplImage*,Facefeatures *);
    static float Pointdistance(CvPoint p1, CvPoint p2);

};

#endif // PREPROCESSING_H
