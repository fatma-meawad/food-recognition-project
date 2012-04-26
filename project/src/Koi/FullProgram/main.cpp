#include "Includes.h"

int main(int argc, char *argv[])
{
    Videocapture VC;
    VC.Init(CV_CAP_ANY);

    cvNamedWindow("asd",CV_WINDOW_AUTOSIZE);

    //cvWaitKey(0);

    while(true)
    {
        VC.UpdateFrame();
        Preprocessing::MakeGrayscale(VC.CurrentFrame);
        cvShowImage("asd",VC.CurrentFrame);

        if(cvWaitKey(15) == 27)
                break;
    }

}
