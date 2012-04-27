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

    cvNamedWindow("asd",CV_WINDOW_AUTOSIZE);

    //cvWaitKey(0);

    while(true)
    {
        VC.UpdateFrame();
       // Preprocessing::MakeGrayscale(VC.CurrentFrame);

       face = f.detectfeatures(VC.CurrentFrame,old_face);
       old_face=face;

       Painting::drawFullFace(VC.CurrentFrame,&face);  // Paint test

      // cvDrawRect(VC.CurrentFrame,cvPoint(face.mFace.x,face.mFace.y),cvPoint(face.mFace.x + face.mFace.width,face.mFace.y + face.mFace.height),cvScalar(0x00,0x00,0x00),1,8,0);

        //temp = p.Stabilize(VC.CurrentFrame, &face);
        cvShowImage("asd",VC.CurrentFrame);

        if(cvWaitKey(5) == 27)
                break;
    }

}
