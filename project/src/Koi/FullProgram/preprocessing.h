#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include "Includes.h"

class Facefeatures;

class Preprocessing
{
public:
    Preprocessing();

    static void MakeGrayscale(IplImage *);
    static IplImage * Crop(CvRect,IplImage*);

    static IplImage * Stabilize(Facefeatures*,IplImage*);
};

#endif // PREPROCESSING_H
