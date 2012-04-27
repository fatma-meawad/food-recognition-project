#include "featuredetection.h"

Featuredetection::Featuredetection()
{
}


int detectface (IplImage* img, CvRect* face){
    int i;
    static CvHaarClassifierCascade* cascade = 0;
    static CvMemStorage* storage = 0;
    storage = cvCreateMemStorage(0);
    cascade = (CvHaarClassifierCascade*)cvLoad( "../../../../../opencv/data/haarcascades/haarcascade_frontalface_alt.xml", 0, 0, 0 );
    if( !cascade )
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
    }else{
        CvSeq* faces = cvHaarDetectObjects( img, cascade, storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) );

        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
            // Create a new rectangle for drawing the face
            CvRect*r= (CvRect*)cvGetSeqElem( faces, i );
            *face=*r;
            // Find the dimensions of the face,and scale it if necessary
            cvClearMemStorage( storage );
            return 1;
        }
    }
    return -1;
}

int detectEye (IplImage* img,CvPoint roi, CvRect* eyes){
    int i;
    static CvHaarClassifierCascade* cascade = 0;
    static CvMemStorage* storage = 0;
    storage = cvCreateMemStorage(0);
    cascade = (CvHaarClassifierCascade*)cvLoad( "../../../../../opencv/data/haarcascades/haarcascade_eye.xml", 0, 0, 0 );
    if( !cascade )
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
    }else{
        CvSeq* faces = cvHaarDetectObjects( img, cascade, storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) );

        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
            // Create a new rectangle for drawing the face
            CvRect*r = (CvRect*)cvGetSeqElem( faces, i );
            *eyes=*r;
            eyes->x=r->x+roi.x;
            eyes->y=r->y+roi.y;

            // Find the dimensions of the face,and scale it if necessary
            cvClearMemStorage( storage );
            return 1;
        }
    }
    return -1;
}


Facefeatures Featuredetection::detectfeatures(IplImage* img){
    Facefeatures head;
    CvPoint A;
    if(-1==detectface(img,&head.mFace)){
        fprintf( stderr, "Could not locate head" );
    }else{
        cvSetImageROI(img,cvRect(head.mFace.x,head.mFace.y,head.mFace.width/2,head.mFace.height/2));
        A.x=head.mFace.x;
        A.y=head.mFace.y;
        detectEye(img,A,&head.mLeftEye);
        cvResetImageROI(img);
        cvSetImageROI(img,cvRect(head.mFace.x+head.mFace.width/2,head.mFace.y,head.mFace.width/2,head.mFace.height/2));
        A.x=head.mFace.x+head.mFace.width/2;
        A.y=head.mFace.y;
        detectEye(img,A,&head.mRightEye);
        cvResetImageROI(img);


        cvRectangleR( img, head.mFace, CV_RGB(255,0,0), 3, 8, 0 );
        cvRectangleR( img, head.mLeftEye, CV_RGB(0,255,0), 3, 8, 0 );
        cvRectangleR( img, head.mRightEye, CV_RGB(0,0,255), 3, 8, 0 );
    }
    cvShowImage("result", img);
    return head;

}
