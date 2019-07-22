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

        Quando si lavora con maschere o immagini booleane le operazioni di dilatazione o erosione
        sono spesso suffiecienti.
        Per le immagini grayscale o a colori si utilizzano tante altre operazioni tutte gestite da:

        void cvMorphologyEx(
            const CvArr* src,
            CvArr* dst,
            CvArr* temp,
            IplConvKernel* element
            int operation,
            int iteration = 1
        )
        temp è un'array che deve avere la stessa dimensione di src.. e serve solo con alcune operazioni
        La lista delle operazioni e se necessitano dell'array è a pag. 136


        -OPENING / CLOSING
            CV_MOP_OPEN / CV_MOP_CLOSE
            OPEN: effettua prima un'erosione poi una dilatazione
                  Praticamente viene spesso utilizzato quando dobbiamo analizzare un'immagine al microscopio
                  e si devono contare le cellule...
                  Open viene utilizzato per separare le cellule prima di contarle
                  Vengono rimosse le piccole zone luminose
            CLOSE: effetua prima una dilatazione poi un erosione
                    Viene utilizzato per ridurre il rumore nelle componenti connesse
                    Vengono unite le zone luminose

        -Gradiente
            gradient(src) = dilate(src) - erode(src)
            Si usa solitamente per isolare il perimetro degli oggetti (rendendolo luminoso) in modo da trattarle come un unico oggetto
        

        -Top Hat / Black Hat
            Servono per isolare rispettivamente aree luminose o scure rispetto ai pixel vicini
            Si usano per oggetti che esibiscono cambi di luminosità.
            
            TopHat(src) = src - open(src)
            BlackHat(src) = close(src) - src

        

        FLOOD FILL
        Questa funzione viene utilizzata per isolare porzioni di immagini da utilizzare più tardi
        Si può utilizzare anche per creare maschere da immagini in input
        Praticamente colora una zona di pixel che rientrano in uno specifico range

        void cvFloodFill(
            IplImage* img,
            CvPoint seedPoint,
            CvScalar newVal,
            CvScalar loDiff = cvScalarAll(0),
            CvScalar upDiff = cvScalarAll(0),
            CvConnectedComp* comp = NULL,
            int flags = 4,
            CvArr* mask = NULL
        )

        

        




   */
    
    return 0;
}
