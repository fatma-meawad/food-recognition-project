#include "Includes.h"

int main(int argc, char *argv[])
{
    videocapture VC;
    VC.Init(ANY_CAM);

    cvNamedWindow("asd",CV_WINDOW_AUTOSIZE);

    //cvWaitKey(0);

    while(true)
    {
        VC.UpdateFrame();
        cvShowImage("asd",VD.CurrentImage);

        if(cvWaitKey(15) == 27)
                break;
    }

}
