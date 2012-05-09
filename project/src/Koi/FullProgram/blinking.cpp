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

    return pixelgray/(inputImage->imageSize);


}

int Blinking::Analyze(IplImage* inputimage, CvRect righteye, CvRect lefteye)
{
    CvRect REImage, LEImage;
 //   IplImage * RightEye, LeftEye;
    int UpperRE , LowerRE,UpperLE,LowerLE;


    if(righteye.x != -1)
    {
        REImage = righteye;

        LowerRE = CalcPixels(Preprocessing::Crop(REImage,inputimage));  //calculate the lower grayscale pixels, the eye for the right;

        REImage.y = std::max(0,REImage.y - REImage.height); //move it upwards one height max to 0 though

        UpperRE = CalcPixels(Preprocessing::Crop(REImage,inputimage));  //calculate the lower grayscale pixels, the eyelid for the right;

        if(UpperRE - LowerRE < blinkingthreshold)
            std::cout << "left eye closed, value: " << UpperRE - LowerRE << endl;
    }

    if(lefteye.x != -1)
    {
        LEImage = lefteye;

        LowerLE = CalcPixels(Preprocessing::Crop(LEImage,inputimage));
       // std::cout << "LOW: " << LowerLE << endl;

        cvShowImage("Before",Preprocessing::MakeGrayscale(Preprocessing::Crop(LEImage,inputimage)));
        cvMoveWindow("Before", 500, 50);

        LEImage.y = std::max(0,LEImage.y - LEImage.height);

        cvShowImage("After",Preprocessing::MakeGrayscale(Preprocessing::Crop(LEImage,inputimage)));
        cvMoveWindow("After", 600, 50);

        UpperLE = CalcPixels(Preprocessing::Crop(LEImage,inputimage));
        //std::cout << "UPP: " << UpperLE << endl;
        //std::cout << "DIFF: " << UpperLE - LowerLE << std::endl;
        if(UpperLE -LowerLE < blinkingthreshold)
            std::cout << "right eye closed, value: " << UpperLE - LowerLE << endl;
    }


    return 1;


  //  REImage.height += REImage.height;
  //  LEImage.height += LEImage.height;

   // RightEye = Preprocessing::Crop(REImage,inputimage);
   // LeftEye = Preprocessing::Crop(LEImage,inputimage);

}


