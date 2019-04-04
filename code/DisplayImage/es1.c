//Compilarla con: g++ -std=c++11 es1 `pkg-config --libs --cflags opencv` -o es1


#include "opencv/highgui.h"

int main(int argc, char** argv )
{
    IplImage* img = cvLoadImage(argv[1]);
    cvNamedWindow("Example1",CV_WINDOW_AUTOSIZE);
    cvShowImage("Example1",img);
    cvWaitKey(0);
    cvReleaseImage(&img);
    cvDestroyWindow("Example1");
}
