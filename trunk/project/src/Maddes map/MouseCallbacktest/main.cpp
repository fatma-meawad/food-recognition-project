
#include <iostream>
#include <opencv-2.3.1/opencv/cv.h>
#include <opencv-2.3.1/opencv/highgui.h>
#include <opencv-2.3.1/opencv2/imgproc/imgproc_c.h>
#include <math.h>




void mouse_callback( int event, int x, int y, int flags, void* param )
{

    IplImage * passedImage = (IplImage*)param;

    switch(event)
    {

    }
}





int main(int argc, char *argv[])
{

    IplImage * InputImage = 0;

    if(argc > 1)
        InputImage = cvLoadImage(argv[1],CV_LOAD_IMAGE_COLOR);

    cvNamedWindow("Image",CV_WINDOW_AUTOSIZE);
    cvSetMouseCallback("Image",mouse_callback,null);


    cvShowImage("Image",InputImage);


    cvWaitKey(0);
}
