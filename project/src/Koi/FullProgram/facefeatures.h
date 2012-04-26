#ifndef FACEFEATURES_H
#define FACEFEATURES_H

#include "Includes.h"

class Facefeatures
{

public:

    CvRect mFace;
    CvRect mLeftEye;
    CvRect mRightEye;
    CvRect mNose;
    CvRect mMouth;

    CvPoint center(CvRect rect);
};

#endif // FACEFEATURES_H

