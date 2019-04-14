//g++ -std=c++11 timelaps.c `pkg-config --libs --cflags opencv` -o timelaps
#include "highgui.h"
#include "cv.h"
#include <stdio.h>
#include <string.h>

int main(int argc,char** argv)
{
    if(argc != 3)
    {
        printf("Inserisci il numero corretto di parametri e riprova.\n");
        exit(1);
    }

    int factor = atoi(argv[2]);
    CvCapture* capture = cvCreateFileCapture(argv[1]);
    if(!capture)
    {
        return -1;
    }

    IplImage* out_frame = cvQueryFrame(capture);
    double fps = cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
    CvSize size = cvSize(
        (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH),
        (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT)
        );

    CvVideoWriter* writer = cvCreateVideoWriter("out.avi",CV_FOURCC('P','I','M','1'),fps,size,1);
    int frames = (int) cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT);
    printf("Fps: %d\nFrameTotali:%d\n",(int)fps,frames);
    int framesScritti=0;
    int frameDaScrivere=0;
    while(out_frame!=NULL)
    {
        cvWriteFrame(writer,out_frame);
        cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,frameDaScrivere);
        out_frame=cvQueryFrame(capture);
        //printf("Writing frame...\n");
        framesScritti++;
        frameDaScrivere+=factor;
    }
    printf("Frame Scritti: %d",framesScritti);
    cvReleaseVideoWriter(&writer);
    cvReleaseImage(&out_frame);
    cvReleaseCapture(&capture);
    return 0;
    
}

