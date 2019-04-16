//g++ -std=c++11 comparison.c `pkg-config --libs --cflags opencv` -o comparison
#include "highgui.h"
#include "cv.h"
#include <stdio.h>

int main(int argc,char** argv)
{

    IplImage* src;
    if(argc != 3)
    {
        printf("Inserire il numero giusto di parametri");
        exit(1);
    }

    IplImage* src1 = cvLoadImage(argv[1]);
    IplImage* src2 = cvLoadImage(argv[2]);
    IplImage* src1_gray = cvCreateImage(cvGetSize(src1), 8, 1);
    IplImage* src2_gray = cvCreateImage(cvGetSize(src2), 8, 1);
    cvCvtColor(src1,src1_gray,CV_BGR2GRAY);
    cvCvtColor(src2,src2_gray,CV_BGR2GRAY);
    cvNamedWindow("Src1");
    cvNamedWindow("Src2");
    cvShowImage("Src1",src1_gray);
    cvShowImage("Src2",src2_gray);
    cvCmp(src1_gray,src2_gray,src1_gray,CV_CMP_EQ);

    cvNamedWindow("Result");
    cvShowImage("Result",src1_gray);
    
    cvWaitKey();

    return 0;
}
