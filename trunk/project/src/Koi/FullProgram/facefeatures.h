#ifndef FACEFEATURES_H
#define FACEFEATURES_H

#include "Includes.h"

class Facefeatures
{
    CvRect mFace;
    CvRect mLeftEye;
    CvRect mRightEye;
    CvRect mNose;
    CvRect mMouth;

public:

    CvPoint center(CvRect rect);
};

#endif // FACEFEATURES_H

