#include "blinking.h"

#define samples 10

// Average values as reference
int avg = samples;
double avgArea = 0;
double avgMass = 0;
double openLen = 0;
CvPoint avgCenter = cvPoint(0,0);

bool CalcPixels(IplImage * inputImage)
{
    CvScalar pixel;
    IplImage * input;
    input = Preprocessing::MakeBinary(inputImage);   // Make picture binary before analyzing

    cvShowImage("After", input);

    double mass = 0;
    bool closed;
    CvPoint massCenter = cvPoint(0,0);

    int eX = input->width/4;        // Sets size of sub-area to be analyzed
    int eY = input->height/4;       //              -||-

    // Create average values for
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

        // Assume open eyes
        return false;
    }
    else
    {
        double area = 0;

        eY = std::min(eY,input->height - avgCenter.y);
        eX = std::min(eX, input->width - avgCenter.x);

        vector<CvPoint> blackPixels;

        // Find all black pixels in sub-area
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

            // Calculate center of black pixels
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

        // If average mass and average "density" is high enough, consider eyes closed
        if((avgMass/area - mass/area)/(avgMass/area) +abs(openLen - avgLen)/openLen > 0.8)
            closed = true;
        else
            closed = false;

        cvReleaseImage(&input);

        return closed;
    }
}

// Analyze image, determine whether eye is closed or not
int Blinking::Analyze(IplImage* inputimage, CvRect righteye)
{
    CvRect REImage;
    int closed = -1;

    // If there exists a right eye, then analyze the eye
    if(righteye.x != -1)
    {
        REImage = righteye;
        REImage.y += FindUpperResize(REImage);
        REImage.height -= FindUpperResize(REImage);
        REImage.height -= FindLowerResize(REImage);

        // Analyze cropped image
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

        // Show cropped Eye-frame
        cvShowImage("Eye",Preprocessing::MakeBinary(Preprocessing::Crop(REImage,inputimage)));
    }

    return closed;
}

int Blinking::FindLowerResize(CvRect eye)
{
    return eye.height / 4;
}

int Blinking::FindUpperResize(CvRect eye)
{
    return eye.height / 3;
}




