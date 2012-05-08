#include "Includes.h"

int main(int argc, char *argv[])
{
    Videocapture VC;
    Facefeatures face;
    Facefeatures old_face;
    old_face.mFace.x=-1;   // säger att old_face inte är användbar;
    VC.Init(CV_CAP_ANY);
    Preprocessing p;
    Featuredetection f;
    IplImage * temp;

    Painting paint;
    Data d1;

    timeval start, stop;


    for(int i = 0; i < 10; i++){
        d1.timeStamp = (double)i/10; d1.blinkingfreq = i;
        d1.breathingfreq = i+1; d1.pulsefreq = i-1;

        paint.mData.push_back(d1);
    }

    paint.drawInit(&paint);
    paint.drawGraph();



    cvNamedWindow("asd",CV_WINDOW_AUTOSIZE);

    //cvWaitKey(0);

    while(true)
    {
        gettimeofday(&start, NULL);

        VC.UpdateFrame();
        // Preprocessing::MakeGrayscale(VC.CurrentFrame);

        face = f.detectfeatures(VC.CurrentFrame,old_face);
        old_face=face;

        paint.drawFullFace(VC.CurrentFrame,&face);  // Paint test

        temp = p.Stabilize(VC.CurrentFrame, &face);

        cvShowImage("asd",temp);

        if(cvWaitKey(5) == 27)
            break;

        gettimeofday(&stop, NULL);
        cout << "FPS: " << 1000/(((stop.tv_sec - start.tv_sec)* 1000 + (stop.tv_usec - start.tv_usec)/1000.0) + 0.5) << endl;
    }

    cvDestroyWindow("asd");

}
