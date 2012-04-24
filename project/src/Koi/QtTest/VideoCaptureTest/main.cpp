#include <QtCore/QCoreApplication>


#include <opencv-2.3.1/opencv/cv.h>
#include <opencv-2.3.1/opencv/highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>

// Create memory for calculations
static CvMemStorage* storage = 0;

// Create a new Haar classifier
static CvHaarClassifierCascade* cascade = 0;
static CvHaarClassifierCascade* cascadeEye = 0;

// Function prototype for detecting and drawing an object from an image
void detect_and_draw( IplImage* image );

// Function to find eyes
bool detect_eyes( IplImage* image );

// Global points for ROI
CvPoint g1 = cvPoint(0,0);
CvPoint g2 = g1;

// Main function, defines the entry point for the program.
int main( int argc, char** argv )
{

    // Structure for getting video from camera or avi
    CvCapture* capture = 0;

    // Images to capture the frame from video or camera or from file
    IplImage *frame, *frame_copy = 0;

    // Input file name for avi or image file.
    const char* input_name = 0;

    // Check for the correct usage of the command line
    if( argc > 1)
        input_name = argv[1];

    // Load the HaarClassifierCascade
    cascade = (CvHaarClassifierCascade*)cvLoad( "/home/blacktemple/opencv/data/haarcascades/haarcascade_frontalface_alt.xml", 0, 0, 0 );

    // Check whether the cascade has loaded successfully. Else report and error and quit
    if( !cascade )
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        return -1;
    }

    // Allocate the memory storage
    storage = cvCreateMemStorage(0);

    // Find whether to detect the object from file or from camera.
    if( !input_name || (isdigit(input_name[0]) && input_name[1] == '\0') )
        capture = cvCaptureFromCAM( CV_CAP_ANY );
    else
        capture = cvCaptureFromAVI( input_name );

    // Create a new named window with title: result
    cvNamedWindow( "result", 1 );

    // Find if the capture is loaded successfully or not.

    // If loaded succesfully, then:
    if( capture )
    {
        // Capture from the camera.
        for(;;)
        {
            // Capture the frame and load it in IplImage
            if( !cvGrabFrame( capture ))
                break;
            frame = cvRetrieveFrame( capture );

            // If the frame does not exist, quit the loop
            if( !frame )
                break;

            // Allocate framecopy as the same size of the frame
            if( !frame_copy )
                frame_copy = cvCreateImage( cvSize(frame->width,frame->height),
                                            IPL_DEPTH_8U, frame->nChannels );

            // Check the origin of image. If top left, copy the image frame to frame_copy.
            if( frame->origin == IPL_ORIGIN_TL )
                cvCopy( frame, frame_copy, 0 );
            // Else flip and copy the image
            else
                cvFlip( frame, frame_copy, 0 );

            // Call the function to detect and draw the face
            detect_and_draw( frame_copy );

            // Wait for a while before proceeding to the next frame
            if( cvWaitKey( 10 ) >= 0 )
                break;
        }

        // Release the images, and capture memory
        cvReleaseImage( &frame_copy );
        cvReleaseCapture( &capture );
    }
    else
        return -3;

}

// Function to detect and draw any faces that is present in an image
void detect_and_draw( IplImage* img )
{
    IplImage *faceImg = 0;
    int scale = 1;

    // Create two points to represent the face locations
    CvPoint pt1, pt2;
    int i;

    // Clear the memory storage which was used before
    cvClearMemStorage( storage );

    // Find whether the cascade is loaded, to find the faces. If yes, then:
    if( cascade )
    {

        // There can be more than one face in an image. So create a growable sequence of faces.
        // Detect the objects and store them in the sequence
        CvSeq* faces = cvHaarDetectObjects( img, cascade, storage,
                                            1.1, 2, CV_HAAR_DO_CANNY_PRUNING,
                                            cvSize(40, 40) );

        // Loop the number of faces found.
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
            // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );

            // Find the dimensions of the face,and scale it if necessary
            pt1.x = r->x*scale;
            pt2.x = (r->x+r->width)*scale;
            pt1.y = r->y*scale;
            pt2.y = (r->y+r->height)*scale;

            // Clone the original image
            IplImage *cloneImg = cvCloneImage(img);

            // Set Region Of Interest where the face is located
            cvSetImageROI(cloneImg,cvRect(pt1.x,pt1.y,(pt2.x-pt1.x),(pt2.y-pt1.y)));
            faceImg=cvCloneImage(cloneImg);
            cvResetImageROI(cloneImg);

            // Free the image
            cvReleaseImage( &cloneImg );
        }

        if(faces ? faces->total : 0){
            if(detect_eyes(faceImg))
                g1 = pt1;

            cvShowImage("result", faceImg);
        }
        else
            cvShowImage("result", img);
        cvReleaseImage(&faceImg);
    }
}

// Function to detect eyes
bool detect_eyes( IplImage* img )
{
    int scale = 1;
    bool twoEyes = false;

    // Create two points to represent the face locations
    CvPoint pt1, pt2;
    int i;

    // Clear the memory storage which was used before
    cvClearMemStorage( storage );

    cascadeEye = (CvHaarClassifierCascade*)cvLoad( "/home/blacktemple/opencv/data/haarcascades/haarcascade_eye.xml", 0, 0, 0 );

    // Find whether the cascade is loaded, to find the faces. If yes, then:
    if( cascadeEye )
    {
        // Haar feature for eyes
        CvSeq* eyes = cvHaarDetectObjects( img, cascadeEye, storage,
                                            1.1, 2, CV_HAAR_DO_CANNY_PRUNING,
                                            cvSize(40, 40) );

        // Loop the number of eyes found.
        for( i = 0; i < (eyes ? eyes->total : 0); i++ )
        {
            // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*)cvGetSeqElem( eyes, i );

            // Find the dimensions of the face,and scale it if necessary
            pt1.x = r->x*scale;
            pt2.x = (r->x+r->width)*scale;
            pt1.y = r->y*scale;
            pt2.y = (r->y+r->height)*scale;

            // Draw rectangles where the eyes are located
            cvRectangle( img, pt1, pt2, CV_RGB(255,0,0), 3, 8, 0 );
        }

        if(eyes->total > 1)
            twoEyes = true;

        // Put number of eyes on the screen
        CvFont font;
        char str[20];
        sprintf(str,"Eyes: %d",eyes->total);
        cvInitFont(&font,CV_FONT_HERSHEY_PLAIN, 1.0,1.0,0,1);
        cvPutText (img, str,cvPoint(20,20), &font, cvScalar(0,0,0));
    }
    return twoEyes;
}

