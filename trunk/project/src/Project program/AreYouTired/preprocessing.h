#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include "Includes.h"

class Preprocessing
{
public:
    Preprocessing();
    IplImage * MakeGrayscale(IplImage *);
    IplImage * Crop(CvRect, IplImage *);


};

#endif // PREPROCESSING_H
