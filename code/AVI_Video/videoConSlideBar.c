//g++ -std=c++11 videoConSlideBar.c `pkg-config --libs --cflags opencv` -o videoConSlideBar

//Add slider to video player

#include "cv.h"
#include "highgui.h"

int g_slider_position = 0;
CvCapture* g_capture = NULL;

void onTrackbarSlide(int pos)
{
    cvSetCaptureProperty(g_capture,CV_CAP_PROP_POS_FRAMES,pos);
}

int main(int argc,char** argv)
{
    cvNamedWindow("Example3",CV_WINDOW_AUTOSIZE);
    g_capture = cvCreateFileCapture(argv[1]);
    int frames = (int) cvGetCaptureProperty(g_capture,CV_CAP_PROP_FRAME_COUNT);
    
    if(frames != 0)
    {
        cvCreateTrackbar("Position","Example3",&g_slider_position,frames,onTrackbarSlide);
        IplImage* frame;
        while(1){
            //Prende il puntatore al prossimo frame da visualizzare
            //Utilizza la memoria già allocata per capture
            frame = cvQueryFrame(g_capture);
            if(!frame) break;
            cvShowImage("Example3",frame);
            //Se dopo che cvWaitKey aspetta 33ms l'utente non preme esc allora continua con il frame dopo
            //Per riprodurre correttamente il video bisognerebbe leggere il frame rate del video e aspettare i secondi giusti
            double fps = cvGetCaptureProperty(g_capture,CV_CAP_PROP_FPS);
            cvSetTrackbarPos("Position","Example3",++g_slider_position);
            char c = cvWaitKey((int)fps);
            if(c==27) break;
        }
    }
    //Usato per rilasciare le risorse
    cvReleaseCapture(&g_capture);
    cvDestroyWindow("Example3");
}
