#include "preprocessing.h"

Preprocessing::Preprocessing()
{
    this->CurrentP = cvPoint(0,0);
//    this->Tolerance = 100;
}


IplImage * Preprocessing::Crop(CvRect Size, IplImage * Image)
{
    IplImage * CroppedImage;
    CvRect orgsize = cvRect(0,0,Image->width,Image->height); //save original size

    cvSetImageROI(Image,Size);

    CroppedImage = cvCreateImage(cvSize(Image->roi->width,Image->roi->height),Image->depth,Image->nChannels); //create return image


    cvCopyImage(Image,CroppedImage); //copy

    cvSetImageROI(Image, orgsize);

    return CroppedImage;

}


void Preprocessing::MakeGrayscale(IplImage * Image)
{
    //cvCvtColor(Image,Image,CV_RGB2GRAY);
}

IplImage * Preprocessing::Stabilize(Facefeatures* Inputfeatures, IplImage * Image)
{

    if(Pointdistance(this->CurrentP,cvPoint(0,0)) == 0.0 || Pointdistance(cvPoint(Inputfeatures->mFace.x,Inputfeatures->mFace.y),CurrentP) > Tolerance)
    {
        CurrentP = cvPoint(Inputfeatures->mFace.x,Inputfeatures->mFace.y);
        CurrentCrop = cvRect(std::max(Inputfeatures->mFace.x - Tolerance, 0),
                             std::max(Inputfeatures->mFace.y - Tolerance, 0),
                             std::min(Inputfeatures->mFace.width +  2 * Tolerance,Image->width),
                             std::min(Inputfeatures->mFace.height + 2 * Tolerance,Image->height));
    }

    return this->Crop(CurrentCrop, Image);
}


float Preprocessing::Pointdistance(CvPoint p1, CvPoint p2)
{
    return sqrt((double)pow((p1.x - p2.x),2) + (double)pow((p1.y - p2.y),2));
}
