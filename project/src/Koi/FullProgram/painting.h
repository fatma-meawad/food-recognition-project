#ifndef PAINTING_H
#define PAINTING_H

#include "Includes.h"

class Painting
{
public:
    Painting();

    IplImage* drawHairCross(IplImage*, CvPoint);
    IplImage* drawRect(IplImage*, CvRect);
    IplImage* drawCircle(IplImage*, CvPoint);

    void drawGraph();
};

#endif // PAINTING_H
