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
    static IplImage* drawCircle(IplImage*, CvPoint, int, int);

    void drawGraph();

    void update(int x, int y);

    int mSelect;
    IplImage* mImage;

    std::vector<Data> mData;

    cv::Rect mLeftButton;
    cv::Rect mRightButton;

    void drawInit(Painting*);
};

#endif // PAINTING_H
