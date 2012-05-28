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
    IplImage * Gray = cvCreateImage(cvSize(Image->width,Image->height),IPL_DEPTH_8U,1);
    cvCvtColor(Image, Gray, CV_RGB2GRAY);
    cvShowImage("Gray", Gray);
    cvEqualizeHist(Gray, Gray);
    cvShowImage("Equalized", Gray);
    cvNot(Gray, Gray);    // Inverter
    cvThreshold(Gray,Gray,225,255,CV_THRESH_BINARY_INV);    // Threshold
    cvShowImage("Threshold", Gray);



    /*CvMemStorage* storage = cvCreateMemStorage(0);
    cvSmooth(Gray, Gray, CV_GAUSSIAN, 3, 3);
    CvSeq* circles = cvHoughCircles(Gray, storage, CV_HOUGH_GRADIENT,2, Gray->height, 250, 50, Gray->height/8, Gray->height/1.6);

    std::cout << "Total circles: " << circles->total << std::endl;

    for (int i = 0; i < circles->total; i++)
        {
             float* p = (float*)cvGetSeqElem( circles, i );
             cvCircle( Gray, cvPoint(cvRound(p[0]),cvRound(p[1])),
                 3, CV_RGB(0,255,0), -1, 8, 0 );
             cvCircle( Gray, cvPoint(cvRound(p[0]),cvRound(p[1])),
                 cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );
        }*/

    // Free memory
    cvReleaseImage(&Image);
    //cvReleaseMemStorage(&storage);

    return Gray;
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

    return VC.CurrentFrame; //kan vara void om man vill

}
