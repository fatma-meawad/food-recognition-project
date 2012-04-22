
#include <iostream>
#include <opencv-2.3.1/opencv/cv.h>
#include <opencv-2.3.1/opencv/highgui.h>
#include <opencv-2.3.1/opencv2/imgproc/imgproc_c.h>
#include <math.h>

using namespace std;


bool circle = false;
CvPoint * CR;
CvPoint * CC;
float Radius = 0.0;

float CalcRad()
{
    return sqrt(pow(CC->x - CR->x,2) + pow(CC->y - CR->y,2));
}

void DrawCirc(IplImage * image)
{
    cvDrawCircle(image,*CC,CalcRad(),cvScalar(0x00,0x00,0x00),2);
}


void mouse_callback( int event, int x, int y, int flags, void* param )
{

    IplImage * passedImage = (IplImage*)param;

    switch(event)
    {
    case CV_EVENT_MOUSEMOVE:
        if(circle)
        {
            CR->x = x;
            CR->y = y;
        }
        //cout << "CV_EVENT_MOUSEMOVE";
        break;
    case CV_EVENT_LBUTTONDOWN:
        circle = true;
        CC->x = x;
        CC->y = y;
        cout << "CV_EVENT_RBUTTONDOWN";
        break;
    case CV_EVENT_LBUTTONUP:
        circle = false;
        DrawCirc(passedImage);
        cout << "CV_EVENT_RBUTTONUP";
        break;
    }
}





int main(int argc, char *argv[])
{

    IplImage * InputImage = 0;
    IplImage * temp = 0;

    CC = new CvPoint();
    CR = new CvPoint();

    if(argc > 1)
        InputImage = cvLoadImage(argv[1],CV_LOAD_IMAGE_COLOR);

    cvNamedWindow("Image",CV_WINDOW_AUTOSIZE);
    cvSetMouseCallback("Image",mouse_callback,NULL);
    temp = cvCreateImage(cvSize(InputImage->width,InputImage->height),InputImage->depth,InputImage->nChannels);


    while(true)
    {

        cvCopyImage(InputImage,temp);

        if(circle)
        {
            DrawCirc(temp);
        }
        cvShowImage("Image",temp);


        if(cvWaitKey(2) == 27)
            break;
    }

}
