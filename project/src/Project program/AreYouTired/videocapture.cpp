#include "videocapture.h"
#include "Includes.h"

using namespace cv;
using namespace std;

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
    case ANY_CAM:
        this->capture = cvCaptureFromCAM(-1);
        if(!this->capture)
        {
            cout << "Error: capture == NULL";
            return -1;
        }
        break;

    default:
        cout << "invalid cammode";
        return -2;
        break;
    }


    return 1;
}


IplImage * Videocapture::GetFrame()
{
    IplImage * returnimage = cvQueryFrame(this->capture);
    return returnimage;
}


int Videocapture::UpdateFrame()
{
    this->CurrentFrame = this->GetFrame();

    if(!this->CurrentFrame)
    {
        cout << "cant get frame";
        return -2;
    }
    return 1;
}
