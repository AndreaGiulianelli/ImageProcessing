//Compilarla con: g++ -std=c++11 es2.c `pkg-config --libs --cflags opencv` -o es2

#include "opencv/highgui.h"

int main(int argc,char** argv)
{
    if(argc != 2)
    {
        printf("ERROR: Insert a valid number of parameters");
        exit(1);
    }
    cvNamedWindow("Example2",CV_WINDOW_AUTOSIZE);

    //Prende come argomento il nome del FILE AVI
    //Restituisce la struttura CvCapture che contiene una struttura
    //con tutte le informazioni sul file AVI. Appena creata la struttura viene inizializzata all'inzio del video AVI
    CvCapture* capture = cvCreateFileCapture(argv[1]);
    IplImage* frame;

    while(1){
        //Prende il puntatore al prossimo frame da visualizzare
        //Utilizza la memoria già allocata per capture
        frame = cvQueryFrame(capture);
        if(!frame) break;
        cvShowImage("Example2",frame);
        //Se dopo che cvWaitKey aspetta 33ms l'utente non preme esc allora continua con il frame dopo
        //Per riprodurre correttamente il video bisognerebbe leggere il frame rate del video e aspettare i secondi giusti
        double fps = cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
        char c = cvWaitKey((int)fps);
        if(c==27) break;
        
    }
    //Usato per rilasciare le risorse
    cvReleaseCapture(&capture);
    cvDestroyWindow("Example2");
}