#ifndef BLINKING_H
#define BLINKING_H

#include "Includes.h"

#define blinkingthreshold 12
#define upperresize 20
#define lowerresize 10

class Blinking
{

public:
    Blinking(){}
    int Analyze(IplImage*, CvRect);
    static int FindUpperResize(CvRect);
    static int FindLowerResize(CvRect);

};

#endif // BLINKING_H
