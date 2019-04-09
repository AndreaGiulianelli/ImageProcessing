//g++ -std=c++11 es4.c `pkg-config --libs --cflags opencv` -o es4

#include "highgui.h"
#include "cv.h"

int main(int argc,char** argv)
{
    CvCapture* capture;

    capture = cvCreateCameraCapture(0);

    assert(capture != NULL);

    cvNamedWindow("Camera");

    int frames = (int) cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT);

    IplImage* frame;
    while(1)
    {
        frame = cvQueryFrame(capture);
        if(!frame) break;
        cvShowImage("Camera",frame);
        

        //Se dopo che cvWaitKey aspetta 33ms l'utente non preme esc allora continua con il frame dopo
        //Per riprodurre correttamente il video bisognerebbe leggere il frame rate del video e aspettare i secondi giusti
        double fps = cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
        char c = cvWaitKey((int)fps);
        if(c==27) break;
    }

    return 0;
}