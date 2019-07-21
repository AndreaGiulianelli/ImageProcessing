//g++ -std=c++11 processing.c `pkg-config --libs --cflags opencv` -o processing

#include "highgui.c"

int main(int argc,char** argv)
{
    if(argc != 2)
    {
        printf("Inserire il numero corretto di parametri");
        exit(1);
    }
    IplImage* img = cvLoadImage(argv[1]);

    //SMOOTHING
    /*
        Lo smoothing viene utilizzato per ridurre il rumore o gli errori della camera

    */
    /*
        void cvSmooth(
            const CvArr*    src,
            CvArr**         dst,
            int smoothtype = CV_GAUSSIAN
            int param1 = 3
            int param2 = 0
            int param3 = 0
            int param4 = 0
        );

        Il valore dei param1/2/3/4 dipende dal smoothtype selezionato
        Tabella a pagina 126
        
        IMPORTANTE:
        Il filtro di Gauss non mantiene i bordi.
        Il filtro bilaterale invece li mantiene.
    */

   /*
    IMAGE MORPHOLOGY

    -Dilatation and Erosion
        https://www.youtube.com/watch?v=7-FZBgrW4RE
        https://www.youtube.com/watch?v=HcpxKCdzjdY (Mostra come utilizzare gli structuring element)
        La dilatazione, come dice il nome provvede ad aggiungere pixel nei bordi di un immagine
        in modo da ingrandirla o addensarla
        L'erosione, riduce il numero di pixel dai bordi dell'immagine per contrarre l'immagine e farla più "fine" 

        void cvErode(
            IplImage* src,
            IplImage* dst,
            IplConvKernel* B=NULL
            int iterations = 1
        )

        void cvDilate(
            IplImage* src
            IplImage* dst
            IplConvKernel* B=NULL
            int iterations = 1
        )

        Quando B (il kernel, o structuring element) non viene passato, è di default un kernel 3x3 con un ancora centrale

    
    -Creare un proprio kernel
        Il kernel ha un tipo: IplConvKernel
        Inoltre i kernel sono allocati con cvCreateStructuringElementEx() 
        e deallocati con cvReleaseStructuringElement()

        IplConvKernel* cvCreateStructuringElementEx(
            int cols,
            int rows,
            int anchor_x,
            int anchor_y,
            int shape,
            int* values = NULL)
        (PAG. 135)

        

   */
    
    return 0;
}
