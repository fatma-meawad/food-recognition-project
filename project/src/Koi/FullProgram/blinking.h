#ifndef BLINKING_H
#define BLINKING_H

#include "Includes.h"

#define blinkingthreshold 12
#define upperresize 20
#define lowerresize 10

class Blinking
{



public:
    Blinking();
    int Init();
    int Analyze(IplImage*, CvRect, CvRect);
    static int Findupperresize(CvRect);
    static int Findlowerresize(CvRect);

};

#endif // BLINKING_H
