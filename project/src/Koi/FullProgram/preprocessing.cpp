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

    if(Size.height < 0 || Size.width < 0 || Size.x < 0 || Size.y < 0)
        return Image;

    cvSetImageROI(Image,Size);

    CroppedImage = cvCreateImage(cvSize(Image->roi->width,Image->roi->height),Image->depth,Image->nChannels); //create return image

    cvCopyImage(Image,CroppedImage); //copy

    cvSetImageROI(Image, orgsize);

    return CroppedImage;
}


IplImage * Preprocessing::MakeGrayscale(IplImage * Image)
{    
    IplImage * Temp = cvCreateImage(cvSize(Image->width,Image->height),IPL_DEPTH_8U,1);
    cvCvtColor(Image, Temp, CV_RGB2GRAY);
    //cvNot(Temp, Temp);    // Inverter
    //cvThreshold(Temp,Temp,150,250,CV_THRESH_BINARY_INV);    // Threshold

    // Free memory
    cvReleaseImage(&Image);

    return Temp;
}

IplImage * Preprocessing::MakeHSV(IplImage * Image)
{
    IplImage * Temp = cvCreateImage(cvSize(Image->width,Image->height),IPL_DEPTH_8U,3);
    cvCvtColor(Image, Temp, CV_RGB2HSV);

    cvReleaseImage(&Image);

    return Temp;
}

IplImage * Preprocessing::Stabilize(IplImage * Image,Facefeatures* Inputfeatures)
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
