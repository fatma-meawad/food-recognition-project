

#include <iostream>
#include <opencv-2.3.1/opencv/cv.h>
#include <opencv-2.3.1/opencv/highgui.h>
#include <opencv-2.3.1/opencv2/imgproc/imgproc_c.h>
#include <math.h>

using namespace std;

bool measure = false;
bool box = false;
CvPoint ROICorner;
CvPoint ROICorner2;


void mouse_callback( int event, int x, int y, int flags, void* param )
{
    switch(event)
    {

    case CV_EVENT_LBUTTONDOWN:
        box = true;
        ROICorner.x = x;
        ROICorner.y = y;
        break;

    case CV_EVENT_MOUSEMOVE:

        if(box)
        {
            ROICorner2.x = x;
            ROICorner2.y = y;
        }
        break;

    case CV_EVENT_LBUTTONUP:
        measure = true;
        box = false;
        break;

    }
}


void DrawRect(IplImage * input)
{
    cvDrawRect(input,ROICorner,ROICorner2,cvScalar(0x00,0x00,0x00),2);
}


CvScalar CalcColors(IplImage * Image)
{

    CvScalar Colors;
    CvScalar pixel;


    Colors.val[0] = Colors.val[1] = Colors.val[2] = 0;

    for(int i = Image->roi->yOffset; i < Image->roi->height;i++)// + Image->roi->yOffset; i++)
    {
        for(int j = Image->roi->xOffset; j < Image->roi->width;j++)// + Image->roi->xOffset; j++)
        {
            pixel = cvGetAt(Image,i,j);
            //printf("%f,",pixel.val[0]);
            Colors.val[0] += pixel.val[0];
            Colors.val[1] += pixel.val[1];
            Colors.val[2] += pixel.val[2];
        }
    }

  //  printf("%d\n",Colors.val[0]);

    //BLIR 0 AV NÅGON ANLEDNING
    return Colors;
}




int main(int argc, char *argv[])
{

    IplImage * frame = 0;
    IplImage * temp = 0;
    IplImage * clone = 0;
    CvCapture * video = 0;
    CvScalar Colors;
    int fps = 0;
    FILE* blue;
    FILE* green;
    FILE* red;

    cvNamedWindow("Video",CV_WINDOW_AUTOSIZE);
   // cvNamedWindow("ROI",CV_WINDOW_AUTOSIZE);
   // cvNamedWindow("CLONE",CV_WINDOW_AUTOSIZE);
    cvSetMouseCallback("Video",mouse_callback,NULL);

    if(argc > 1)
        video = cvCaptureFromAVI(argv[1]);
    else
        return -1;

    //home//emil//
    blue = fopen("bluevalues.txt","w");
    green = fopen("greenvalues.txt","w");
    red = fopen("redvalues.txt","w");

    if(!blue || !green || !red)
    {
        printf("fel i filer");
        return -2;
    }

    frame = cvQueryFrame(video);


    fps = ( int )cvGetCaptureProperty( video, CV_CAP_PROP_FPS );

    while(1)
    {
        temp = cvCreateImage(cvSize(frame->width,frame->height),frame->depth,frame->nChannels);
        cvCopyImage(frame,temp);

        DrawRect(temp);
        cvShowImage("Video",temp);

        if(measure)
        {
            cvSetImageROI(temp,cvRect(ROICorner.x,ROICorner.y,sqrt(pow(ROICorner2.x - ROICorner.x,2)),sqrt(pow(ROICorner2.y - ROICorner.y,2))));


            //cvShowImage("ROI",temp);

            // clone = cvCloneImage(temp);

            //cvShowImage("CLONE",clone);

            Colors = CalcColors(temp);

            if(fprintf(blue,"%f\n",Colors.val[0]) == -1)
                return -3;

            if(fprintf(green,"%f\n",Colors.val[1]) == -1)
                return -4;

            if(fprintf(red,"%f\n",Colors.val[2]) == -1)
                return -5;
        }





        if(cvWaitKey(1000/fps) == 27)
            break;


        frame = cvQueryFrame(video);

        if(!frame)
            break;
    }

    cvReleaseCapture(&video);
    cvDestroyWindow("Video");
    fclose(blue);
    fclose(green);
    fclose(red);

}
