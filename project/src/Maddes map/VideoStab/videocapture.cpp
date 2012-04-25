#include "videocapture.h"
#include "Includes.h"

using namespace cv;

videocapture::videocapture()
{
}

videocapture::~videocapture()
{

}

int videocapture::Init(int camMode)
{

    return 1;
}


IplImage * videocapture::GetFrame()
{
    IplImage * returnimage = cvQueryFrame(this->capture);
    return returnimage;
}


int videocapture::UpdateFrame()
{
    return 1;
}
