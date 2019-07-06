//g++ -std=c++11 trackbar.c `pkg-config --libs --cflags opencv` -o trackbar
#include "highgui.h"

int main()
{
    //La trackbar (slider) possiede un nome come le finestre che è unico
    //Per creare una trackbar si usa:
    /*
        int cvCreateTrackbar(
            const char*          trackbar_name
            const char*          window_name
            int*                 value
            int                  count
            CvTrackbarCollback   on_change
        )

    value è un puntatore al valore della trackbar, sarà settanto automaticamente al valore in cui la trackbar 
    sarà mossa
    count è il massimo valore della trackbar
    */



   /*
    Per leggere o settare la posizione della trackbar(ovunque nel programma) si usano:
    
    int cvGetTrackbarPos(const char* trackbar_name,const char* window_name);
    void cvSetTrackbarPos(const char* trackbar_name,const char* window_name,int pos);
   */


    return 0;
}