

#include <iostream>
#include <opencv-2.3.1/opencv/cv.h>
#include <opencv-2.3.1/opencv/highgui.h>
#include <opencv-2.3.1/opencv2/imgproc/imgproc_c.h>
#include <opencv-2.3.1/opencv2/video/video.hpp>


int main(int argc, char *argv[])
{
    CvCapture * capture = 0;
    IplImage * frame = 0;

    if (!(capture = cvCaptureFromCAM(0)))
         printf("Cannot initialize camera\n");


    cvNamedWindow("Video",CV_WINDOW_AUTOSIZE);


    while (1)
    {

          frame = cvQueryFrame(capture);

          if (!frame)
              break;


          cvShowImage("Video",frame);


          if( cvWaitKey( 15 ) == 27 )
                                  break;


    }


}
