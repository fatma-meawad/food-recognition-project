#ifndef FEATUREDETECTION_H
#define FEATUREDETECTION_H

#include "Includes.h"

class Facefeatures;

class Featuredetection
{
public:
    Featuredetection();
    Facefeatures detectfeatures(IplImage* img);
};

#endif // FEATUREDETECTION_H
