#include "blinking.h"



int Blinking::Init()
{
    return 1;
}

bool CalcPixels(IplImage * inputImage)
{
    CvScalar pixel;
    IplImage * input = cvCreateImage(cvSize(inputImage->width,inputImage->height),IPL_DEPTH_8U,inputImage->nChannels);
    input = Preprocessing::MakeGrayscale(inputImage);

    int totX = 0;
    int area = 0;
    bool clear;
    bool closed;

    for(int j = input->height/3; j < input->height*2/3; j++)
    {
        clear = true;
        for(int i = input->width*2/4; i < input->width; i++)
        {
            pixel = cvGetAt(input,j,i);
            if(pixel.val[0] != 255)
            {
                clear = false;
                area++;
            }
        }

        if(clear)
            totX++;
    }

    //std::cout << "Height: " << input->height/10 << ", Total lines: " << totX << ", Area: " << (double)area/((input->width/2)*(input->height/3)) << "     ";

    if((totX - 1 > (input->height)/10  || (double)area/((input->width/2)*(input->height/3)) < 0.2))
        closed = true;
    else
        closed = false;

    return closed;
}

int Blinking::Analyze(IplImage* inputimage, CvRect righteye, CvRect lefteye)
{
    CvRect REImage;

    if(righteye.x != -1)
    {
        REImage = righteye;
        REImage.y += Findupperresize(REImage);
        REImage.height -= Findupperresize(REImage);
        REImage.height -= Findlowerresize(REImage);

        if(CalcPixels(Preprocessing::Crop(REImage,inputimage)))
            std::cout  << "Right Closed!!!" << std::endl;
        else
            std::cout  << "Right Open!!!" << std::endl;

        //cin.get();
        cvShowImage("Eye",Preprocessing::MakeGrayscale(Preprocessing::Crop(REImage,inputimage)));
        cvMoveWindow("Eye", 500, 50);
    }

    return 1;
}

int Blinking::Findlowerresize(CvRect eye)
{
    return eye.height / 4;
}

int Blinking::Findupperresize(CvRect eye)
{
    return eye.height / 3;
}




