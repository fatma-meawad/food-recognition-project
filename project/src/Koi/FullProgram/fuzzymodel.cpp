#include "fuzzymodel.h"


//Pulse definitions
#define pulselowlimit 60
#define pulsemedlowlimit 65
#define pulseaverage 72
#define pulsemedhighlimit 80
#define pulsehighlimit 100

//Breathing definitions
#define breathinglowlimit 8
#define breathingmedlowlimit 12
#define breathingaverage 234
#define breathingmedhighlimit 15
#define breathinghighlimit 20

//Blinking definitions
#define blinkinglowlimit 6
#define blinkingmidlowlimit 8
#define blinkingavrage 10
#define blinkingmidhighlimit 25
#define blinkinghighlimit 30

//Blinkingspeed definitions
#define blinkingspeedlow 10
#define blinkingspeedmidlow 30
#define blinkingspeedaverage 123
#define blinkingspeedmedhigh 298
#define blinkingspeedhigh 400


#define subjectage 20
#define maxbreathingrate 120

Fuzzymodel::Fuzzymodel()
{
}

float Fuzzymodel::AnalyzeTired(Data *data)
{
    int breathing,pulse,blinking;

    Fuzzymodel::NormalizeData(data);

    breathing = Fuzzymodel::AnalyzeBreathing(data);
    pulse = Fuzzymodel::AnalyzePulse(data);
    blinking = Fuzzymodel::AnalyzeBlinking(data);

    return std::min(breathing,std::min(pulse,blinking));
}

float Fuzzymodel::AnalyzeStressed(Data *data)
{
    int breathing,pulse,blinking;

    Fuzzymodel::NormalizeData(data);

    breathing = Fuzzymodel::AnalyzeBreathing(data);
    pulse = Fuzzymodel::AnalyzePulse(data);
    blinking = Fuzzymodel::AnalyzeBlinking(data);

    return std::min(breathing,std::min(pulse,blinking));
}


//Analyzing different features, returns either high medium or low
float Fuzzymodel::AnalyzePulse(Data *data)
{
    float low,med,high;

    high = Fuzzymodel::PulseHigh(data);
    med = Fuzzymodel::PulseMed(data);
    low = Fuzzymodel::PulseLow(data);

    if(low > med && low > high)
        return 1;
    if(med > low && med > high)
        return 2;
    if(high > med && high > low)
        return 3;

    return -1;
}


float Fuzzymodel::AnalyzeBlinking(Data *data)
{
    float low,med,high;

    high = Fuzzymodel::BlinkingHigh(data);
    med = Fuzzymodel::BlinkingMed(data);
    low = Fuzzymodel::BlinkingLow(data);

    if(low > med && low > high)
        return 1;
    if(med > low && med > high)
        return 2;
    if(high > med && high > low)
        return 3;

    return -1;
}

float Fuzzymodel::AnalyzeBreathing(Data *data)
{
    float low,med,high;

    high = Fuzzymodel::BreathingHigh(data);
    med = Fuzzymodel::BreathingMed(data);
    low = Fuzzymodel::BreathingLow(data);

    if(low > med && low > high)
        return 1;
    if(med > low && med > high)
        return 2;
    if(high > med && high > low)
        return 3;

    return -1;
}
//Analyzing different features, returns either high medium or low

//Fuzzy graph for blinking
float Fuzzymodel::BlinkingLow(Data *data)
{
    float k = (-1)/(blinkingmidlowlimit - blinkinglowlimit);

    if(data->blinkingfreq < blinkinglowlimit)
        return 1;

    return std::max((float)0,(float)k*(data->blinkingfreq - blinkinglowlimit) + 1);

}

float Fuzzymodel::BlinkingMed(Data *data)
{
    float krising = 1/(blinkingmidlowlimit - blinkinglowlimit);
    float kfalling = (-1)/(blinkinghighlimit - blinkingmidhighlimit);

    if(data->blinkingfreq < blinkingmidhighlimit && data->blinkingfreq > blinkingmidlowlimit)
        return 1;

    if(data->blinkingfreq < blinkingmidlowlimit)
        return std::max((float)0,(float)krising*(data->blinkingfreq - blinkinglowlimit));

    if(data->blinkingfreq > blinkingmidhighlimit)
        return std::max((float)0,(float)kfalling*(data->blinkingfreq - blinkingmidhighlimit) + 1);

    return -1;

}

float Fuzzymodel::BlinkingHigh(Data *data)
{
    float k = 1 / (blinkinghighlimit - blinkingmidhighlimit);

    if(data->blinkingfreq > blinkinghighlimit)
        return 1;

    return std::max((float)0,(float)k*data->blinkingfreq - blinkingmidhighlimit);
}
//Fuzzy graph for blinking



//Fuzzy graph for breathing
float Fuzzymodel::BreathingLow(Data *data)
{
    float k = (-1) / (breathingmedlowlimit - breathinglowlimit);

    if(data->breathingfreq < breathinglowlimit)
        return 1;

    return std::max((float)0,(float)k*(data->breathingfreq - blinkinglowlimit));
}

float Fuzzymodel::BreathingMed(Data *data)
{
    float krising = 1/(breathingmedlowlimit - breathinglowlimit);
    float kfalling = (-1)/(breathinghighlimit - breathingmedhighlimit);

    if(data->breathingfreq < blinkingmidhighlimit && data->breathingfreq > blinkingmidlowlimit)
        return 1;

    if(data->breathingfreq < breathingmedlowlimit)
        return std::max((float)0,(float)krising*(data->breathingfreq - breathinglowlimit));

    if(data->breathingfreq > breathingmedhighlimit)
        return std::max((float)0,(float)kfalling*(data->breathingfreq - breathingmedhighlimit) + 1);

    return -1;
}

float Fuzzymodel::BreathingHigh(Data *data)
{
    float k = 1 / (breathinghighlimit - breathingmedhighlimit);

    if(data->breathingfreq > breathinghighlimit)
        return 1;

    return std::max((float)0,(float)k*(data->breathingfreq - breathinghighlimit));
}
//Fuzzy graph for breating


//Fuzzy graph for pulse
float Fuzzymodel::PulseLow(Data *data)
{
    float k = (-1)/(pulsemedlowlimit - pulselowlimit);

    if(data->pulsefreq < pulselowlimit)
        return 1;

    return std::max((float)0,(float)k*(data->breathingfreq - pulselowlimit) + 1);
}

float Fuzzymodel::PulseMed(Data * data)
{
    float krising = 1/(pulsemedlowlimit - pulselowlimit);
    float kfalling = (-1)/(pulsehighlimit - pulsemedhighlimit);

    if(data->pulsefreq < pulsemedhighlimit && data->pulsefreq > pulsemedlowlimit)
        return 1;

    if(data->pulsefreq < pulsemedlowlimit)
        return std::max((float)0,(float)krising*(data->breathingfreq - pulselowlimit) + 1);

    if(data->pulsefreq > pulsemedhighlimit)
        return std::max((float)0,(float)kfalling*(data->pulsefreq - pulsemedhighlimit) + 1);

    return -1;
}

float Fuzzymodel::PulseHigh(Data * data)
{
    float k = 1 / (pulsehighlimit - pulsemedhighlimit);

    if(data->pulsefreq > pulsehighlimit)
        return 1;

    return std::max((float)0,(float)k*data->pulsefreq - breathingmedhighlimit);
}
//Fuzzy graph for pulse




//Normalization, not needed atm
void Fuzzymodel::NormalizeData(Data * data)
{
   data->blinkingfreq = Fuzzymodel::NormalizeBlinking(data);
   data->breathingfreq = Fuzzymodel::NormalizeBreathing(data);
   data->pulsefreq = Fuzzymodel::NormalizePulse(data);
}

float Fuzzymodel::NormalizeBreathing(Data * data)
{
    return data->breathingfreq / maxbreathingrate;
}

float Fuzzymodel::NormalizePulse(Data * data)
{
    return data->pulsefreq / (206 - (0.71 * subjectage));
}

float Fuzzymodel::NormalizeBlinking(Data * data)
{
    return 1;
}
//Normalization, not needed atm

