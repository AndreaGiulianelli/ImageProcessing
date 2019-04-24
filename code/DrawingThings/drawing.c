//g++ -std=c++11 drawing.c `pkg-config --libs --cflags opencv` -o drawing
#include <stdio.h>
#include "highgui.h"
#include "cv.h"



int main()
{
    IplImage* image = cvCreateImage(CvSize(500,500),IPL_DEPTH_8U,3);
    cvNamedWindow("Finestra");

    //Disegno una linea
    /*
        Parametri:
            - CvArr* arr
            - CvPoint inizio
            - CvPoint fine
            - CvScalar colore
            - int larghezza
            - int anti-aliasing mode (default 8... 4 è molto più veloce)
    */
    cvLine(image,CvPoint(0,0),CvPoint(500,500),CvScalar(0,255,0),2,8);


    //Disegno un rettangolo
    /*
        Parametri uguali a CvLine tranne l'ultimo
        Se la larghezza la imposto a CV_FILLED (-1) allora imposta il colore del bordo anche come colore interno
    */
   cvRectangle(image,CvPoint(250,5),CvPoint(450,205),CvScalar(255,0,0),1);


    //Disegno un cerchio
    /*
        Parametri:
            - CvArr* arr
            - CvPoint centro
            - int raggio
            - CvScalar colore
            - int larghezza linea
            - int anti-aliasing

        Se la larghezza la imposto a CV_FILLED (-1) allora imposta il colore del bordo anche come colore interno
    */

    cvCircle(image,CvPoint(250,250),50,CvScalar(0,0,255),CV_FILLED,8);


    //Esiste cvEllipse per disegnare un ellisse
    /*
        void cvEllipse(
            CvArr* img,
            CvPoint center,
            CvSize axes,
            double angle,
            double start_angle,
            double end_angle,
            CvScalar color,
            int thickness = 1,
            int line_type = 8
        );
    */

    cvShowImage("Finestra",image);
    cvWaitKey();
    return 0;
}