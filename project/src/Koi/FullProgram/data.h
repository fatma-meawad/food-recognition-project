#ifndef DATA_H
#define DATA_H

#include "Includes.h"

/**
  *  Class to store relevant data to be analyzed
  */

class Data
{

public:
    Data(){}

    double timeStamp;

    int pulsefreq;
    int breathingfreq;
    int blinkingfreq;
};

#endif // DATA_H
