#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include "Includes.h"

class Preprocessing
{
public:
    Preprocessing();

    static void MakeGrayscale(IplImage *);
    static IplImage * Crop(CvRect,IplImage*);

    static IplImage * Stabilize(IplImage*,Facefeatures *);

};

#endif // PREPROCESSING_H
