#ifndef PULSE_H
#define PULSE_H

#include "Includes.h"

class Facefeatures;

class Pulse
{
public:
    Pulse();
    int pulseValue(IplImage* img, Facefeatures* face);
};

#endif // PULSE_H


