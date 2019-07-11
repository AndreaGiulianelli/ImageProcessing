//g++ -std=c++11 buttons.c `pkg-config --libs --cflags opencv` -o buttons
#include "highgui.h"

int main()
{
    //Per inizializzare la struttura CvCapture abbiamo bisogno di due funzioni
    //a seconda che il video provenga da camera o da file

    /*
        CvCapture* cvCreateFileCapture(const char* filename)
        CvCapture* cvCreateCameraCapture(int index)

        CONTROLLARE sempre che il puntatore alla struttura CvCapture non sia NULL..
        Se fosse NULL significa che si è verificato qualche problema nell'apertura del file
        Ritorna NULL anche se sulla macchina non è installato quel particolare codec...
        Quindi potrebbe andare su una macchina e su un'altra no

        Con cvCreateCamereCapture passo un intero...
        - 0 - Quando ho solo una camera, altrimenti il numero di camera da selezionare
        - Diverse costanti che selezionano l'ingresso pag.119

    */


   /*
        Leggere un video
        
        int cvGrabFrame(CvCapture* capture);
        IplImage* cvRetrieveFrame(CvCapture* capture);
        IplImage* cvQueryFrame(CvCapture* capture);

        

   */
    return 0;
}