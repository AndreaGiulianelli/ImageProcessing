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
    //Example3 - Foto originale
    //Example4-out - Foto dopo aver eseguito lo smoothing
    cvNamedWindow("Example3",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Example4-out",CV_WINDOW_AUTOSIZE);

    g_capture = cvCreateFileCapture(argv[1]);

    //Ottengo il numero di frames nel video in modo da calibrare lo slider
    int frames = (int) cvGetCaptureProperty(g_capture,CV_CAP_PROP_FRAME_COUNT);
    
    //Faccio il controllo perchè alcuni formati non danno il numero di frame totali.. Perciò in questi casi la trackbar non viene visualizzata
    if(frames != 0)
    {
        //Position e la label della trackbar
        //Come paramentro passo frames: che è il numero massimo che deve gestire
        cvCreateTrackbar("Position","Example3",&g_slider_position,frames,onTrackbarSlide);   
    }

    IplImage* frame;
    while(1){
        //Prende il puntatore al prossimo frame da visualizzare
        //Utilizza la memoria già allocata per capture
        frame = cvQueryFrame(g_capture);
        if(!frame) break;
        cvShowImage("Example3",frame);

        //Il primo argomento è la dimensione da allocare, il secondo è il tipo di dato usato per ogni canale dell'immagine e il terzo è il numero di canali (3 da 8 bit)
        IplImage* out = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,3);
        //Faccio lo smooth dell'immagine con una funzione gaussiana su un area 5x5 su ogni pixel
        //Quindi esegue abbastanza il blur
        cvSmooth(frame,out,CV_GAUSSIAN,5,5);
        cvShowImage("Example4-out",out);
        cvReleaseImage(&out);

        //Se dopo che cvWaitKey aspetta 33ms l'utente non preme esc allora continua con il frame dopo
        //Per riprodurre correttamente il video bisognerebbe leggere il frame rate del video e aspettare i secondi giusti
        double fps = cvGetCaptureProperty(g_capture,CV_CAP_PROP_FPS);
        
        //Aggiorno la posizione della trackBar
        //NB: Questo rallenta la riproduzione del video
        cvSetTrackbarPos("Position","Example3",++g_slider_position);
        char c = cvWaitKey((int)fps);
        if(c==27) break;
    }
    //Usato per rilasciare le risorse
    cvReleaseCapture(&g_capture);
    cvDestroyWindow("Example3");
    cvDestroyWindow("Example4-out");
}
