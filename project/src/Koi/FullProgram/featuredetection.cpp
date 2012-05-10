#include "featuredetection.h"

#define ROITolerance 100 //toleransen för beskärningen.

Featuredetection::Featuredetection()
{
    this->lock = false;

    this->cascade = (CvHaarClassifierCascade*)cvLoad( "../../../../../opencv/data/haarcascades/haarcascade_frontalface_alt.xml", 0, 0, 0 );
    this->cascade_eye = (CvHaarClassifierCascade*)cvLoad( "../../../../../opencv/data/haarcascades/haarcascade_eye.xml", 0, 0, 0 );
}

CvSeq* GetFeatures(IplImage* img, CvHaarClassifierCascade * cascade, CvMemStorage* storage)
{
    return cvHaarDetectObjects( img, cascade, storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) );
}

CvSeq* Compensate(CvSeq * sequence, int x ,int y)
{
    CvMemStorage* storage;
    CvRect* r = 0;

    storage = cvCreateMemStorage(0); //fixar kompenseringen

    CvSeq* ReturnSequence = cvCreateSeq(0,sizeof(CvSeq),sizeof(CvRect*),storage);

    for(int i = 0; i < sequence->total; i++ )
    {
        r = (CvRect*)cvGetSeqElem( sequence, i );
        r->x += (x - (ROITolerance/2));
        r->y += (y - (ROITolerance/2));
        //cvSeqPush(ReturnSequence,r);
    }

    return ReturnSequence;
}

CvSeq * GetFaces(IplImage* img, CvHaarClassifierCascade * cascade, CvMemStorage* storage, CvRect old_face)
{
    CvSeq* faces;
    IplImage * temp;
    CvRect Size;

    if(old_face.x == -1)
    {
REDO:
        faces = cvHaarDetectObjects( img, cascade, storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) ); //om det gamla ansiktet är oanvändbart, analysera hela bilden.
        goto CONT;
    }
    else
    {
        Size = cvRect(old_face.x - ROITolerance/2,old_face.y - ROITolerance/2,old_face.width+ROITolerance,old_face.height + ROITolerance);

        temp = Preprocessing::Crop(Size,img);

        faces = cvHaarDetectObjects( temp, cascade, storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) ); //om föregående ansikte är användbart börja med att genomsök föregående ansikte + en thersh
        faces = Compensate(faces,old_face.x,old_face.y);  //kompensera för beskärningen.
        if(faces->total == 0)
        {

            goto REDO; //om det inte gunkade genomsök hela bilden;
        }
    }


CONT:
    return faces;

}


int Featuredetection::detectface (IplImage* img, CvRect* face, CvRect* old_face){
    int i;
    static CvMemStorage* storage = 0;
    static CvMemStorage* storage2 = 0;
    CvSeq* faces;

    storage = cvCreateMemStorage(0);
    if( !this->cascade )
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
    }else{

        faces = GetFaces(img,this->cascade,storage,*old_face); //sköter ansiktssökningen.

        if (old_face->x==-1){


            for( i = 0; i < (faces ? faces->total : 0); i++ )
            {

                CvRect*r= (CvRect*)cvGetSeqElem( faces, i );



                cvSetImageROI(img,cvRect(r->x,r->y,r->width,r->height*3/5));
                storage2 = cvCreateMemStorage(0);
                CvSeq* eyes = cvHaarDetectObjects( img, this->cascade_eye, storage2,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) );
                cvResetImageROI(img);
                if (1<eyes->total){



                    printf("Hittade ett ansikte innom gränsen\n");
                    *face = *r;
                    cvClearMemStorage(storage); // ##### Varför kastade du ansiktet om du inte hittade ögon?
                    cvClearMemStorage(storage2);
                    return 1;






                }
            }
        }else{
            for( i = 0; i < (faces ? faces->total : 0); i++ )
            {
                // Create a new rectangle for drawing the face
                CvRect*r= (CvRect*)cvGetSeqElem( faces, i );
                //if(Preprocessing::Pointdistance(cvPoint(old_face.x,old_face.y),cvPoint(r->x,r->y)) < 20 || old_face.x==-1 )
                if(abs(r->x-old_face->x)<50 && abs(r->y-old_face->y)<50)
                {
                    if(abs(r->width-old_face->width)<50 && abs(r->height-old_face->height)<50 ){
                        printf("Hittade ett ansikte innom gränsen\n");
                        *face = *r;
                        cvClearMemStorage(storage);
                        return 1;
                    }
                }
                printf("Felaktigt ansikte");

            }
        }

    }
    return -1;
}

int Featuredetection::detectEye (IplImage* img,CvPoint roi, CvRect* eyes, Facefeatures* old_face){
    int i;
    CvSeq* faces;
    static CvMemStorage* storage = 0;
    storage = cvCreateMemStorage(0);
    if( !this->cascade_eye )
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
    }else{


        try
        {
            faces = cvHaarDetectObjects( img, this->cascade_eye, storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) ); //blev konstigt ibland så fick prova en try cath sats för att ta reda på felet.
        }
        catch(exception e)
        {
            printf("exception i eye");
            return -2; //ibland får man  OpenCV Error: Incorrect size of input array (Non-positive cols or rows) in cvInitMatHeader, file /home/madde/AI/opencv/modules/core/src/array.cpp, line 146

        }

        //  CvSeq* faces = cvHaarDetectObjects( img, cascade, storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) );

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


Facefeatures* Featuredetection::detectfeatures(IplImage* img, Facefeatures* old_face){
    Facefeatures head;
    CvPoint A;
    if(0>detectface(img,&head.mFace,&old_face->mFace)){                   // mindre än noll för fel medelanden istället för -1
        fprintf( stderr, "Could not locate head\n" );
        //head.mFace.x = -1;
        head=*old_face;                                                  // om inget huvud hittas antar vi att det är på samma ställe som förra gången.
        return &head;
    }else{
        //cvShowImage("result", img);

        //printf("Huvudets övre högra punkt är i X: %i och i Y: %i , Bredden: %i  och höjden  %i\n",head.mFace.x,head.mFace.y,head.mFace.width,head.mFace.height);
        cvSetImageROI(img,cvRect(head.mFace.x,head.mFace.y,head.mFace.width/2,head.mFace.height*3/5));
        //cvShowImage("result", img);
        A.x=head.mFace.x;
        A.y=head.mFace.y;
        if (detectEye(img,A,&head.mLeftEye,old_face)==-1){
            head.mLeftEye=old_face->mLeftEye;
        }
        cvResetImageROI(img);
        cvSetImageROI(img,cvRect(head.mFace.x+head.mFace.width/2,head.mFace.y,head.mFace.width/2,head.mFace.height*3/5));
        A.x=head.mFace.x+head.mFace.width/2;
        A.y=head.mFace.y;
        if (detectEye(img,A,&head.mRightEye,old_face)==-1){
            head.mRightEye=old_face->mRightEye;
        }
        cvResetImageROI(img);


        cvRectangleR( img, head.mFace, CV_RGB(255,0,0), 3, 8, 0 );
        cvRectangleR( img, head.mLeftEye, CV_RGB(0,255,0), 3, 8, 0 );
        cvRectangleR( img, head.mRightEye, CV_RGB(0,0,255), 3, 8, 0 );
        //cvShowImage("result", img);
    }

    //cvShowImage("result", img);
    return &head;

}
