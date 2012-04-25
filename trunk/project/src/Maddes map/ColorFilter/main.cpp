
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <math.h>


using namespace std;
using namespace cv;


int smoothint = 0;
int smoothlevel = 0.1;

int minredLevel = 0;
int minblueLevel = 0;
int mingreenLevel = 0;
int maxredLevel = 0;
int maxblueLevel = 0;
int maxgreenLevel = 0;


void Minred_callback(int position)
{
    minredLevel = position;
}

void Minblue_callback(int position)
{
    minblueLevel = position;
}

void Mingreen_callback(int position)
{
    mingreenLevel = position;
}

void Maxred_callback(int position)
{
    maxredLevel = position;
}

void Maxblue_callback(int position)
{
    maxblueLevel = position;
}

void Maxgreen_callback(int position)
{
    maxgreenLevel = position;
}



int main(int argc, char *argv[])
{
    IplImage * InputImage = 0;
    IplImage * OpImage = 0;
    CvScalar Pixel;


    if(argc > 1)
    {
            InputImage = cvLoadImage( argv[1] , CV_LOAD_IMAGE_COLOR);
    }

    cout << "File Loaded";

    cvNamedWindow("Color filter",0);

    cvCreateTrackbar("Min Red","Color filter",&smoothlevel,255, Minred_callback);
    cvCreateTrackbar("Min Green","Color filter",&smoothlevel,255, Mingreen_callback);
    cvCreateTrackbar("Min Blue","Color filter",&smoothlevel,255, Minblue_callback);

    cvCreateTrackbar("Max Red","Color filter",&smoothlevel,255, Maxred_callback);
    cvCreateTrackbar("Max Green","Color filter",&smoothlevel,255, Maxgreen_callback);
    cvCreateTrackbar("Max Blue","Color filter",&smoothlevel,255, Maxblue_callback);

    OpImage = cvCreateImage(cvSize(InputImage->width,InputImage->height),InputImage->depth,InputImage->nChannels);


    printf("HEJ");

    while(1)
    {
        cvCopyImage(InputImage,OpImage);

        for(int i = 0; i < OpImage->width; i++)
        {
            for(int j = 0; j < OpImage->height; j++)
            {
                Pixel = cvGetAt(OpImage,j,i);

                if(Pixel.val[0] < minblueLevel || Pixel.val[0] > maxblueLevel)
                {
                    Pixel.val[0] = 0;
                }

                if(Pixel.val[1] < mingreenLevel || Pixel.val[1] > maxgreenLevel)
                {
                    Pixel.val[1] = 0;
                }

                if(Pixel.val[2] < minredLevel || Pixel.val[2] > maxredLevel)
                {
                    Pixel.val[2] = 0;
                }

                cvSet2D(OpImage,j,i,Pixel);
            }
        }

        cvShowImage("Color filter",OpImage);

        if( cvWaitKey( 15 ) == 27 )
                                break;
    }

}
