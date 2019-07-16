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
            Ritorna 1 se è riuscito ad ottenere il frame, 0 altrimenti
            Salva il frame in un buffer inacessibile, o meglio accessibile solo con 
            cvRetrieveFrame.. E' un modo molto più veloce per salvare il frame
        IplImage* cvRetrieveFrame(CvCapture* capture);
            Prende l'immagine grabbata dalla funzione precedente, il problema è che se abbiamo
            bisogno dell'immagine dobbiamo copiarla, ATTENZIONE a non copiare il puntatore, ma l'immaggine stessa.
            Tutto questo perchè quel buffer verrà riscritto non appena lanciamo un altro cvGrabFrame.
        
        IplImage* cvQueryFrame(CvCapture* capture);
            Modo più veloce
   */

    /*
        Per settare o ottenere proprietà dalla struttura CvCapture possiamo:
            double cvGetCaptureProperty(CvCapture* capture,int property_id);
            int cvSetCaptureProperty(CvCapture* capture,int property_id,double value);
        
        Alcune proprietà: 
        NOME COSTANTE               Valore Numerico Rappresentato   Descrizione
        CV_CAP_PROP_POS_MSEC        0                               La posizione corrente nel video
        CV_CAP_PROP_POS_FRAME       1                               Posizione corrente come numero di frame
        CV_CAP_PROP_POS_AVI_RATIO   2                               Posizione dato come numero tra 0 e 1 (utile con le trackbar)
        CV_CAP_PROP_FRAME_WIDTH     3                               Larghezza del frame
        CV_CAP_PROP_FRAME_HEIGHT    4                               Altezza del frame
        CV_CAP_PROP_FPS             5                               FPS con cui il video è stato registrato
        CV_CAP_PROP_FOURCC          6                               E' il nome a 4 caratteri del codec utilizzato per comprire il video che si sta leggendo
        CV_CAP_PROP_FRAME_COUNT     7                               Numero totale di frame... (Non è molto affidabile)   

        Tutte queste proprietà sono ritornate come double.. tranne FOURCC, ma basta castare il risultato
        double f = cvGetCaptureProperty(capture,CV_CAP_PROP_FOURCC);
        char* fourcc = (char*) (&f);

        Il set della posizione nuova tramite cvSetCaptureProperty con le varie costanti per la posizione nel video funziona solo con codec specifici   
    */
  //ALLA FINE va rilasciata con cvReleaseCapture(CvCapture* capture)
    return 0;
}