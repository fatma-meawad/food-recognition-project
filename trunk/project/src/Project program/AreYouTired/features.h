#ifndef FEATURES_H
#define FEATURES_H

#include "Includes.h"

class Features
{
    CvRect mFace;
    CvRect mLeftEye;
    CvRect mRightEye; //Possible nose, mouth etc

public:
    Features();
};

#endif // FEATURES_H

