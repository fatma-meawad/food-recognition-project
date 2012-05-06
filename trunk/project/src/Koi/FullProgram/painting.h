#ifndef PAINTING_H
#define PAINTING_H

#include "Includes.h"

class Facefeatures;
class Data;

class Painting
{
public:
    Painting();

    static IplImage* drawFullFace(IplImage*, Facefeatures*);
    static IplImage* drawHairCross(IplImage*, CvPoint);
    static IplImage* drawRect(IplImage*, CvRect);
    static IplImage* drawCircle(IplImage*, CvPoint);

    static void drawGraph(std::list<Data>);

 private:
    static void init(void);
};

#endif // PAINTING_H
