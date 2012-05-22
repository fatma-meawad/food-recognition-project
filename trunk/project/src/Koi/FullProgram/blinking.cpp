#include "blinking.h"

#define samples 10

int avg = samples;
double avgMass = 0;
CvPoint avgCenter = cvPoint(0,0);

int Blinking::Init()
{
    return 1;
}

bool CalcPixels(IplImage * inputImage)
{
    CvScalar pixel;
    IplImage * input;// = cvCreateImage(cvSize(inputImage->width,inputImage->height),IPL_DEPTH_8U,inputImage->nChannels);
    input = Preprocessing::MakeGrayscale(inputImage);

    double mass = 0;
    bool closed;
    CvPoint massCenter = cvPoint(0,0);

    int eX = input->width/4;
    int eY = input->height/4;

    if(avg > 0)
    {
        double maxMass = mass;
        for(int i = 0; i < (input->width - eX); i++)
        {
            for(int j = 0; j < (input->height - eY); j++)
            {
                mass = 0;
                for(int k = j; k < j + eY; k++)
                    for(int l = i; l < i + eX; l++)
                    {
                        pixel = cvGetAt(input,k,l);
                        if(pixel.val[0] != 255)
                            mass++;
                    }
                if(mass > maxMass)
                {
                    massCenter = cvPoint(i,j); //std::cout << massCenter.x << "," << massCenter.y << ", " << mass << ",   " << input->width << "," <<input->height << std::endl;
                    maxMass = mass;
                }
            }
        }

        if(avg == 1)
        {
            avgCenter = cvPoint((massCenter.x + avgCenter.x)/samples, (massCenter.y + avgCenter.y)/samples);
            avgMass = (avgMass + maxMass)/samples;
        }
        else
        {
            avgCenter = cvPoint(massCenter.x + avgCenter.x, massCenter.y + avgCenter.y);
            avgMass += maxMass;
        }

        avg--;
        return false;
    }
    else
    {
        double area = 0;

        eY = std::min(eY,input->height - avgCenter.y);
        eX = std::min(eX, input->width - avgCenter.x);

        for(int k = avgCenter.y; k < avgCenter.y + eY; k++)
            for(int l = avgCenter.x; l < avgCenter.x + eX; l++)
            {
                pixel = cvGetAt(input,k,l);
                area++;
                if(pixel.val[0] != 255)
                    mass++;
            }

        //std::cout << avgCenter.x << "," << avgCenter.y << "\t";
        std::cout << avgMass/area << "\t" << mass/area << "\t";
        std::cout << (avgMass/area - mass/area)/(avgMass/area) << "\t";

        if((avgMass/area - mass/area)/(avgMass/area) > 0.8)
            closed = true;
        else
            closed = false;

        cvReleaseImage(&input);

        return closed;
    }
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




