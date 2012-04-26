#include "preprocessing.h"

Preprocessing::Preprocessing()
{
}


IplImage * Preprocessing::Crop(CvRect Size, IplImage * Image)
{
    IplImage * CroppedImage;

    CroppedImage = cvCreateImage(cvSize(Size.width,Size.height));

    cvSetImageROI(Image,Size);

    cvCopyImage(Image,CroppedImage);

    cvSetImageRoi(Image);

    return CroppedImage;

}


IplImage * Preprocessing::MakeGrayscale(IplImage * Image)
{
    cvCvtColor(Image,Image,CV_RGB2GRAY);
    return Image;
}
