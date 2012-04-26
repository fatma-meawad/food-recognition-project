
#include "videodetection.h"
#include "videocapture.h"
#include "Includes.h"

int main(int argc, char *argv[])
{

    videodetection VD;

   // videocapture VC;
   // VC.Init(0);
    VD.Init(0);

    VD.InitFace();

    cvNamedWindow("asd",CV_WINDOW_AUTOSIZE);

    //cvWaitKey(0);

    while(true)
    {
        VD.UpdateFrame();
       // VC.UpdateFrame();
        cvShowImage("asd",VD.CurrentImage);

        if(cvWaitKey(15) == 27)
                break;
    }

}
