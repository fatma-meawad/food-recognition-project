
#include <iostream>
#include <opencv-2.3.1/opencv/cv.h>
#include <opencv-2.3.1/opencv/highgui.h>
#include <opencv-2.3.1/opencv2/imgproc/imgproc_c.h>
#include <math.h>


using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{

    IplImage * frame = 0;
    CvCapture * InputCapture = 0;

    if(argc > 1)
        InputCapture = cvCaptureFromAVI(argv[1]);

    if(!InputCapture)
    {
        cout << "Fel i inläsning av fil";
        return -1;
    }

    int fps = ( int )cvGetCaptureProperty( InputCapture, CV_CAP_PROP_FPS );

    cvNamedWindow("Video",CV_WINDOW_AUTOSIZE);

    while(1)
    {
        frame = cvQueryFrame( InputCapture );

        cvShowImage("Video",frame);

        if(cvWaitKey(1000/fps) == 27)
            break;

    }


    cvReleaseCapture(&InputCapture);
    cvDestroyWindow("Video");


}
