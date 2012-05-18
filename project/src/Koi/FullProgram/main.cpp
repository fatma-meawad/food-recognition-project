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

    Featuredetection f;

    Painting paint;
    Data d1;

    timeval start, stop;


//    qDebug() << QImageReader::supportedImageFormats();

    if(argc == 1)
    {
        //VC.Init(CV_CAP_ANY);
        if(VC.Init(CV_CAP_ANY) < 0)
        {
            return -1;
            std::cout << "Error capture == NULL";
        }
    }
    else
        VC.InitAVI(argv[2]);

  /*  for(int i = 0; i < 10; i++){
        d1.timeStamp = (double) gettimeofday(&stop, NULL);
        d1.blinkingfreq =  (int)gettimeofday(&stop, NULL)/123;
        d1.breathingfreq = i+1;
        d1.pulsefreq = i-1;

        paint.mData.push_back();
    }
*/

    d1.timeStamp = 0;
    paint.drawInit(&paint);


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

            Blinker.Analyze(VC.CurrentFrame,old_face.mRightEye,old_face.mLeftEye);

            paint.drawFullFace(VC.CurrentFrame,&old_face);  // Paint test
            d1.blinkingfreq = 1000/(((stop.tv_sec - start.tv_sec)* 1000 + (stop.tv_usec - start.tv_usec)/1000.0) + 0.5);
            d1.timeStamp++;
            //paint.mData.push_back(d1);

        }




         //paint.drawGraph();
         cvShowImage("asd",VC.CurrentFrame);
         cvMoveWindow("asd", 700, 200);

         // Free memory
         cvReleaseImage(&VC.CurrentFrame);

        if(cvWaitKey(1) == 27)
            break;

        gettimeofday(&stop, NULL);
        //cout << "FPS: " << 1000/(((stop.tv_sec - start.tv_sec)* 1000 + (stop.tv_usec - start.tv_usec)/1000.0) + 0.5) << endl;
    }

    //cvDestroyWindow("asd");

}
