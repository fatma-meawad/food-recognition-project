#include "Includes.h"

int main(int argc, char *argv[])
{
    Videocapture VC;
    Facefeatures* pFace;
    Facefeatures face;
    Blinking Blinker;
    Facefeatures old_face;
    old_face.mFace.x=-1;   // says that there is no old face at start
    pFace = &face;
    int redvalLen=100;
    IplImage* img;
    Featuredetection f;
    Breathing Breath;
    Painting paint;
    Data d1;
    Blinkfreq freq;

    timeval start, stop;

    if(argc == 1)
    {
        if(VC.Init(CV_CAP_ANY) < 0)
        {
            return -1;
            std::cout << "Error capture == NULL";
        }
    }
    else
        VC.InitAVI(argv[1]);

    d1.timeStamp = 0;
    //paint.drawInit(&paint);

    while(true)
    {
        gettimeofday(&start, NULL);

        VC.UpdateFrame();

        pFace = f.detectfeatures(VC.CurrentFrame,&old_face);

        if(pFace->mFace.x != -1)
        {
            old_face=*pFace;

            if(redvalLen==100){                                                                                     //plotting graph
                img=cvCreateImage(cvSize(1400,800),IPL_DEPTH_8U,VC.CurrentFrame->nChannels);
                cvZero(img);
                cvNot(img,img);
                redvalLen=0;
            }
            redvalLen++;
            paint.drawCircle(img,cvPoint(redvalLen*12,(Breath.isBreathing(VC.CurrentFrame,pFace)+2)*200),2,-1);
            cvShowImage("Fake graf",img);                                                                              //finished plotting graph


            freq.AddState(Blinker.Analyze(VC.CurrentFrame,old_face.mRightEye));

            //cout << "Freq: " << freq.Analyze() << endl;

            paint.drawFullFace(VC.CurrentFrame,&old_face);  // Paint test
        }

        cvShowImage("asd",VC.CurrentFrame);
        //cvMoveWindow("asd", 700, 200);

        // Free memory
        cvReleaseImage(&VC.CurrentFrame);

        if(cvWaitKey(1) == 27)
            break;

        gettimeofday(&stop, NULL);
        //cout << "FPS: " << 1000/(((stop.tv_sec - start.tv_sec)* 1000 + (stop.tv_usec - start.tv_usec)/1000.0) + 0.5) << endl;
    }

    //cvDestroyWindow("asd");

}
