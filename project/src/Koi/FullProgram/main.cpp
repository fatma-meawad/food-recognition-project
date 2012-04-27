#include "Includes.h"




int main(int argc, char *argv[])
{
    Videocapture VC;
    Facefeatures face;
    VC.Init(CV_CAP_ANY);
    Preprocessing p;
    Featuredetection f;
    IplImage * temp;

    cvNamedWindow("asd",CV_WINDOW_AUTOSIZE);

    //cvWaitKey(0);

    while(true)
    {
        VC.UpdateFrame();
       // Preprocessing::MakeGrayscale(VC.CurrentFrame);

       face = f.detectfeatures(VC.CurrentFrame);


      // cvDrawRect(VC.CurrentFrame,cvPoint(face.mFace.x,face.mFace.y),cvPoint(face.mFace.x + face.mFace.width,face.mFace.y + face.mFace.height),cvScalar(0x00,0x00,0x00),1,8,0);

        temp = p.Stabilize(VC.CurrentFrame, &face);
        cvShowImage("asd",temp);

        if(cvWaitKey(5) == 27)
                break;
    }

}
