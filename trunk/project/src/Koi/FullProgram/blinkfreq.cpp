#include "blinkfreq.h"

Blinkfreq::Blinkfreq()
{
    this->firstadded = false;
}

void Blinkfreq::AddState(int state)
{
    if(!this->firstadded)
    {
        gettimeofday(&this->StartTime,NULL);
        this->firstadded = true;

    }
    gettimeofday(&this->EndTime,NULL);

    if(this->EndTime.tv_sec - this->StartTime.tv_sec > 60)
    {
        this->eyestate.push_back(state);
        this->eyestate.erase(this->eyestate.begin());

        return;
    }

    this->eyestate.push_back(state);

    return;
}

double Blinkfreq::Analyze()
{
    std::vector<int>::iterator start = this->eyestate.begin();
    std::vector<int>::iterator next = this->eyestate.begin() + 1;
    std::vector<int>::iterator end = this->eyestate.end();
    int flanks = 0;


    while(next != end)
    {
        if(*start + *next == 1)
            flanks++;

        start++;
        next++;

    }

    if(this->EndTime.tv_sec - this->StartTime.tv_sec > 60)
        return double((1000*flanks)/120)/1000.0;
    else if(this->EndTime.tv_sec - this->StartTime.tv_sec == 0)
        return NAN;
    else
        return double((1000*flanks) / (2 * (this->EndTime.tv_sec - this->StartTime.tv_sec)))/1000.0;
}
