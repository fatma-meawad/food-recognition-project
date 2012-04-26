#include "videodetection.h"
using namespace std;

videodetection::videodetection()
{
}


int videodetection::Init(int camMode)
{
    this->VC.Init(camMode);
    this->numCascades = 0;
    this->storage = cvCreateMemStorage(0);
    this->cascade_names[0] = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
    return 1;
}


int videodetection::InitFace()
{
    cvWaitKey(10);

    this->cascades[this->numCascades] = (CvHaarClassifierCascade*)cvLoad( this->cascade_names[0] , 0, 0, 0 );

    if(!this->cascades[this->numCascades])
    {
        cout << "Failed to initialize face cascade";
        return -1;
    }

    this->numCascades++;

    return 1;
}

int videodetection::InitEye()
{
    return 1;
}

int videodetection::UpdateFrame()
{


    this->VC.UpdateFrame();
    this->CurrentImage = this->VC.CurrentFrame;

    if(!this->CurrentImage)
    {
        cout << "Current image not updated";
        return -2;
    }

    if(this->numCascades == 0)
        return 1;

    for(int i = 0; i < this->numCascades; i++)
    {
        this->FoundCascades = cvHaarDetectObjects( this->CurrentImage, this->cascades[i], storage, 1.1, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize(40, 40) );


        for( i = 0; i < (this->FoundCascades ? this->FoundCascades->total : 0); i++ )
        {

            CvRect* r = (CvRect*)cvGetSeqElem( this->FoundCascades, i );
            pt1.x = r->x;
            pt2.x = (r->x+r->width);
            pt1.y = r->y;
            pt2.y = (r->y+r->height);

            cvRectangle( this->CurrentImage, pt1, pt2, CV_RGB(255,0,0), 3, 8, 0 );
        }
    }


    return 1;
}
