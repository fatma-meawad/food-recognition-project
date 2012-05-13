#ifndef FUZZYMODEL_H
#define FUZZYMODEL_H

#include "Includes.h"

class Data;

class Fuzzymodel
{
    static float AnalyzeBlinking(Data * data);
    static float AnalyzeBreathing(Data *data);
    static float AnalyzePulse(Data *data);

    static float BlinkingLow(Data *data);
    static float BlinkingMed(Data *data);
    static float BlinkingHigh(Data *data);

    static float BreathingLow(Data *data);
    static float BreathingMed(Data *data);
    static float BreathingHigh(Data *data);

    static float PulseLow(Data *data);
    static float PulseMed(Data *data);
    static float PulseHigh(Data *data);

    static void NormalizeData(Data *data);
    static float NormalizeBreathing(Data *data);
    static float NormalizePulse(Data *data);
    static float NormalizeBlinking(Data *data);


public:
    Fuzzymodel();


    static float AnalyzeTired(Data *data);
    static float AnalyzeStressed(Data *data);


};


#endif // FUZZYMODEL_H
