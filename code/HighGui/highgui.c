//g++ -std=c++11 highgui.c `pkg-config --libs --cflags opencv` -o highgui
#include "highgui.h"

int main(int argc,char** argv)
{

    if(argc!=2)
    {
        printf("Inserisci un numero valido di parametri\n");
        exit();
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


    //SALVARE UN'IMMAGINE
    //int cvSaveImage(nome,CvArr* image)
    //Ritorna 1 se il salvataggio è stato eseguito correttamente, 0 in caso contrario
    cvSaveImage("img.jpg",img);


    //MOSTRARE IMMAGINE
    


    //Quando creo una finestra devo anche deallocarla con la funzione cvDestroyWindow()
    cvDestroyWindow("Finestra");





    

    return 0;
}