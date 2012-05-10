#include "Includes.h"

int main(int argc, char *argv[])
{
    Videocapture VC;
    Facefeatures* pFace;
    Facefeatures face;
    Blinking Blinker;
    Facefeatures old_face;
    old_face.mFace.x=-1;   // säger att old_face inte är användbar;
    pFace = &face;

    Preprocessing p;
    Featuredetection f;
    IplImage * temp;

    Painting paint;
    Data d1;

    timeval start, stop;

    if(argc == 1)
        VC.Init(CV_CAP_ANY);
    else
        VC.InitAVI(argv[2]);

    for(int i = 0; i < 10; i++){
        d1.timeStamp = (double)i/10; d1.blinkingfreq = i;
        d1.breathingfreq = i+1; d1.pulsefreq = i-1;

        paint.mData.push_back(d1);
    }

    //paint.drawInit(&paint);
    //paint.drawGraph();

    //cvNamedWindow("asd",CV_WINDOW_AUTOSIZE);

    //cvWaitKey(0);

    while(true)
    {
        gettimeofday(&start, NULL);

        VC.UpdateFrame();

        pFace = f.detectfeatures(VC.CurrentFrame,&old_face);
        if(pFace->mFace.x != -1)
        {
            old_face=*pFace;

            temp = p.Stabilize(VC.CurrentFrame, &old_face);

            Blinker.Analyze(VC.CurrentFrame,old_face.mRightEye,old_face.mLeftEye);

            paint.drawFullFace(VC.CurrentFrame,&old_face);  // Paint test

            cvShowImage("asd",VC.CurrentFrame);
        }
        if(cvWaitKey(5) == 27)
            break;

        gettimeofday(&stop, NULL);
        cout << "FPS: " << 1000/(((stop.tv_sec - start.tv_sec)* 1000 + (stop.tv_usec - start.tv_usec)/1000.0) + 0.5) << endl;
    }

    //cvDestroyWindow("asd");

}
