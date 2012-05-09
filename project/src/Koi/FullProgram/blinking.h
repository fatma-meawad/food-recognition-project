#ifndef BLINKING_H
#define BLINKING_H

#include "Includes.h"

#define blinkingthreshold 12

class Blinking
{



public:
    Blinking();
    int Init();
    int Analyze(IplImage*, CvRect, CvRect);

};

#endif // BLINKING_H
