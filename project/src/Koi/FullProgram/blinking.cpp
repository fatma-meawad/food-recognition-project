#include "blinking.h"

#define samples 10

int avg = samples;
double avgArea = 0;
double avgMass = 0;
double openLen = 0;
CvPoint avgCenter = cvPoint(0,0);

int Blinking::Init()
{
    return 1;
}

bool CalcPixels(IplImage * inputImage)
{
    CvScalar pixel;
    IplImage * input;
    input = Preprocessing::MakeGrayscale(inputImage);

    //cvSmooth(input, input,CV_MEDIAN,11);

    cvShowImage("After", input);
    cvMoveWindow("After", 200, 100);

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
            int closeX = input->width;

            for(int j = 0; j < (input->height - eY); j++)
            {
                int closeY = input->height;
                mass = 0;
                for(int k = j; k < j + eY; k++)
                    for(int l = i; l < i + eX; l++)
                    {
                        pixel = cvGetAt(input,k,l);
                        if(pixel.val[0] != 255)
                        {
                            mass++;
                            if(l < closeX)
                                closeX = l;
                            if(k < closeY)
                                closeY = k;
                        }
                    }
                if(mass > maxMass)
                {
                    massCenter = cvPoint(i,j);
                    maxMass = mass;
                }

                if(closeY - 1 > i && closeY != input->height)
                    i = closeY - 1;
            }

            if(closeX - 1 > i && closeX != input->width)
                i = closeX - 1;

        }

        vector<CvPoint> blackPixels;

        /*for(int i = 0; i < input->width; i++)
        {
            for(int j = 0; j < input->height; j++)
            {
                pixel = cvGetAt(input,j,i);
                if(pixel.val[0] != 255)
                    blackPixels.push_back(cvPoint(i,j));
            }
        }*/

        for(int k = massCenter.y; k < massCenter.y + eY; k++)
            for(int l = massCenter.x; l < massCenter.x + eX; l++)
            {
                pixel = cvGetAt(input,k,l);
                if(pixel.val[0] != 255)
                    blackPixels.push_back(cvPoint(l,k));
            }

        double avgLen = 0;
        if(blackPixels.size())
        {

            // Calculate center
            int avgX = 0;
            int avgY = 0;
            for(unsigned int i = 0; i < blackPixels.size(); i++)
            {
                avgX += blackPixels.at(i).x;
                avgY += blackPixels.at(i).y;
            }
            avgX = avgX/blackPixels.size();
            avgY = avgY/blackPixels.size();

            // Calculate average distance to from dark pixel to center
            for(unsigned int i = 0; i < blackPixels.size(); i++)
            {
                avgLen += sqrt((avgX - blackPixels.at(i).x)*(avgX - blackPixels.at(i).x) + (avgY - blackPixels.at(i).y)*(avgY - blackPixels.at(i).y));
            }
            avgLen = avgLen/blackPixels.size();
        }
        else
            std::cout << "EMPTY" << "\t";

        if(avg == 1)
        {
            avgCenter = cvPoint((massCenter.x + avgCenter.x)/samples, (massCenter.y + avgCenter.y)/samples);
            avgMass = (avgMass + maxMass)/samples;
            openLen = (openLen + avgLen)/samples;
            avgArea = (avgArea + (eX*eY))/samples;
        }
        else
        {
            avgCenter = cvPoint(massCenter.x + avgCenter.x, massCenter.y + avgCenter.y);
            avgMass += maxMass;
            openLen += avgLen;
            avgArea += (eX*eY);
        }

        avg--;
        return false;
    }
    else
    {
        double area = 0;

        eY = std::min(eY,input->height - avgCenter.y);
        eX = std::min(eX, input->width - avgCenter.x);

        vector<CvPoint> blackPixels;

        /*for(int i = 0; i < input->width; i++)
        {
            for(int j = 0; j < input->height; j++)
            {
                pixel = cvGetAt(input,j,i);
                if(pixel.val[0] != 255)
                    blackPixels.push_back(cvPoint(i,j));
            }
        }*/

        for(int k = avgCenter.y; k < avgCenter.y + eY; k++)
            for(int l = avgCenter.x; l < avgCenter.x + eX; l++)
            {
                pixel = cvGetAt(input,k,l);
                if(pixel.val[0] != 255)
                    blackPixels.push_back(cvPoint(l,k));
            }

        double avgLen = 0;
        if(blackPixels.size())
        {

            // Calculate center
            int avgX = 0;
            int avgY = 0;
            for(unsigned int i = 0; i < blackPixels.size(); i++)
            {
                avgX += blackPixels.at(i).x;
                avgY += blackPixels.at(i).y;
            }
            avgX = avgX/blackPixels.size();
            avgY = avgY/blackPixels.size();

            // Calculate average distance to from dark pixel to center
            for(unsigned int i = 0; i < blackPixels.size(); i++)
            {
                avgLen += sqrt((avgX - blackPixels.at(i).x)*(avgX - blackPixels.at(i).x) + (avgY - blackPixels.at(i).y)*(avgY - blackPixels.at(i).y));
            }
            avgLen = avgLen/blackPixels.size();

            //std::cout << "Dist X, Y: " << avgCenter.x + eX/2 - avgX << ", " << avgCenter.y + eY/2 - avgY << "\t";

            /*if(avgCenter.x + eX/2 - avgX < -1)
                avgCenter.x += abs(avgCenter.x + eX/2 - avgX);
            else if(avgCenter.x + eX/2 - avgX > 1)
                avgCenter.x -= abs(avgCenter.x + eX/2 - avgX);*/
        }
        else
        {
            std::cout << "EMPTY!" << "\t";
            return true;
        }

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
        //std::cout << avgMass/area << "\t" << mass/area << "\t";
        //std::cout << avgArea/area << "\t";
        //std::cout << (openLen - avgLen)/openLen << "\t";
        //std::cout << (avgMass/area - mass/area)/(avgMass/area) << "\t";
        //std::cout << (avgMass/area - mass/area)/(avgMass/area) + abs(openLen - avgLen)/openLen << "\t";

        if((avgMass/area - mass/area)/(avgMass/area) +abs(openLen - avgLen)/openLen > 0.8)
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
    int closed = -1;

    if(righteye.x != -1)
    {
        REImage = righteye;
        REImage.y += Findupperresize(REImage);
        REImage.height -= Findupperresize(REImage);
        REImage.height -= Findlowerresize(REImage);

        if(CalcPixels(Preprocessing::Crop(REImage,inputimage)))
        {
            closed = 1;
            std::cout  << "Right Closed!!!" << std::endl;
        }
        else
        {
            closed = 0;
            std::cout  << "Right Open!!!" << std::endl;
        }

        cvShowImage("Eye",Preprocessing::MakeGrayscale(Preprocessing::Crop(REImage,inputimage)));
        cvMoveWindow("Eye", 500, 50);
    }

    return closed;
}

int Blinking::Findlowerresize(CvRect eye)
{
    return eye.height / 4;
}

int Blinking::Findupperresize(CvRect eye)
{
    return eye.height / 3;
}




