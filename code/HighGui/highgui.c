//g++ -std=c++11 highgui.c `pkg-config --libs --cflags opencv` -o highgui
#include "highgui.h"

int main(int argc,char** argv)
{

    if(argc!=2)
    {
        printf("Inserisci un numero valido di parametri\n");
        exit(1);
    }

    //Creo una finestra:
    /*
        -Primo parametro: nome
        -Secondo parametro: 0 oppure CV_WINDOW_AUTOSIZE
                            Con 0 la finestra non si dimensionerà automaticamente quando carico una nuova immagine
    */
    cvNamedWindow("Finestra",CV_WINDOW_AUTOSIZE);


    //Per ridimensionare una finestra
    //cvResizeWindow("Nome",larghezza,altezza)
    cvResizeWindow("Finestra",100,50);

    //Per SPOSTARE una FINESTRA
    //Mette l'angolo spostato in alto a destra alla posizione x,y
    cvMoveWindow("Finestra",500,500);


    //CARICARE UN'IMMAGINE
    //IplImage* cvLoadImage(nome,iscolor = CV_LOAD_IMAGE_COLOR)
    /*
    Quando il secondo canale non è specificato l'immagine verrà convertita 
    in un'immagine a tre canali.
    Se specifico un parametro:
        - CV_LOAD_IMAGE_ANYDEPTH : profondita diversa da 8 bit per canale
      - CV_LOAD_IMAGE_GRAYSCALE : converte l'immagine in grayscale
        - CV_LOAD_IMAGE_ANYCOLOR : carica l'immagine così com'è senza effettuare conversioni rispetto ai colori
        - CV_LOAD_IMAGE_UNCHANGED : carica l'immagine rispettando i colori e la profondità originale
    Ad esempio se volessi caricare un'immagine a colori con profondità 16 bit: CV_LOAD_IMAGE_COLOR | CV_LOAD_IMAGE_ANYDEPTH.
    */
    IplImage* img = cvLoadImage(argv[1]);
    IplImage* img_dst = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);

    //SALVARE UN'IMMAGINE
    //int cvSaveImage(nome,CvArr* image)
    //Ritorna 1 se il salvataggio è stato eseguito correttamente, 0 in caso contrario
    cvSaveImage("img.jpg",img);


    //MOSTRARE IMMAGINE
    //cvShowImage(const char* nomeFinestra, const CvArr* image);
    cvShowImage("Finestra",img);


    //CONVERTIRE IMMAGINE
    //Converte l'immagine src in un'immagine con le caratteristiche definite nell'header della dst.
    //Il terzo parametro indica se bisogna fare un flip verticale
    //In questo caso passo da 3 canali (RGB) ad un canale (grayscale)
    cvConvertImage(img,img_dst,0);

    //WAIT KEY
    //Aspetta il tempo specificato in millisecondi come parametro 
    //Se entro quel tempo è premuto un tasto, allora la funzione lo restituisce come parametro
    //Altrimenti restituisce 0
    //Se lo chiamo senza parametri, aspetta all'infinito finchè non viene premuto un tasto
    cvWaitKey(1000);

    cvShowImage("Finestra",img);
    cvNamedWindow("Finestra1");
    cvShowImage("Finestra1",img_dst);
    cvWaitKey();
    
    //Rilasciare immagine
    cvReleaseImage(&img);
    cvReleaseImage(&img_dst);
    //Quando creo una finestra devo anche deallocarla con la funzione cvDestroyWindow()
    cvDestroyWindow("Finestra");
    cvDestroyWindow("Finestra1");
    //Deallocare e chiudere tutte le finestre in un solo colpo
    //cvDestroyAllWindows()






    

    return 0;
}