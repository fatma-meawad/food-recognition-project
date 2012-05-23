#ifndef BLINKFREQ_H
#define BLINKFREQ_H

#include "Includes.h"

class blinkfreq
{
    vector<int> eyestate;
    bool firstadded;

    timeval StartTime,EndTime;

public:
    blinkfreq();
    void AddState(int);
    int Analyze();
};

#endif // BLINKFREQ_H
