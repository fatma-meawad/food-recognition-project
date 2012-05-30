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

double CalcPixels(IplImage * inputImage)
{
    CvScalar pixel;
    IplImage * input;
    IplImage * copy = cvCreateImage(cvSize(inputImage->width,inputImage->height),IPL_DEPTH_8U,inputImage->nChannels);
    IplImage * check = cvCreateImage(cvSize(inputImage->width,inputImage->height),IPL_DEPTH_8U,1);
    cvCopy(inputImage, copy);

    //input = Preprocessing::MakeGrayscale(inputImage);
    //Preprocessing::MakeEqualized(input);

    cvShowImage("Equal", inputImage);
    //cvMoveWindow("Equal", 200,100);

    double i = 0;
    double max = 0;
    bool found = false;

    for(; !found; i++)
    {
        cvCopy(inputImage, check);
        cvSmooth(check, check, CV_MEDIAN,11);
        Preprocessing::MakeBinary(check, i);

        for(int y = check->height/3; y < check->height && !found; y++)
            for(int x = 0; x < check->width && !found; x++)
            {
                pixel = cvGetAt(check,y,x);
                if(pixel.val[0] != 255)
                {
                    found = true;
                    for(int k = 0; k<copy->width; k++)
                    {
                        pixel = cvGetAt(copy,y,k);
                        if(pixel.val[0] + pixel.val[1] + pixel.val[2] > max)
                            max = pixel.val[0] + pixel.val[1] + pixel.val[2];
                    }
                    max = max/(255);
                    //cout << "Sum: " << max << "\t";
                }
            }
    }

    return max;
}

int Blinking::Analyze(IplImage* inputImage, CvRect righteye, CvRect lefteye)
{
    CvRect REImage, LEImage;
    int closed = -1;

    IplImage * copy = cvCreateImage(cvSize(inputImage->width,inputImage->height),IPL_DEPTH_8U,inputImage->nChannels);
    cvCopy(inputImage, copy);

    copy = Preprocessing::MakeGrayscale(copy);
    Preprocessing::MakeEqualized(copy);

    timeval start, stop;

    gettimeofday(&start, NULL);

    double left, right = 0;

    if(righteye.x != -1)
    {
        REImage = righteye;
        REImage.y += Findupperresize(REImage);
        REImage.height -= Findupperresize(REImage);
        REImage.height -= Findlowerresize(REImage);

        right = CalcPixels(Preprocessing::Crop(REImage,copy));
    }

    if(lefteye.x != -1)
    {
        LEImage = lefteye;
        LEImage.y += Findupperresize(LEImage);
        LEImage.height -= Findupperresize(LEImage);
        LEImage.height -= Findlowerresize(LEImage);

        left = CalcPixels(Preprocessing::Crop(LEImage,copy));
    }

    gettimeofday(&stop, NULL);

    //cout << "MS: " << (((stop.tv_sec - start.tv_sec)* 1000 + (stop.tv_usec - start.tv_usec)/1000.0) + 0.5);



    if(filter.size() > 8)
        filter.erase(filter.begin());

    double avg = 0;
    for(int i = 0; i<filter.size(); i++)
    {
        avg += filter.at(i);
    }
    avg = avg/filter.size();

    filter.push_back(left*right);

    //cout << "Quote: " << 1 - avg/(left*right) << "\t";

    if(left*right * (1+(1 - avg/(left*right))) < 0.3)
    {
        closed = 1;
        cout << "CLOSED!!!   " << left*right * (1+(1 - avg/(left*right)))  << endl;
    }
    else
    {
        closed = 0;
        cout << "OPEN!!!     " << left*right * (1+(1 - avg/(left*right)))  << endl;
    }

    cvReleaseImage(&copy);

    return closed;
}

int Blinking::Findlowerresize(CvRect eye)
{
    return eye.height / 2;
}

int Blinking::Findupperresize(CvRect eye)
{
    return eye.height / 2.0;
}
