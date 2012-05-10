#include "featuredetection.h"

#define ROITolerance 50 //toleransen för beskärningen.

Featuredetection::Featuredetection()
{
    this->cascade = (CvHaarClassifierCascade*)cvLoad( "../../../../../opencv/data/haarcascades/haarcascade_frontalface_alt.xml", 0, 0, 0 );
    this->cascade_eye = (CvHaarClassifierCascade*)cvLoad( "../../../../../opencv/data/haarcascades/haarcascade_eye.xml", 0, 0, 0 );
    this->storage = cvCreateMemStorage(0);
    this->storage2 = cvCreateMemStorage(0);
}

CvSeq * Featuredetection::GetFaces(IplImage* img, CvHaarClassifierCascade * cascade, CvMemStorage* storage, CvRect* old_face)
{
    CvSeq* faces;
    CvRect Size;


    if(old_face->x == -1)
    {
REDO:
        cvResetImageROI(img);
        faces = cvHaarDetectObjects( img, cascade, storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) ); //om det gamla ansiktet är oanvändbart, analysera hela bilden.

        cvClearMemStorage(storage);
        return faces;
    }
    else
    {

        Size = cvRect(old_face->x - ROITolerance,old_face->y - ROITolerance,old_face->width+ROITolerance* 2,old_face->height + ROITolerance *2);

        cvSetImageROI(img,Size);

        faces = cvHaarDetectObjects( img, cascade, storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) ); //om föregående ansikte är användbart börja med att genomsök föregående ansikte + en thersh

        if(faces->total == 0)
        {
            cvClearSeq(faces);
            goto REDO; //om det inte gunkade genomsök hela bilden;
        }
        cvClearMemStorage(storage);
        return faces;
    }

}


int Featuredetection::detectface (IplImage* img, CvRect* face, CvRect* old_face){
    int i;
    CvSeq* faces;

    if( !this->cascade )
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
    }else{

        faces = GetFaces(img,this->cascade,this->storage,old_face); //sköter ansiktssökningen.

        if (old_face->x==-1){


            for( i = 0; i < (faces ? faces->total : 0); i++ )
            {

                CvRect*r= (CvRect*)cvGetSeqElem( faces, i );



                cvSetImageROI(img,cvRect(r->x,r->y,r->width,r->height*3/5));
                storage2 = cvCreateMemStorage(0);
                CvSeq* eyes = cvHaarDetectObjects( img, this->cascade_eye, this->storage2,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) );
                cvResetImageROI(img);
                if (1<eyes->total){



                    printf("Hittade ett ansikte innom gränsen\n");

                    *face = *r;
                    cvClearMemStorage(this->storage);
                    cvClearMemStorage(this->storage2);
                    cvResetImageROI(img);
                    cvClearSeq(faces);
                    return 1;

                }
            }
        }else{
            for( i = 0; i < (faces ? faces->total : 0); i++ )
            {
                // Create a new rectangle for drawing the face
                CvRect*r= (CvRect*)cvGetSeqElem( faces, i );

                r->x += img->roi->xOffset;
                r->y += img->roi->yOffset;


                if(abs(r->x-old_face->x)<50 && abs(r->y-old_face->y)<50)
                {
                    if(abs(r->width-old_face->width)<50 && abs(r->height-old_face->height)<50 )
                    {
                        printf("Hittade ett ansikte innom gränsen\n");
                        *face = *r;
                        cvClearMemStorage(this->storage);
                        cvClearMemStorage(this->storage2);
                        cvResetImageROI(img);
                        cvClearSeq(faces);
                        return 1;
                    }
                }
                printf("Felaktigt ansikte");

            }
        }

    }

    cvClearMemStorage(this->storage);
    cvClearMemStorage(this->storage2);
    cvResetImageROI(img);
    cvClearSeq(faces);
    return -1;
}

int Featuredetection::detectEye (IplImage* img,CvPoint roi, CvRect* eyes, Facefeatures* old_face){
    int i;
    CvSeq* faces;



    if( !this->cascade_eye )
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
    }else{


        try
        {
            faces = cvHaarDetectObjects( img, this->cascade_eye, this->storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) ); //blev konstigt ibland så fick prova en try cath sats för att ta reda på felet.
        }
        catch(exception e)
        {
            printf("exception i eye");
            return -2; //ibland får man  OpenCV Error: Incorrect size of input array (Non-positive cols or rows) in cvInitMatHeader, file /home/madde/AI/opencv/modules/core/src/array.cpp, line 146

        }

        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
            // Create a new rectangle for drawing the face
            CvRect*r = (CvRect*)cvGetSeqElem( faces, i );
            *eyes=*r;

            eyes->x=r->x+roi.x;
            eyes->y=r->y+roi.y;

            // Find the dimensions of the face,and scale it if necessary
            cvClearMemStorage( this->storage );
            cvClearSeq(faces);
            return 1;
        }
    }

    cvClearMemStorage(this->storage);
    cvClearSeq(faces);
    return -1;
}


Facefeatures* Featuredetection::detectfeatures(IplImage* img, Facefeatures* old_face){
    Facefeatures head;


    if(0>detectface(img,&head.mFace,&old_face->mFace)){                   // mindre än noll för fel medelanden istället för -1
        fprintf( stderr, "Could not locate head\n" );
        head.mFace.x = -1;
        return &head;
    }else{
        head.mRightEye = cvRect(head.mFace.x +head.mFace.width/2 - head.mFace.width/15 - head.mFace.width/3.5,head.mFace.y + head.mFace.height/4.8 ,head.mFace.width/3.5,head.mFace.height*3/5 - head.mFace.height/3.5);
        head.mLeftEye = cvRect(head.mFace.x+head.mFace.width/2 + head.mFace.width/15,head.mFace.y + head.mFace.height/4.8,head.mFace.width/3.5,head.mFace.height*3/5 - head.mFace.height/3.5);
        return &head;
    }
}
