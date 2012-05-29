#include "breathing.h"

Breathing::Breathing()
{
    this->pos=0;
    this->prev=-1;
    this->avg=-1;
}

IplImage* preprocess(IplImage* img){     //creates a Image with the contours in the picture
    CvMemStorage* 	g_storage = NULL;
    IplImage* gray;
    gray = cvCreateImage( cvGetSize( img ), 8, 1 );  //creates the immage, allocating memory for the pixel values
    g_storage = cvCreateMemStorage(0);
    cvClearMemStorage( g_storage );
    CvSeq* contours = 0;
    cvCvtColor( img, gray, CV_BGR2GRAY );
    cvThreshold( gray, gray, 100, 255, CV_THRESH_BINARY );
    cvFindContours( gray, g_storage, &contours );           //find the contours with the thresholdimmage
    cvZero( gray );
    if( contours )
    {
        cvDrawContours(gray,contours,cvScalarAll(255),cvScalarAll(255),100 ); //paint the contours on immage contours
    }
    return gray;
}






int Breathing::getdistance(IplImage* img, Facefeatures* face){
    IplImage* contour;
    contour=preprocess(img);
    int i=0;
    CvScalar pixel;
    CvPoint startpos=cvPoint(face->mFace.x,face->mFace.y+face->mFace.height*1.2);

    while(startpos.y+i<contour->height)  //while the position is in the picture
    {
        pixel = cvGetAt(contour,startpos.y+i,startpos.x);        //get value of pixel
        //cout << pixel.val[0]<<" "<<pixel.val[1] << " i " << i << " y " << startpos.y << endl;
        if(pixel.val[0]>100 )               // if pixel is black then we found a contour and passes on the position
        {
            break;
        }
        i++;   //otherwise go a pixel down and continue looping
    }
    int svar=startpos.y+i;
    //cvLine(contour, cvPoint(startpos.x-10,startpos.y+i), cvPoint(startpos.x+10,startpos.y+i), cvScalar(255,255,255), 1);
    cvLine(contour, startpos, cvPoint(startpos.x,startpos.y+100), cvScalar(255,255,255), 1);        //information lines to see the positions it searches at
    cvShowImage( "Contours", contour );
    cvReleaseImage(&contour);
    return svar;    //return the position of the picture
}

int Breathing::isBreathing(IplImage* img, Facefeatures* face) //returns a binary value 0=bellow or 1=above for valid outputs, -1 if undefined
{
    int b;
    int a = getdistance(img,face);  // the position returned by the function above
    if (this->pos<200) // lower then 200 means that the list hasnt become full yet
    {
        this->list[this->pos]=a;
        this->pos++;
        return -1;  //add the value to the list and return -1 as in not long enough list for comparison
    }
    else //list is full
    {
        if(this->pos==400)  //the end of the list
        {
            this->pos-=200; //go back to the start
        }
        b=this->list[this->pos-200]; //pick the value that is on the spot that the new value will be added on
        this->list[this->pos-200]=a;   // place the new value on that spot
        this->pos++;    //increase the position variable

        if (this->avg==-1)  //if a avg hasnt been calculated yet then loop threw the list and get the avg value
        {
            int i;
            for(i=0;i<200;i++)
                this->avg+=this->list[i];
        }
        else    //if avg has been set, then avg subtract the old value in that spot and adds the new value
        {
            avg=avg-b+a;
        }
        int val=0;
        for(int i=0;i<5;i++)
        {
            if(this->pos-i<200)
            {
                if (this->list[this->pos-i]*200<this->avg)    //if the avg value is bigger then current value then add 1 to val;
                {
                    val+=1;
                }
            }
            else
            {
                if (this->list[this->pos-i-200]*200<this->avg)    //if the avg value is bigger then current value then add 1 to val;
                {
                    val+=1;
                }
            }

        }
        if(val>2)
        {
            return 1;
        }
        else
        {
            return 0;
        }

    }
}

