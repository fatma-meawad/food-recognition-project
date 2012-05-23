#ifndef BREATHING_H
#define BREATHING_H

#include "Includes.h"
class Facefeatures;
class Breathing
{
private:
    int list[200];
    int avg;
    int pos;
    int prev;
public:
    Breathing();
    int getdistance(IplImage* img, Facefeatures* face);
    int isBreathing(IplImage* img, Facefeatures* face);
};

#endif // BREATHING_H
