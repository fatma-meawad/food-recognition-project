#include "painting.h"

Painting::Painting()
{
}
// Draw haircross
IplImage* Painting::drawHairCross(IplImage* img, CvPoint p){
    cvLine(img,cvPoint(p.x-5,p.y),cvPoint(p.x+5,p.y),cvScalar(100,0,100));
    cvLine(img,cvPoint(p.x,p.y-5),cvPoint(p.x,p.y+5),cvScalar(100,0,100));

    return img;
}

// Draw rectangle
IplImage* Painting::drawRect(IplImage * img, CvRect rect){
    cvRectangle(img,cvPoint(rect.x,rect.y),cvPoint(rect.x+rect.width,rect.y+rect.height),cvScalar(255,0,0));

    return img;
}
