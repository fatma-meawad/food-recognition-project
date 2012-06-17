#include "pulse.h"

int Pulse::pulseValue(IplImage* img, Facefeatures* face){
    Preprocessing p;
    int i;
    int j;
    int redness=0;
    CvScalar pixel;
    CvRect test;
    IplImage * bild= p.MakeHSV(img);
    test=cvRect(face->mRightEye.x+face->mRightEye.width*3/10,face->mRightEye.y+face->mRightEye.height*9/10,face->mRightEye.width*3.5/10,face->mRightEye.height*7/10);
    cvSetImageROI(bild,test);
    for(i=0;i<bild->roi->width;i++)
    {
        for(j=0;i<bild->roi->height;i++)
        {
            pixel = cvGetAt(bild,i,j);
            redness+=pixel.val[0]*100;
        }
    }
    //cvShowImage("Test 1", img);
    cvResetImageROI(bild);
    test=cvRect(face->mLeftEye.x+face->mLeftEye.width-face->mLeftEye.width*3.5/10-face->mLeftEye.width*3/10,face->mLeftEye.y+face->mLeftEye.height*9/10,face->mRightEye.width*3.5/10,face->mRightEye.height*7/10);
    cvSetImageROI(bild,test);
    for(i=0;i<bild->roi->width;i++)
    {
        for(j=0;i<bild->roi->height;i++)
        {
            pixel = cvGetAt(bild,i,j);
            redness+=pixel.val[0]*100;
        }
    }
    //cvShowImage("Test 2", img);
    redness=redness/(bild->roi->width*bild->roi->height*2);
    cvResetImageROI(bild);
    printf("Redness: %d\n",redness);
    return redness;
}

/*
CHANGES IN MAIN IN ORDER TO RUN

int redvalLen=100;


if(redvalLen==100){
    img=cvCreateImage(cvSize(1400,800),IPL_DEPTH_8U,VC.CurrentFrame->nChannels);
    cvZero(img);
    cvNot(img,img);
    redvalLen=0;
}
redvalLen++;
paint.drawCircle(img,cvPoint(redvalLen*12,(800-p.pulseValue(VC.CurrentFrame,pFace))),2,-1);

cvShowImage("Fake graf",img);
*/
