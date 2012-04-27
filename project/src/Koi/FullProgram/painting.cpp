#include "painting.h"

Painting::Painting()
{
}
// Draw haircross
IplImage* Painting::drawHairCross(IplImage* img, CvPoint p){
    cvLine(img,cvPoint(p.x-15,p.y),cvPoint(p.x+15,p.y),cvScalar(100,0,100), 1);
    cvLine(img,cvPoint(p.x,p.y-15),cvPoint(p.x,p.y+15),cvScalar(100,0,100), 1);

    return img;
}

// Draw rectangle
IplImage* Painting::drawRect(IplImage * img, CvRect rect){
    cvRectangleR(img,rect,cvScalar(255,0,0), 5);

    return img;
}

// Draw alla features
IplImage* Painting::drawFullFace(IplImage * img, Facefeatures * ff)
{
    drawRect(img, ff->mFace);
    drawHairCross(img, ff->center(ff->mLeftEye));
    drawHairCross(img, ff->center(ff->mRightEye));

    return img;
}

// Graphs
void Painting::drawGraph(std::list<Data> ls)
{
    for (list<Data>::iterator it = ls.begin(); it != ls.end(); it++){
        std::cout << it->pulsefreq << std::endl;
    }
}
