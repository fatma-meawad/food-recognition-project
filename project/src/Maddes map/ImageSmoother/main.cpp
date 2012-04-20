
#include <iostream>
#include <opencv-2.3.1/opencv/cv.h>
#include <opencv-2.3.1/opencv/highgui.h>
#include <opencv-2.3.1/opencv2/imgproc/imgproc_c.h>


using namespace std;
using namespace cv;


int smoothint = 0;
int smoothlevel = 1;

void smooth_callback(int position)
{
    smoothint = position;
}


int main(int argc, char *argv[])
{
    IplImage * InputImage = 0;
    IplImage * OpImage = 0;


    if(argc > 1)
    {
            InputImage = cvLoadImage( argv[1] , CV_LOAD_IMAGE_COLOR);
    }

    cout << "File Loaded";

    cvNamedWindow("Color filter",0);
    cvCreateTrackbar("Smoothness","Color filter",&smoothlevel,100, smooth_callback);

    OpImage = cvCreateImage(cvSize(InputImage->width,InputImage->height),InputImage->depth,InputImage->nChannels);

    while(1)
    {
        cvCopyImage(InputImage,OpImage);

        for(int i = 0; i < smoothint; i++)
        {
            cvSmooth(OpImage,OpImage,CV_GAUSSIAN,5,5);
        }

        cvShowImage("Color filter",OpImage);

        if( cvWaitKey( 15 ) == 27 )
                                break;
    }

}
