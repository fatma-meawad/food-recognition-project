#include "painting.h"

Painting::Painting()
{
}
// Draw haircross
IplImage* Painting::drawHairCross(IplImage* img, CvPoint p){
    cvLine(img,cvPoint(p.x-5,p.y),cvPoint(p.x+5,p.y),cvScalar(100,0,100), 2);
    cvLine(img,cvPoint(p.x,p.y-5),cvPoint(p.x,p.y+5),cvScalar(100,0,100), 2);

    return img;
}

// Draw rectangle
IplImage* Painting::drawRect(IplImage * img, CvRect rect){
    cvRectangleR(img,rect,cvScalar(255,0,0), 5);

    return img;
}

IplImage* Painting::drawFullFace(IplImage * img, Facefeatures * ff)
{
    drawRect(img, ff->mFace);
    drawHairCross(img, ff->center(ff->mLeftEye));
    drawHairCross(img, ff->center(ff->mRightEye));

    return img;
}
