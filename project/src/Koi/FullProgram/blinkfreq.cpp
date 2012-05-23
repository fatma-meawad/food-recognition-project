#include "blinkfreq.h"

blinkfreq::blinkfreq()
{
    this->firstadded = false;
}

void blinkfreq::AddState(int state)
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

int blinkfreq::Analyze()
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
        return flanks/120;

    return flanks / (this->EndTime.tv_sec - this->StartTime.tv_sec);

    return -1;
}
