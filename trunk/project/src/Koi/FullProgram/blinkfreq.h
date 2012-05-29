#ifndef BLINKFREQ_H
#define BLINKFREQ_H

#include "Includes.h"

class Blinkfreq
{
    std::vector<int> eyestate;
    bool firstadded;

    timeval StartTime,EndTime;

public:
    Blinkfreq();
    void AddState(int);
    double Analyze();
};

#endif // BLINKFREQ_H
