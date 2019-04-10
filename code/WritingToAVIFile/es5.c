//g++ -std=c++11 es5.c `pkg-config --libs --cflags opencv` -o es5
//Convert a video to grayscale
// argv[1]: input video file
// argv[2]: name of new output file


#include "highgui.h"
#include "cv.h"


int main(int argc,char** argv)
{
    if(argc != 3)
    {
        printf("Invalid parameters number...\n");
        exit(1);
    }

    CvCapture* capture = 0;
    capture = cvCreateFileCapture(argv[1]);
    if(!capture)
    {
        return -1;
    }

    IplImage* bgr_frame = cvQueryFrame(capture); //Inizia la lettura del video
    
}