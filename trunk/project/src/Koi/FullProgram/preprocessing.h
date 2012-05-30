#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include "Includes.h"

#define Tolerance 20

class Videocapture;

class Preprocessing
{
    CvPoint CurrentP;
    CvRect CurrentCrop;

public:
    Preprocessing();

    static IplImage * MakeGrayscale(IplImage *);
    static IplImage * MakeThreshold(IplImage *, int);
    static IplImage * MakeHSV(IplImage *);
    static IplImage * Crop(CvRect,IplImage*);
    static IplImage * MakeDiffImage(Videocapture VC);

    IplImage * Stabilize(IplImage*,Facefeatures *);
    static float Pointdistance(CvPoint p1, CvPoint p2);

};

#endif // PREPROCESSING_H
