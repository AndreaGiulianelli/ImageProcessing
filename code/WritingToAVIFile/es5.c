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

    //Inizia la lettura del video
    //Necessario per settare le proprietà del video nella struttura
    IplImage* bgr_frame = cvQueryFrame(capture); 
    double fps = cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
    CvSize size = cvSize(
        (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH),
        (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT)
        );

    //Il secondo parametro è il video codec (Tramite CV_FOURCC riusciamo ad esprimerlo in quattro caratteri)    
    //MJPEG è un codec video in cui tutti i frame del video vengonno codificati come un immagine JPG
    //Formato AVI: CV_FOURCC('P','I','M','1')
    CvVideoWriter* writer = cvCreateVideoWriter(argv[2],CV_FOURCC('M','J','P','G'),fps,size,1);
    IplImage* logpolar_frame = cvCreateImage(size,IPL_DEPTH_8U,3);

    while((bgr_frame=cvQueryFrame(capture))!=NULL)
    {
        cvLogPolar(bgr_frame,logpolar_frame,cvPoint2D32f(bgr_frame->width/2,bgr_frame->height/2),40,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS);
        cvWriteFrame(writer,logpolar_frame);
    }

    cvReleaseVideoWriter(&writer);
    cvReleaseImage(&logpolar_frame);
    cvReleaseCapture(&capture);
    return(0);

}