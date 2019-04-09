//g++ -std=c++11 es3.c `pkg-config --libs --cflags opencv` -o es3
//Creo funzione per fare il pyramid Down di un immagine
#include "highgui.h"
#include "cv.h"
#include <stdio.h>

IplImage* doPyrDown(IplImage*,int);
IplImage* doCanny(IplImage*,double,double,double);

int main(int argc,char** argv)
{
    if(argc != 2)
    {
        printf("ERROR: insert the proper number of parameters..\n");
        exit(1);
    }
    
    IplImage* img = cvLoadImage(argv[1]);
    cvNamedWindow("Example1",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Example1-out",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Example1-canny",CV_WINDOW_AUTOSIZE);

    IplImage* out = doPyrDown(img,CV_GAUSSIAN_5x5);
    IplImage* out1 = doCanny(out,10,100,3);
    cvShowImage("Example1",img);
    cvShowImage("Example1-out",out);
    cvShowImage("Example1-canny",out1);

    cvWaitKey(0);
    cvReleaseImage(&img);
    cvReleaseImage(&out);
    cvReleaseImage(&out1);

    cvDestroyWindow("Example1");
    cvDestroyWindow("Example1-out");
    cvDestroyWindow("Example1-canny");
}

IplImage* doPyrDown(IplImage* in,int filter = CV_GAUSSIAN_5x5)
{
    assert(in->width%2==0 && in->height%2==0);
    
    IplImage* out = cvCreateImage(cvSize(in->width/2,in->height/2),in->depth,in->nChannels);
    cvPyrDown(in,out);
    return(out);
}

IplImage* doCanny(IplImage* in,double lowThresh,double highThresh,double aperture)
{
    /*if(in->nChannels != 1)
    {
        return 0; //Canny può solo gestire immagini ad un canale
    }*/

    //Canny definisce i contorni dell'immagine
    IplImage* out = cvCreateImage(cvGetSize(in), IPL_DEPTH_8U,1);
    cvCanny(in,out,lowThresh,highThresh,aperture);
    return(out);
}