#include "head.h"



// Create memory for calculations
static CvMemStorage* storage = 0;

int main( int argc, char** argv )
{
    /**
      * Initiera class (madde)
      *
      *
      **/

    Head head;

    // Structure for getting video from camera or avi
    CvCapture* capture = 0;

    // Images to capture the frame from video or camera or from file
    IplImage *frame, *frame_copy = 0;

    // Allocate the memory storage
    storage = cvCreateMemStorage(0);

    // Add path to see video, default is cam
    if( argc > 1 )
        capture = cvCaptureFromAVI( argv[1] );
    else
        capture = cvCaptureFromCAM( CV_CAP_ANY );

    // Create a new named window with title: result
    cvNamedWindow( "result", 1 );

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
                frame_copy = cvCreateImage( cvSize(frame->width,frame->height), IPL_DEPTH_8U, frame->nChannels );

            // Check the origin of image. If top left, copy the image frame to frame_copy.
            if( frame->origin == IPL_ORIGIN_TL )
                cvCopy( frame, frame_copy, 0 );
            // Else flip and copy the image
            else
                cvFlip( frame, frame_copy, 0 );

             /**
              *
              *     Tillkalla era funktioner här
              *
              *
              **/

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
