//Compilarla con: g++ -std=c++11 es1 `pkg-config --libs --cflags opencv` -o es1


#include "opencv/highgui.h"

int main(int argc, char** argv )
{
    if(argc != 2)
    {
        printf("ERROR: insert the proper number of parameters..\n");
        exit(1);
    }
    //Carica in memoria l'immagine e alloca la giusta struttura dati per gestirla (viene fatto tutto in automatico)
    //IplImage è il tipo di dato che usa Opencv per gestire qualsiasi tipo di immagine
    IplImage* img = cvLoadImage(argv[1]);

    //cvNamedWindow apre una finestra che può contenere e visualizzare un'immagine
    //Il secondo parametro setta la proprietà della finestra: 0-->valore di default, CV_WINDOW_AUTOSIZE--->dimensione automatica
    //La finestra viene aperta solo quando viene richiamata esplicitamente.. Il comando in se la inserisce solamente in memoria
    cvNamedWindow("Example1",CV_WINDOW_AUTOSIZE);

    //Visualizza un'immagine su una finestra esistente
    cvShowImage("Example1",img);

    //cvWaitKey stoppa il programma finchè non premo un tasto
    //Se passo un numero positivo, aspetta x millisecondi e poi continua anche se non premo nulla
    //Se passo 0 il programma aspetta all'infinito finche non premo un tasto
    cvWaitKey(0);
    
    //Dealloca la memoria riservata per l'immagine
    cvReleaseImage(&img);

    //Distrugge la finestra e dealloca la memoria occupata da quest'ultima
    cvDestroyWindow("Example1");
}
