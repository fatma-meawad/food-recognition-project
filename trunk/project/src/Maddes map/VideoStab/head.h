#ifndef HEAD_H
#define HEAD_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>




class head
{

    CvRect mFace, mLeftEye, mRightEye; //Possible nose, mouth etc

};

class FindFeatures
{
    IplImage * RefinedImage;

    Head mAvgHead;                      // Use when analysing positions

    Head avgHead(/* headstack */);      // The average values from the stack of heads

    IplImage* findFace(IplImage* img, Head* oldHead, Head* newHead);    // Take frame, return ROI for eyes, checks with old head, sets new head    paint

    void findEyes(IplImage* img, Head* oldHead, Head* newHead);        // Use image from findFace to find eyes, set eyes in new head    paint

};

#endif // HEAD_H
