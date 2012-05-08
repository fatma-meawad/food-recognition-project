#include "blinking.h"

Blinking::Blinking()
{
}



int Blinking::Init()
 {
    return 1;
}

int CalcPixels(IplImage * inputImage)
{
    int pixelgray = 0;
    CvScalar pixel;
    IplImage * input = Preprocessing::MakeGrayscale(inputImage);

    for(int i = 0; i < inputImage->height; i++)
    {
        for(int j = 0; j < inputImage->width; j++)
        {
            pixel = cvGetAt(input,i,j);
            pixelgray += pixel.val[0];
        }
    }

    return pixelgray;


}

int Blinking::Analyze(IplImage* inputimage, CvRect righteye, CvRect lefteye)
{
    CvRect REImage, LEImage;
 //   IplImage * RightEye, LeftEye;
    int UpperRE , LowerRE,UpperLE,LowerLE;


    if(righteye.x != -1)
    {
        REImage = righteye;

        LowerRE = CalcPixels(Preprocessing::Crop(righteye,inputimage));  //calculate the lower grayscale pixels, the eye for the right;

        REImage.y = std::min(0,REImage.y - REImage.height); //move it upwards one height max to 0 though

        UpperRE = CalcPixels(Preprocessing::Crop(righteye,inputimage));  //calculate the lower grayscale pixels, the eyelid for the right;

        if(LowerRE - UpperRE > blinkingthreshold)
            std::cout << "right eye closed";
    }

    if(lefteye.x != -1)
    {
        LEImage = lefteye;

        LowerLE = CalcPixels(Preprocessing::Crop(lefteye,inputimage));

        LEImage.y = std::min(0,LEImage.y - LEImage.height);

        UpperLE = CalcPixels(Preprocessing::Crop(lefteye,inputimage));

        if(LowerLE - UpperLE > blinkingthreshold)
            std::cout << "left eye closed";
    }


    return 1;


  //  REImage.height += REImage.height;
  //  LEImage.height += LEImage.height;

   // RightEye = Preprocessing::Crop(REImage,inputimage);
   // LeftEye = Preprocessing::Crop(LEImage,inputimage);

}


