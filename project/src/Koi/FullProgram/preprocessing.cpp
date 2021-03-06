#include "preprocessing.h"

Preprocessing::Preprocessing()
{
    this->CurrentP = cvPoint(0,0);
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

IplImage * Preprocessing::MakeBinary(IplImage * Image)
{    
    IplImage * Binary = cvCreateImage(cvSize(Image->width,Image->height),IPL_DEPTH_8U,1);
    cvCvtColor(Image, Binary, CV_RGB2GRAY);                   // Make grey
    cvEqualizeHist(Binary, Binary);                             // Equalize image, helpful with shifting light settings
    cvNot(Binary, Binary);                                      // Inverter
    cvThreshold(Binary,Binary,225,255,CV_THRESH_BINARY_INV);    // Threshold, makes it binary

    // Free memory
    cvReleaseImage(&Image);

    return Binary;
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

IplImage * Preprocessing::MakeDiffImage(Videocapture VC)
{


    if(VC.CurrentFrame == NULL)
        return NULL;

    IplImage * Temp = cvCreateImage(cvSize(VC.CurrentFrame->width,VC.CurrentFrame->height),VC.CurrentFrame->depth,VC.CurrentFrame->nChannels);

    cvCopyImage(VC.CurrentFrame,Temp);
    VC.UpdateFrame();


    cvAbsDiff(Temp,VC.CurrentFrame,VC.CurrentFrame);

    cvReleaseImage(&Temp);

    return VC.CurrentFrame;

}
