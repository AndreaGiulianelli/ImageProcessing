//g++ -std=c++11 processing.c `pkg-config --libs --cflags opencv` -o processing

#include "highgui.h"

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
    https://homepages.inf.ed.ac.uk/rbf/HIPR2/morops.htm
    -Dilatation and Erosion
        https://www.youtube.com/watch?v=7-FZBgrW4RE
        https://www.youtube.com/watch?v=HcpxKCdzjdY (Mostra come utilizzare gli structuring element)
        La dilatazione, come dice il nome provvede ad aggiungere pixel nei bordi di un immagine
        in modo da ingrandirla o addensarla.
        Chiude i buchini del rumore neri.. Perche allargando l'immagine li ingloba
        Riempie
        
        L'erosione, riduce il numero di pixel dai bordi dell'immagine per contrarre l'immagine e farla più "fine" 
        Riesce a ridurre il rumore quando sono causati da bianco in quanto non rispettando la maschera li fa neri e quindi li chiude
        In caso ad esempio di cerchi bianchi con linee che attraversano tutta l'immagine bianche riesce ad eliminare le linee e rendere
        chiari i cerchi bianchi...

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

        //CUSTOM STRUCTURING ELEMENT
        int values_dilation[1225];
        for(int i = 0; i<1225;i++)
        {
            values_dilation[i] = 1;
        }
        IplConvKernel* structuring_element_dilation = cvCreateStructuringElementEx(35,35,17,17,CV_SHAPE_CUSTOM,values_dilation);


        IplImage* img_dilation = cvLoadImage("whiteRectBlackHole.jpg",CV_LOAD_IMAGE_GRAYSCALE);
        IplImage* img_post_dilation = cvCreateImage(cvSize(img_dilation->width,img_dilation->height),img_dilation->depth,img_dilation->nChannels);
        cvDilate(img_dilation,img_post_dilation,structuring_element_dilation);
        cvNamedWindow("Immagine");
        cvNamedWindow("Immagine Dilatata");
        cvShowImage("Immagine", img_dilation);
        cvShowImage("Immagine Dilatata",img_post_dilation);

        cvWaitKey();


        IplImage* img_grayscale = cvLoadImage(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
        IplImage* img_eroded = cvCreateImage(cvSize(img_grayscale->width,img_grayscale->height),img_grayscale->depth,img_grayscale->nChannels);
        cvErode(img_grayscale,img_eroded);
        cvNamedWindow("Immagine");
        cvNamedWindow("Immagine Erosa");
        cvShowImage("Immagine",img_grayscale);
        cvShowImage("Immagine Erosa",img_eroded);
        
        
        cvWaitKey();
        
        
        //CUSTOM STRUCTURING ELEMENT
        int values[64];
        for(int i = 0; i<64;i++)
        {
            values[i] = 1;
        }
        IplConvKernel* structuring_element = cvCreateStructuringElementEx(8,8,4,4,CV_SHAPE_CUSTOM,values);

        //Provare con immagine: circle3
        cvErode(img_grayscale,img_eroded,structuring_element);
        cvShowImage("Immagine Erosa",img_eroded);

        cvWaitKey();

        

/*

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
        
        https://homepages.inf.ed.ac.uk/rbf/HIPR2/morops.htm
        -OPENING / CLOSING
            CV_MOP_OPEN / CV_MOP_CLOSE
            OPEN: effettua prima un'erosione poi una dilatazione
                  Praticamente viene spesso utilizzato quando dobbiamo analizzare un'immagine al microscopio
                  e si devono contare le cellule...
                  Open viene utilizzato per separare le cellule prima di contarle
                  Vengono rimosse le piccole zone luminose, oppure rimuove tutti gli oggetti piccoli e insignificanti nello sfondo
            CLOSE: effetua prima una dilatazione poi un erosione
                    Viene utilizzato per ridurre il rumore nelle componenti connesse
                    Vengono unite le zone luminose
                    Rimuove i piccoli fori
                    Riempie
*/      
        
        cvMorphologyEx(img_grayscale,img_eroded,NULL,structuring_element,CV_MOP_OPEN);
        cvMorphologyEx(img_dilation,img_post_dilation,NULL,structuring_element_dilation,CV_MOP_CLOSE);
        cvShowImage("Immagine Erosa",img_eroded);
        cvShowImage("Immagine Dilatata",img_post_dilation); //Se si nota eseguendo.. mantiene le proporzioni meglio


/*  
        -Gradiente
        https://www.meccanismocomplesso.org/opencv-python-image-edge-gradient-analysis/

            gradient(src) = dilate(src) - erode(src)
            Nelle immagini booleane serve semplicemente ad isolare il perimetro delle macchie esistenti
            Nelle immagini grayscale indica quanto velocemente la luminosità dell'immagine varia.
            In questo modo possiamo delimitare il perimetro di aree luminose.
            Il poter calcolare il gradiente di un colore è un ottimo strumento per calcolare i bordi di un’immagine.
            Infatti il nostro occhio riesce a distinguere i contorni di una figura presente in un’immagine proprio grazie 
            ai salti tra un colore in un altro. 
            Inoltre il nostro occhio è in grado di percepire le profondità proprio grazie alle varie 
            sfumature di colore che vanno dal chiaro allo scuro, appunto il gradiente.


*/

/*
        -Top Hat / Black Hat
            Servono per isolare rispettivamente aree luminose o scure rispetto ai pixel vicini
            Si usano per oggetti che esibiscono cambi di luminosità.

            TopHat: enfatizza gli elementi luminosi nello sfondo nero.
            BlackHat: enfatizza gli elementi neri nello sfondo bianco.
            
            TopHat(src) = src - open(src)
            BlackHat(src) = close(src) - src
*/  
        IplImage* img_star = cvLoadImage("star.jpg");
        IplImage* img_topHat = cvCreateImage(cvSize(img_star->width,img_star->height),img_star->depth,img_star->nChannels);
        cvMorphologyEx(img_star,img_topHat,NULL,structuring_element,CV_MOP_BLACKHAT);


        cvNamedWindow("Star");
        cvNamedWindow("Star BlackHat");
        cvShowImage("Star",img_star);
        cvShowImage("Star BlackHat",img_topHat);
        cvWaitKey();

/*
        

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

  /*
        RESIZE
        A volte abbiamo la necessita di convertire l'immagine in un'altra di dimensione diversa.
        Oppure vogliamo fare un zoom in/out.
        Per fare entrambe le cose si può usare cvResize()
        Questa funzione metterà l'immagine sorgente esattamente dentro le dimensioni dell'immagine di destinazione
        Se abbiamo impostato il ROI dentro l'immagine sorgente, il ROI verrà ridimensionato per mantere il suo significato,
        se invece il ROI è settato nell'immagine di destinazione, allora l'immagine sorgente verrà ridimensionata all'interno del ROI

        void cvResize(
            const CvArr*    src,
            CvArr*          dst,
            int             interpolation = CV_INTER_LINEAR
        );

        L'ultimo argomento è il modo di interpolazione, le altre opzioni sono:
        - CV_INTER_NN       Nearest neighbor
        - CV_INTER_LINEAR   Bilinear
        - CV_INTER_AREA     Pixel area re-sampling
        - CV_INTER_CUBIC    Bicubic interpolation (La più utilizzata, ma non è sempre la più giusta... dipende dalla situazione)
                            Bicubic interpolation viene utilizzata quando la velocità di esecuzione non è un problema (Quindi un video)


        https://www.youtube.com/watch?v=AqscP7rc8_M&t=454s
        https://www.youtube.com/watch?v=poY_nGzEEWM

  */


    IplImage* img_beforeResize = cvLoadImage("whiteRectBlackHole.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    IplImage* img_afterResize = cvCreateImage(cvSize(img_beforeResize->width * 2,img_beforeResize->height * 2),img_beforeResize->depth,img_beforeResize->nChannels);
    cvResize(img_beforeResize,img_afterResize);
    cvNamedWindow("Before Resize");
    cvNamedWindow("After Resize");
    cvShowImage("Before Resize",img_beforeResize);
    cvShowImage("After Resize",img_afterResize);
    


    /*
        IMAGE PYRAMIDS

        Una piramide di immagini è una collezione di immagini tutte derivanti da una singola immagine.
        Sono ridotte di risoluzione fino alla dimensione desiderata, anche un singolo pixel!
        Ci sono due tipi di piramidi: 
        - Gaussian: usata per fare il downsample di immagini
        - Laplacian: è necessaria quando vogliamo ricostruire una immagine soprastante nella piramide a partire da un immagine piu un basso

        void cvPyrDown(
            IplImage* src,
            IplImage* dst,
            IplFilter filter = IPL_GAUSSIAN_5x5
        );

        Possiamo anche trasformare un immmagine che è il doppio più grande in larghezza e altezza

        void cvPyrUp(
            IplImage* src,
            IplImage* dst,
            IPlFilter filter = IPL_GAUSSIAN_5x5
        );

        In this case the image is first upsized to twice the original in each dimension, with the
        new (even) rows filled with 0s. Thereafter, a convolution is performed with the given
        filter (actually, a filter twice as large in each dimension than that specified*) to approxi-
        mate the values of the “missing” pixels.
        We noted previously that the operator PyrUp() is not the inverse of PyrDown() . This
        should be evident because PyrDown() is an operator that loses information. In order to
        restore the original (higher-resolution) image, we would require access to the informa-
        tion that was discarded by the downsampling.

        Le piramidi di Laplace funzionano cosi
        L1 = g1 - EXPAND[g2]
        L2 = g2 - EXPAND[g3]

        Praticamente ogni livello della piramide di Laplace è dato dalla differenza
        tra il livello i-1 e il livello i della piramide di gauss (che ovviamente avrà i contorni più sfuocati a 
        causa della convulazione). 
        Perciò le piramidi di Laplace definiscono un po' i contorni di un'immagine 
    */

    IplImage* img_beforePyrDown = cvLoadImage("red_eyes.jpg");
    cvNamedWindow("ImageBedorePyrDown");
    cvShowImage("ImageBedorePyrDown",img_beforePyrDown);
    IplImage* img_PyrDown = cvCreateImage(cvSize(img_beforePyrDown->width / 2,img_beforePyrDown->height / 2),img_beforePyrDown->depth,img_beforePyrDown->nChannels);
    cvPyrDown(img_beforePyrDown,img_PyrDown);
    cvNamedWindow("ImagePyrDown");
    cvShowImage("ImagePyrDown",img_PyrDown);

    IplImage* img_PyrUp = cvCreateImage(cvSize(img_beforePyrDown->width,img_beforePyrDown->height),img_beforePyrDown->depth,img_beforePyrDown->nChannels);
    cvPyrUp(img_PyrDown,img_PyrUp);

    IplImage* firstLevelLaplace = cvCreateImage(cvSize(img_beforePyrDown->width,img_beforePyrDown->height),img_beforePyrDown->depth,img_beforePyrDown->nChannels);
    cvSub(img_beforePyrDown,img_PyrUp,firstLevelLaplace);

    cvNamedWindow("ImagePyrUp");
    cvShowImage("ImagePyrUp",img_PyrUp); //Da notare l'effetto della convulazione del kernel che crea l'effetto blur
    cvNamedWindow("FirstLevelLaplace");
    cvShowImage("FirstLevelLaplace",firstLevelLaplace); //Si nota che Laplace definisce i bordi dell'immagine   


    

    /*  
        THRESHOLD

        double cvThreshold(
            CvArr* src,
            CvArr* dst,
            double threshold,
            double max_value,
            int threshold_type
        );

        Tipi di threshold (M = max_value):

        CV_THRESH_BINARY        dst(i) = (src(i) > T) ? M : 0
        CV_THRESH_BINARY_INV    dst(i) = (src(i) > T) ? 0 : M
        CV_THRESH_TRUNC         dst(i) = (src(i) > T) ? M : src(i)
        CV_THRESH_TOZERO_INV    dst(i) = (src(i) > T) ? 0 : src(i)
        CV_THRESH_TOZERO        dst(i) = (src(i) > T) ? src(i) : 0

    */

    //Sommo tutti e tre i canali di un'immagine in un'immagine bianco e nero
    IplImage* r = cvCreateImage(cvGetSize(img_beforePyrDown),IPL_DEPTH_8U,1);
    IplImage* g = cvCreateImage(cvGetSize(img_beforePyrDown),IPL_DEPTH_8U,1);
    IplImage* b = cvCreateImage(cvGetSize(img_beforePyrDown),IPL_DEPTH_8U,1);

    cvSplit(img_beforePyrDown,r,g,b,NULL);

    IplImage* s = cvCreateImage(cvGetSize(img_beforePyrDown),IPL_DEPTH_8U,1);
    cvAddWeighted(r,1./3.,g,1./3.,0.0,s);
    cvAddWeighted(s,2./3.,b,1.3/3.,0.0,s);

    IplImage* dstThreshold = cvCreateImage(cvGetSize(img_beforePyrDown),IPL_DEPTH_8U,1);
    cvShowImage("Weighted",s);
    cvThreshold(s,dstThreshold,100,255,CV_THRESH_BINARY);
    cvShowImage("Threshold",dstThreshold);


    cvWaitKey();
    cvReleaseImage(&img_dilation);
    cvReleaseImage(&img);
    cvReleaseImage(&img_eroded);
    cvReleaseImage(&img_post_dilation);
    cvReleaseImage(&img_star);
    cvReleaseImage(&img_topHat);
    cvReleaseImage(&img_beforeResize);
    cvReleaseImage(&img_afterResize);
    cvReleaseImage(&firstLevelLaplace);
    cvDestroyWindow("Immagine");
    cvDestroyWindow("Immagine Dilatata");
    cvDestroyWindow("Immagine Erosa");
    cvDestroyWindow("Star");
    cvDestroyWindow("Star TOPHAT");
    cvDestroyWindow("FirstLevelLaplace");
    cvWaitKey();
    return 0;
}
