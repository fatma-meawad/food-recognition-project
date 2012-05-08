#include "videocapture.h"
#include "Includes.h"

Videocapture::Videocapture()
{
}

Videocapture::~Videocapture()
{
    cvReleaseCapture(&this->capture);
}

int Videocapture::Init(int camMode)
{
    int cm = camMode;

    switch(cm)
    {
    case CV_CAP_ANY:
        this->capture = cvCaptureFromCAM(-1);
        if(!this->capture)
        {
            std::cout << "Error: capture == NULL";
            return -1;
        }
        break;

    default:
        std::cout << "invalid cammode";
        return -2;
        break;
    }


    return 1;
}


IplImage * Videocapture::GetFrame()
{
    if(!this->capture)
    {
        std::cout << "Capture = null";
        return NULL;
    }

    IplImage * returnimage = cvQueryFrame(this->capture);
    return returnimage;
}


int Videocapture::UpdateFrame()
{
    this->CurrentFrame = this->GetFrame();

    if(!this->CurrentFrame)
    {
        std::cout << "cant get frame";
        return -2;
    }
    this->AVI = false;
    return 1;
}

int Videocapture::InitAVI(char * filename)
{
    this->capture = cvCaptureFromAVI(filename);

    if(!this->capture)
         {
        std::cout << "Error: Avi capture == null";
        return -1;
    }

    this->AVI = true;
    this->fps = ( int )cvGetCaptureProperty( this->capture, CV_CAP_PROP_FPS );
    return 1;
}
