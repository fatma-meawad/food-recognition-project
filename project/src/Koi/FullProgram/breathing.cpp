#include "breathing.h"

Breathing::Breathing()
{
    this->pos=0;
    this->prev=-1;
    this->avg=-1;
}

IplImage* preprocess(IplImage* img){
    CvMemStorage* 	g_storage = NULL;
    IplImage* gray;
    gray = cvCreateImage( cvGetSize( img ), 8, 1 );
    g_storage = cvCreateMemStorage(0);
    cvClearMemStorage( g_storage );
    CvSeq* contours = 0;

    cvCvtColor( img, gray, CV_BGR2GRAY );
    cvThreshold( gray, gray, 100, 255, CV_THRESH_BINARY );
    cvFindContours( gray, g_storage, &contours );
    IplImage* dst = cvCreateImage( cvGetSize(img), 8, 3 );
    cvZero( dst );
    if( contours ){

        cvDrawContours(dst,contours,cvScalarAll(255),cvScalarAll(255),100 );
    }

    return dst;

}






int Breathing::getdistance(IplImage* img, Facefeatures* face){
    IplImage* contour;
    contour=preprocess(img);
    int i=0;
    //int a;
    //int b;
    //int count=0;
    CvScalar pixel;
    CvPoint startpos=cvPoint(face->mFace.x,face->mFace.y+face->mFace.height*1.2);


    cvLine(contour, cvPoint(startpos.x-2,startpos.y+40), cvPoint(startpos.x+2,startpos.y+40), cvScalar(255,255,255), 1);
    while(startpos.y+i<contour->height){

        pixel = cvGetAt(contour,startpos.y+i,startpos.x);

        //cout << cvGetReal2D(contour,startpos.x,startpos.y+i)     << " i " << i << " y " << startpos.y << endl;
        //cout << pixel.val[0] << endl;
        cout << pixel.val[0]<<" "<<pixel.val[1] << " i " << i << " y " << startpos.y << endl;
        if(pixel.val[0]>100 )
        {
            break;
        }
        i++;

    }


    int svar=startpos.y+i;;//-face->mFace.height/2-face->mFace.y;
    cvLine(contour, cvPoint(startpos.x-10,startpos.y+i), cvPoint(startpos.x+10,startpos.y+i), cvScalar(255,255,255), 1);
    cvLine(contour, startpos, cvPoint(startpos.x,startpos.y+100), cvScalar(255,255,255), 1);
    cvShowImage( "Contours", contour );
    cvReleaseImage(&contour);
    return svar;

}

int Breathing::isBreathing(IplImage* img, Facefeatures* face){
    int b;
    int a = getdistance(img,face);
    if (this->pos<200){
        this->list[this->pos]=a;
        this->pos++;
        return -1;
    }else{
        if(this->pos==400){
            this->pos-=200;
        }
        b=this->list[this->pos-200];
        this->list[this->pos-200]=a;
        this->pos++;

        if (this->avg==-1){
            int i;
            for(i=0;i<200;i++){
                this->avg+=this->list[i];
            }
        }else{
            avg=avg-b+a;
        }
        if (a*200>this->avg){
            return 0;
        }else{
            return 1;
        }

    }



}

