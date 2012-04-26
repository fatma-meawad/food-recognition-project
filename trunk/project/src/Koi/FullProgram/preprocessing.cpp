#include "preprocessing.h"

Preprocessing::Preprocessing()
{
}


IplImage * Preprocessing::Crop(CvRect Size, IplImage * Image)
{
    IplImage * CroppedImage;
    CvRect orgsize = cvRect(0,0,Image->width,Image->height);

    CroppedImage = cvCreateImage(cvSize(Size.width,Size.height),Image->depth,Image->nChannels);

    cvSetImageROI(Image,Size);

    cvCopyImage(Image,CroppedImage);

    cvSetImageROI(Image, orgsize);

    return CroppedImage;

}


void Preprocessing::MakeGrayscale(IplImage * Image)
{
    cvCvtColor(Image,Image,CV_RGB2GRAY);
}
