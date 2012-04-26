#include "facefeatures.h"

CvPoint Facefeatures::center(CvRect rect){

    return cvPoint(rect.x+rect.width/2,rect.y+rect.height/2);
}
