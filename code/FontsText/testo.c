//g++ -std=c++11 testo.c `pkg-config --libs --cflags opencv` -o testo
#include <stdio.h>
#include "highgui.h"
#include "cv.h"



int main()
{
    IplImage* image = cvCreateImage(CvSize(500,500),IPL_DEPTH_8U,3);
    cvNamedWindow("Finestra");


    CvFont font;
    cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0,1.0,1,0);
    cvPutText(image,"Hello Word",CvPoint(0,100),&font,CvScalar(255,255,255));

    cvShowImage("Finestra",image);
    cvWaitKey();
    return 0;
}