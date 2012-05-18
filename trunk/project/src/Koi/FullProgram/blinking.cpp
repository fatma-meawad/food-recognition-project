#include "blinking.h"

#define samples 10

double massDiff = 0.5;
double areaDiff = 0.5;
int avg = samples;

int Blinking::Init()
{
    return 1;
}

bool CalcPixels(IplImage * inputImage)
{
    CvScalar pixel;
    IplImage * input;// = cvCreateImage(cvSize(inputImage->width,inputImage->height),IPL_DEPTH_8U,inputImage->nChannels);
    input = Preprocessing::MakeGrayscale(inputImage);

    int linesX = 0;
    int area = 0;
    double area2 = 0;
    CvPoint darkCenter = cvPoint(0,0);
    double lengthToCenter;
    bool clear;
    bool closed;

    int sX = input->width*2/4;
    int eX = input->width;
    int sY = input->height/3;
    int eY = input->height*2/3;

    // Second area test
    int sX2 = input->width*2/4;
    int eX2= input->width;
    int sY2 = input->height/2;
    int eY2 = input->height;

    for(int j = sY; j < eY; j++)
    {
        clear = true;
        for(int i = sX; i < eX; i++)
        {
            pixel = cvGetAt(input,j,i);
            if(pixel.val[0] != 255)
            {
                darkCenter.x += i;
                darkCenter.y += j;
                clear = false;
                area++;
            }
        }

        if(clear)
            linesX++;
    }

    darkCenter.x = darkCenter.x/area;
    darkCenter.y = darkCenter.y/area;

    for(int j = sY2 ; j < eY2; j++)
        for(int i =  sX2; i < eX2; i++)
        {
            pixel = cvGetAt(input,j,i);
            if(pixel.val[0] != 255)
                area2++;
        }

    area2 = area2/((eY2 - sY2)*(eX2 - sX2));


    lengthToCenter = (sqrt((darkCenter.x - (sX + eX)/2)*(darkCenter.x - (sX + eX)/2) + (darkCenter.y - (sY + eY)/2)*(darkCenter.y - (sY + eY)/2)))
            /(sqrt(((eX - sX)/2 - sX)*((eX - sX)/2 - sX) + ((eY - sY)/2 - sY)*((eY - sY)/2 - sY)));

    std::cout << abs(lengthToCenter - massDiff) << "\t" << abs((double)area/((eX - sX)*(eY - sY)) - areaDiff) << "\t"
              << abs(lengthToCenter - massDiff) + abs((double)area/((eX - sX)*(eY - sY)) - areaDiff) << "\t"
              << eX - darkCenter.x << "\t" << eY - darkCenter.y << "\t" << area2 << "\t";

    //if((linesX - 1 > (input->height)/10  || (double)area/((eX - sX)*(eY - sY)) < 0.2))

    if(abs(lengthToCenter - massDiff) + abs((double)area/((eX - sX)*(eY - sY)) - areaDiff) > 0.35)
        closed = true;
    else
        closed = false;

    cvReleaseImage(&input);

    if(avg > 0)
    {
        if(avg != samples)
        {
            massDiff = (lengthToCenter + massDiff)/2;
            areaDiff = ((double)area/((eX - sX)*(eY - sY)) + areaDiff)/2;
        }
        else
        {
            massDiff = lengthToCenter;
            areaDiff = (double)area/((eX - sX)*(eY - sY));
        }

        avg--;
        if(avg == 0)
            std::cout << "Start!";
    }

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




