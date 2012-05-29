#include "featuredetection.h"

#define ROITolerance 50 //toleransen för beskärningen.

Featuredetection::Featuredetection()
{
    this->cascade = (CvHaarClassifierCascade*)cvLoad( "../../../../../opencv/data/haarcascades/haarcascade_frontalface_alt.xml", 0, 0, 0 );
    if( !this->cascade )
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
    }
    this->cascadeEye = (CvHaarClassifierCascade*)cvLoad( "../../../../../opencv/data/haarcascades/haarcascade_eye.xml", 0, 0, 0 );
    if( !this->cascade )
    {
        fprintf( stderr, "ERROR: Could not load classifier cascadeEye\n" );
    }
    this->storage = cvCreateMemStorage(0);
    this->storage2 = cvCreateMemStorage(0);
}

CvSeq * Featuredetection::GetFaces(IplImage* img, CvRect* oldFace)  //function that finds the faces
{
    CvSeq* faces;
    CvRect Size;


    if(oldFace->x == -1)   //if previouse face was undefined then search the whole picture
    {
        cvResetImageROI(img);
        faces = cvHaarDetectObjects( img, this->cascade, this->storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) ); //search the whole picture, and return results
        cvClearMemStorage(this->storage);
        return faces;
    }
    else    //if previouse face was defined
    {

        Size = cvRect(oldFace->x - ROITolerance,oldFace->y - ROITolerance,oldFace->width+ROITolerance* 2,oldFace->height + ROITolerance *2);

        cvSetImageROI(img,Size);        //set a roi around where the previouse face to start seaching

        faces = cvHaarDetectObjects( img, this->cascade, this->storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) ); // then search for a face in that region

        if(faces->total == 0)
        {
            cvClearSeq(faces);
            cvResetImageROI(img);
            faces = cvHaarDetectObjects( img, this->cascade, this->storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) ); //om det gamla ansiktet är oanvändbart, analysera hela bilden.
            cvClearMemStorage(this->storage);
            return faces;
        }
        cvClearMemStorage(this->storage);
        return faces;
    }

}


int Featuredetection::detectface (IplImage* img, CvRect* face, CvRect* oldFace){
    int i;
    CvSeq* faces;


    faces = GetFaces(img,oldFace); //call function which searches for faces
    if (oldFace->x==-1)
    {           //if previouse picture was undefined

        for( i = 0; i < faces->total; i++ )     //loop threw every face untill a propper one is found
        {

            CvRect*r= (CvRect*)cvGetSeqElem( faces, i );        //pick up a element

            cvSetImageROI(img,cvRect(r->x,r->y,r->width,r->height*3/5));        //picks out the region around the eyes to varify that the head has eyes to varify the face abit more accurate
            storage2 = cvCreateMemStorage(0);
            CvSeq* eyes = cvHaarDetectObjects( img, this->cascadeEye, this->storage2,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) );        //searhes for the eyes
            cvResetImageROI(img);
            if (1<eyes->total){            //if it fins more than 1 eye then it sets that face into the face variable, clears the memory and returns the value of it

                *face = *r;
                cvClearMemStorage(this->storage);
                cvClearMemStorage(this->storage2);
                cvResetImageROI(img);
                cvClearSeq(faces);
                return 1;

            }
        }
    }
    else            //if previouse face was defined
    {
        for( i = 0; i < faces->total; i++ )     //loop threw every face
        {
            // Create a new rectangle for drawing the face
            CvRect*r= (CvRect*)cvGetSeqElem( faces, i ); //pick out a element
            if(img->roi)            // if roi is true then the points where found on a picture with roi active and compensation is aplied
            {
                r->x += img->roi->xOffset;
                r->y += img->roi->yOffset;
            }

            if(abs(r->x-oldFace->x)<50 && abs(r->y-oldFace->y)<50)        // compares it with the position of the oldFace which is the value from the previouse picture, aswell as width and height
            {
                if(abs(r->width-oldFace->width)<50 && abs(r->height-oldFace->height)<50 )
                {
                    *face = *r;
                    cvClearMemStorage(this->storage);
                    cvClearMemStorage(this->storage2);
                    cvResetImageROI(img);
                    cvClearSeq(faces);
                    return 1;
                }
            }
        }
    }



    cvClearMemStorage(this->storage);       //if no propper face was found clear mem storage and return -1 which means no face detected
    cvClearMemStorage(this->storage2);
    cvResetImageROI(img);
    cvClearSeq(faces);
    return -1;
}

// detect eye removed can be found in revision 89 or earlier


Facefeatures* Featuredetection::detectfeatures(IplImage* img, Facefeatures* oldFace){
    Facefeatures* head= new Facefeatures;
    if(0>detectface(img,&head->mFace,&oldFace->mFace)){                   //function that checks for "propper" faces, if such a face is found the function returns a number above 0 and a head object, if not then a number bellow 0
        fprintf( stderr, "Could not locate head\n" );                   // if no propper face was found then faces gets set to its undefined value at head->mFace.x = -1; and returns the head with the bad information.
        head->mFace.x = -1;
        return head;
    }else{
        head->mRightEye = cvRect(head->mFace.x +head->mFace.width/2 - head->mFace.width/15 - head->mFace.width/3.5,head->mFace.y + head->mFace.height/4.8 ,head->mFace.width/3.5,head->mFace.height*3/5 - head->mFace.height/3.5);        // using symmetry to place out the regions for the eyes using the symmetry of the face
        head->mLeftEye = cvRect(head->mFace.x+head->mFace.width/2 + head->mFace.width/15,head->mFace.y + head->mFace.height/4.8,head->mFace.width/3.5,head->mFace.height*3/5 - head->mFace.height/3.5);
        return head;
    }
}
