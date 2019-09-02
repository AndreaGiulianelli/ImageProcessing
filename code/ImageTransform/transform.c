//g++ -std=c++11 transform.c `pkg-config --libs --cflags opencv` -o transform
#include "highgui.h"

int main(int argc,char** argv)
{




    /*
    Convolution

    La convoluzione è una delle trasformazioni più usate, ed è qualcosa che si fa in ogni parte dell'immagine
    Il kernel è un array di coefficienti numerici con un punto di ancoraggio che è tipicamente al centro.
    La dimensione del kernel viene chiamata "support"

    void cvFilter2D(
        const CvArr* src,
        CvArr*      dst,
        const CvMat*  kernel,
        CvPoint anchor = cvPoint(-1,-1)   --> con -1, -1 si indica il centrale.
    );

    
    */

    IplImage* img = cvLoadImage(argv[1]);
    IplImage* imgDst = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,3);

    int vals[] = {1,0,-1,0,0,0,-1,0,1}; //E' un kernel per l'edge detenction trovato su wikipedia

    CvMat kernel;
    cvInitMatHeader(&kernel,3,3,CV_8SC1,vals);

    cvFilter2D(img,imgDst,&kernel);
    cvNamedWindow("Src");
    cvNamedWindow("Dst");
    cvShowImage("Src",img);
    cvShowImage("Dst",imgDst);
    cvWaitKey();


    /*
        Quando facciamo una convoluzione abbiamo il problema del mantenimento dei bordi.
        Per risolvere questo problema esiste una funzione che copia l'immagine in una leggermente più grande 
        e ricostruisce i bordi.

        void cvCopyMakeBorder(
            const CvArr* src,
            CvArr* dst,
            CvPoint offset,
            int bordertype,
            CvScalar value = cvScalarAll(0)
        );

        The offset argument tells cvCopyMakeBorder() where to place the copy of the original
        image within the destination image. Typically, if the kernel is N-by-N (for odd N) then
        you will want a boundary that is (N – 1)/2 wide on all sides or, equivalently, an image
        that is N – 1 wider and taller than the original. In this case you would set the offset to
        cvPoint((N-1)/2,(N-1)/2) so that the boundary would be even on all sides.

        The bordertype can be either IPL_BORDER_CONSTANT or IPL_BORDER_REPLICATE (see Figure 6-2).
        In the fi rst case, the value argument will be interpreted as the value to which all pixels
        in the boundary should be set. In the second case, the row or column at the very edge of
        the original is replicated out to the edge of the larger image. Note that the border of the
        test pattern image is somewhat subtle (examine the upper right image in Figure 6-2); in
        the test pattern image, there’s a one-pixel-wide dark border except where the circle pat-
        terns come near the border where it turns white. There are two other border types de-
        fined, IPL_BORDER_REFLECT and IPL_BORDER_WRAP , which are not implemented at this time
        in OpenCV but may be supported in the future.



    */



   /*
        Sobel 

        cvSobel(
            const CvArr* src,
            CvArr*      dst,
            int     xorder, (grado della derivata.. solitmente messe a 0,1,2)
            int     yorder,
            int     aperture_size = 3 (è la dimensione del kernel... deve essere dispari : 1,3,5,7 supportati)
        );
        Prima di fare il sobel è CONSIGLIABILE applicare un gaussian blur, e OBBLIGATORIO convertirla in grayscale

   */

    IplImage* imgSobel_x = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1); 
    IplImage* imgSobel_y = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1); 
    IplImage* imgSobel = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1); 
    IplImage* imgBlur = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,3);
    IplImage* imgGrayScale = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
    cvSmooth(img,imgBlur);
    cvCvtColor(imgBlur,imgGrayScale,CV_BGR2GRAY);
    cvShowImage("Src",imgGrayScale);
    cvSobel(imgGrayScale,imgSobel_x,1,0,3);
    cvSobel(imgGrayScale,imgSobel_y,0,1,3);

    cvNamedWindow("SobelX");
    cvNamedWindow("SobelY");
    cvShowImage("SobelX",imgSobel_x);
    cvShowImage("SobelY",imgSobel_y);

    //Cosi unisco sobel x e y
    cvAddWeighted(imgSobel_x,0.5,imgSobel_y,0.5,0.0,imgSobel);
    cvShowImage("Dst",imgSobel);
    cvWaitKey();
    cvDestroyWindow("SobelX");
    cvDestroyWindow("SobelY");
    
    /*
        Scharr Filter
        When the size of the kernel is 3, the Sobel kernel shown above may produce noticeable inaccuracies 
        (after all, Sobel is only an approximation of the derivative).
        OpenCV addresses this inaccuracy for kernels of size 3 by using the Scharr function. 
        This is as fast but more accurate than the standar Sobel function.
        Praticamente usa altri valori nel kernel.
        
        Per utilizzarlo occorre specificare come aperture_size il valore CV_SCHARR.
        Quando si vuole utilizzare un kernel 3x3 conviene sempre utilizzare lo scharr.

    */
    cvSobel(imgGrayScale,imgSobel_x,1,0,CV_SCHARR);
    cvSobel(imgGrayScale,imgSobel_y,0,1,CV_SCHARR);
    cvAddWeighted(imgSobel_x,0.5,imgSobel_y,0.5,0.0,imgSobel);
    cvShowImage("Dst",imgSobel);
    cvWaitKey();

    /*
        Laplace
        E' come una derivata seconda dell'immagine..
        E' come un secondo ordine del Sobel, infatti internamente OpenCv usa il sobel dentro Laplace
        
        void cvLaplace(
            const CvArr*    src,
            CvArr*          dst,
            int             aperture_size = 3
        );

        La sorgente puo essere 8-bit unsigned o 32-bit floating.
        La destinazione deve essere 16-bit signed o 32-bit floating.


    */

    IplImage* imgLaplace = cvCreateImage(cvGetSize(imgGrayScale),IPL_DEPTH_8U,1);
    cvLaplace(imgGrayScale,imgLaplace);
    cvShowImage("Dst",imgLaplace);
    cvWaitKey();


    /*  
        Canny
        E' un metodo per trovare i bordi di un immagine.
        E' solitamente chimato Canny edge detector.
        Se un pixel ha un gradiente sopra l'upper threshold allora viene accettato.
        Se è sotto viene scartato.
        Se è in mezzo per essere accettato deve essere collegato ad un pixel che è sopra l'upper
        E' indipendente dalla risoluzione, crea un bordo definito indipendente dalla risoluzione.

        void cvCanny(
            const CvArr*    img,
            CvArr*          edges,
            double          lowThresh,
            double          highThresh,
            int             aperture_size = 3
        );

        L'immagine di input deve essere grayscale e l'output anche.
        Spiegazione fatta bene:
        https://www.youtube.com/watch?v=sRFM5IEqR2w&list=PLzH6n4zXuckoRdljSlM2k35BufTYXNNeF&index=3

    */ 
    IplImage* imgCanny = cvCreateImage(cvGetSize(imgGrayScale),IPL_DEPTH_8U,1);
    cvCanny(imgGrayScale,imgCanny,50,100);
    cvShowImage("Dst",imgCanny);
    cvWaitKey();

    /*
        Hough Transform
        https://www.youtube.com/watch?v=G019Av7XhGo
        https://www.uio.no/studier/emner/matnat/ifi/INF4300/h09/undervisningsmateriale/hough09.pdf
        https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_lines/hough_lines.html
        Coordinate Polari: https://www.youmath.it/formulari/formulari-di-geometria-analitica/456-sistema-di-coordinate-polari.html
        
        CvSeq* cvHoughLines2(
            CvArr*  image,
            void*   line_storage,
            int     method,
            double  rho,
            double  theta,
            int     threshold,
            double  param1 = 0
            double  param2 = 0
        );

        line_storage è un puntatore a dove il risultato deve essere memorizzato,
        può essere un cvMemoryStorage oppure una matrice Nx1 (N diventa il massimo numero di linee ritornate).
        Method può essere CV_HOUGH_STANDARD, CV_HOUGH_PROBABILISTIC, CV_HOUGH_MULTI_SCALE.
        rho : The resolution of the parameter r in pixels. We use 1 pixel.
        theta: The resolution of the parameter \theta in radians. We use 1 degree (CV_PI/180) perchè la conversione rad = (gradi * pi) / 180
        threshold: The minimum number of intersections to “detect” a line
        What the function returns depends on how it was called. If the line_storage value was
        a matrix array, then the actual return value will be NULL. In this case, the matrix should
        be of type CV_32FC2 if the SHT or multi-scale HT is being used and should be CV_32SC4 if
        the PPHT is being used. In the first two cases, the ρ- and θ-values for each line will be
        placed in the two channels of the array. In the case of the PPHT, the four channels will
        hold the x- and y-values of the start and endpoints of the returned segments. In all of
        these cases, the number of rows in the array will be updated by cvHoughLines2() to cor-
        rectly reflect the number of lines returned.

    */
    IplImage* imgHough = cvLoadImage(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
    cvCanny(imgHough,imgHough,50,100);
    CvMat* line_storage = cvCreateMat(10,1,CV_32FC2);
    cvHoughLines2(imgHough,line_storage,CV_HOUGH_STANDARD,1,3.14/180,50);
    //[0] è il rho
    //[1] è theta

    for(int i=0;i<10;i++)
    {
        float* ptr = (float*) CV_MAT_ELEM_PTR(*line_storage,i,0);
        printf("%f - %f\n",ptr[0],ptr[1]);
        float rho = ptr[0];
        float theta = ptr[1];

        double a = cos(theta);
        double b = sin(theta);
        double x0 = a*rho;
        double y0 = b*rho;
        
        //Partendo da un punto mi calcolo due punti separati che stanno sulla stessa linea, in modo da disegnarla.
        //https://answers.opencv.org/question/21132/draw-the-lines-detected-by-cvhoughlines/
        CvPoint pt1 = CvPoint(cvRound(x0 + 1000 * (-b)), y0 + 1000* (a));
        CvPoint pt2 = CvPoint(cvRound(x0 - 1000 * (-b)), y0 - 1000* (a));
        cvLine(imgHough,pt1,pt2,CvScalar(255,255,255),2,8);
    }

    cvShowImage("Dst",imgHough);
    cvWaitKey();


    /*
        Hough Circle Transform
        In openCv utilizza una tecnica chiamata Hough gradient method.
        Funziona in questo modo: 
        Prima l'immagine viene fatta passare in un filtro di edge detenction (Ex. Canny).
        Dopodichè per ogni punto non-nero viene considerato il gradiente locale (facendo una Sobel x e y)
        Usando questo gradiente, ogni punto lungo la linea indicata dalla sua pendenza viene incrementato l'accomulatore.
        Allo stesso tempo tutti i punti a zero sono segnati perche potrebbero essere il centro del cerchio.


        CvSeq* cvHoughCircles(
            CvArr*  image,
            void*   circle_storage,
            int     method,
            double  dp,
            double  min_dist,
            double  param1,
            double  param2,
            int     min_radius = 0
            int     max_radius = 0
        );

        se come metodo di storage usiamo un array, deve essere di tipo CV_32FC3.
        dp è la risoluzione dell'accomulatore, cioè di dove cerca i cerchi: 
        -   1: mantiene la stessa risoluzione
        -   numero piu alto: viene ridotta di quel fattore x.

        min_dist è la minima distanza che può esistere tra due cerchi al fine di farli considerare dall'algoritmo come distinti
        Impostando come metodo CV_HOUGH_GRADIENT i parametri param1 e param2 sono i due threshold, il primo del canny il secondo dell'accomulatore

    */

    IplImage* imgHoughCircleNormal = cvLoadImage(argv[1]);
    IplImage* imgHoughCircle = cvCreateImage(cvGetSize(imgHoughCircleNormal),IPL_DEPTH_8U,1);
    cvCvtColor(imgHoughCircleNormal,imgHoughCircle,CV_BGR2GRAY);
    cvSmooth(imgHoughCircle,imgHoughCircle,CV_GAUSSIAN,5,5);
    cvCanny(imgHoughCircle,imgHoughCircle,220,250);

    /*
        Creo una locazione dinamica di oggetti...
        Praticamente sono liste linkate che permettono una veloce allocazione e deallocazione...

    */
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* results = cvHoughCircles(imgHoughCircle,storage,CV_HOUGH_GRADIENT,1,imgHoughCircle->width/10,150,100,0,0);
    
    for(int i = 0;i< results->total; i++)
    {
        float* p = (float*) cvGetSeqElem(results,i);
        CvPoint pt = CvPoint(cvRound(p[0]),cvRound(p[1]));
        cvCircle(imgHoughCircleNormal,pt,cvRound(p[2]),CV_RGB(0x00,0xff,0x00),3,8);
    }

    cvShowImage("Dst",imgHoughCircleNormal);
    cvWaitKey();

    /*
    Remap

    Il remapping é un processo che serve a prendere i pixel da un immagine e metterli in un altro
    posto nella nuova immagine.
    Ovviamente potrebbe essere necessario un interpolazione perché non sempre c'é una corrispondenza
    uno a uno con la sorgente e la destinazione.

    g(x,y) = f(h(x,y))
    g é l'immagine rimappata, f é l'immagine sorgente e h(x,y) é la funzione di mapping che opera su (x,y)

    Vari tipi di Remap: 
    https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/remap/remap.html
    https://www.peeknpoke.net/single-post/2016/10/29/OpenCV-remap-function

    void cvRemap(
        const CvArr* src,
        CvArr*       dst,
        const CvArr* mapx,
        const CvArr* mapy,
        int          flags = CV_INTER_LINER | CV_WARP_FILL_OUTLIERS,
        CvScalar     fillval = cvScalarAll(0)
    );

    mapx e mapy indica dove ogni pixel deve essere rilocato.
    La dimensione deve essere la stessa di src e dst... peró é single-channel,
    e solitamente di tipo float : IPL_DEPTH_32F

    le flags possono essere : 
    - CV_INTERN_NN          Nearest neighbor
    - CV_INTER_LINEAR       Bilinear(default)
    - CV_INTER_AREA         Pixel area resampling
    - CV_INTER_CUBIC        Bicubic interpolation

    You may also add (using the OR operator) the flag CV_WARP_FILL_OUTLIERS, whose effect
    is to fi ll pixels in the destination image that are not the destination of any pixel in the
    input image with the value indicated by the final argument fillval. In this way, if you
    map all of your image to a circle in the center then the outside of that circle would auto-
    matically be filled with black (or any other color that you fancy).
    */

    IplImage* img_srcRemap = cvLoadImage(argv[1]);
    IplImage* img_dstRemap = cvCreateImage(cvGetSize(img_srcRemap),img_srcRemap->depth,img_srcRemap->nChannels);
    CvMat* mapx = cvCreateMat(img_srcRemap->height,img_srcRemap->width,CV_32FC1);
    CvMat* mapy = cvCreateMat(img_srcRemap->height,img_srcRemap->width,CV_32FC1);

    for(int i=0; i<img_srcRemap->height;i++)
    {
        for(int j=0;j<img_srcRemap->width;j++)
        {
            //Prestare attenzione al fatto che il punto 0,0 non é in basso a sinistra ma
            //in alto a sinistra.
            *((float*)CV_MAT_ELEM_PTR(*mapx,i,j)) = j;
            *((float*)CV_MAT_ELEM_PTR(*mapy,i,j)) = img_srcRemap->height - i;
        }
    }

    cvRemap(img_srcRemap,img_dstRemap,mapx,mapy);
    cvShowImage("Dst",img_dstRemap);
    cvWaitKey();

    /*
        Le funzioni che permettono di stretchare, contorcere, contrarre o ruotare un'immagine
        sono dette geometric transform...
        Per superfici planari, ci sono due tipi di trasformazioni geometriche...
        - una usa una matrice 2x3: affine transforms
        - una usa una matrice 3x3: perspective transforms o homographies..

        Le transformazioni affini sono qualsiasi composizione di una applicazione lineare L con una
        translazione
        Esempi di affinitá sono le rotazioni, omotetie, translazioni, rototranslazioni, riflessioni.
        Le affinitá non sono necessariamnete isometrie, non preservano cioé angoli e distanze, mentre
        mantengono sempre il PARALLELISMO tra le rette.
        Perció sono per i parallelogrammi, e bastano tre punti per generare la matrice della trasfomazione affine,
        in quanto vengono mantenuti i parallelismi tra rette.

        https://homepages.inf.ed.ac.uk/rbf/HIPR2/affine.htm
        Spiegazione Coordinate Proiettive: http://www.sci.utah.edu/~acoste/uou/Image/project3/ArthurCOSTE_Project3.pdf
        Spiegazione trasformazioni affini semplice: http://www.frattali.it/trasformazioniaffini.htm
        https://www.math.it/tutorial/trasformazioniGeometriche/trasformazioniGeometriche.pdf
        
        
        DENSE AFFINE TRANSFORMATION
        Sono transformazioni affini, in cui l'immagine di destinazione (quella deformata)
        deve apparire naturale e lineare..
        Perció dopo aver effettuato la trasfomazione é necessario effettuare dell'interpolazione

        void cvWarpAffine(
            const CvArr* src,
            CvArr* dst,
            const CvMat** map_matrix,
            int flags = CV_INTER_LINEAR | CV_WARP_FILL_OUTLINERS,
            CvScalar fillval = cvScalarAll(0)
        );

        map_matrix é la matrice 2x3 necessaria per applicare la transformazione affine.
        Gli ultimi due argomenti controllano l'interpolazione.
        Ci sono anche dei flags addizionali (di solito aggiunti con degli OR) :
        - CV_WARP_FILL_OUTLIERS: é lo stesso che si usava per il Remap
        - CV_WARP_INVERSE_MAP: praticemte il warp (la distorsione) avviene al contrario..
                               invece che dall'src al dst, avviene dalla dst all'src.

        cvWarpAffine é un'operazione che impiega parecchie risorse e presenta un'overhead elevato rispetto
        alla semplice trasformazione affine..
        Perció per effettuare una semplice transformazione affine su un immagine a 8 bit per canale in sorgente
        e 32 bit per canale di destinazione, possiamo usare:

        void cvGetQuadrangleSubPix(
            const CvArr* src,
            CvArr* dst,
            const CvMat** map_matrix
        );

        Questa funzione effettua anche l'interpolazione.


        OpenCv provvede due funzioni per generare la matrice.
        La prima é per quando abbiamo due immagini che sono in relazione per qualche trasformazione affine
        o sappiamo in che modo vogliamo trasformarle partendo da due punti.

        CvMat* cvGetAffineTransform(
            const CvPoint2D32f*     pts_src,
            const CvPoint2D32f*     pts_dst,
            CvMat*                  map_matrix
        );

        pts_src e dst sono array di tre punti bidimensionali (x,y) 

        Il secondo modo per ottenere la map_matrix é tramite cv2DRotationMatrix()
        praticamente permette di ottenere la matrice per effettuare una rotazione attorno 
        ad uno specifico punto, di uno specifico angolo e addirittura di effettuare un'eventuale scaling

        CvMat* cv2DRotationMatrix(
            CvPoint2D32f    center,
            double          angle,
            double          scale,
            CvMat*          map_matrix
        );

        center é il punto centrale di rotazione.
        angle é l'angolo di rotazione, e scale é l'eventuale rescaling.
    */

    CvPoint2D32f srcTri[3],dstTri[3];
    CvMat* rot_mat = cvCreateMat(2,3,CV_32FC1);
    CvMat* warp_mat = cvCreateMat(2,3,CV_32FC1);
    IplImage* src;
    IplImage* dst;

    src = cvLoadImage(argv[1]);
    dst = cvCloneImage(src);
    dst->origin = src->origin;
    cvZero(dst);

    //Warp matrix

   srcTri[0].x = 0;
   srcTri[0].y = 0;
   srcTri[1].x = src->width - 1;
   srcTri[1].y = 0;
   srcTri[2].x = 0;
   srcTri[2].y = src->height - 1;

    dstTri[0].x = 0;
    dstTri[0].y = src->height*0.33;
    dstTri[1].x = src->width*0.85;
    dstTri[1].y = src->height*0.25;
    dstTri[2].x = src->width*0.15;
    dstTri[2].y = src->height*0.7;

    cvGetAffineTransform(srcTri,dstTri,warp_mat);
    cvWarpAffine(src,dst,warp_mat);
    cvShowImage("Dst",dst);
    cvWaitKey();
    
    cvCopy(dst,src);

    //Rotation Matrix

    CvPoint2D32f center = cvPoint2D32f(src->width / 2,src->height / 2);
    double angle = -50.0;
    double scale = 0.6;
    cv2DRotationMatrix(center,angle,scale,rot_mat);
    cvWarpAffine(src,dst,rot_mat);
    cvShowImage("Dst",dst);
    cvWaitKey();

    /*
        Per effettuare la transformazione di una lista di punti, si puó usare la funzione cvTrasform()

        void cvTransform(
            const CvArr*    src,
            CvArr*          dst,
            const CvMat*    transmat,
            const CvMat*    shiftvec = NULL
        );

        In general, src is an N-by-1 array with Ds channels, where N is the number of points to
        be transformed and Ds is the dimension of those source points. The output array dst
        must be the same size but may have a different number of channels, Dd . 
        The transformation matrix transmat is a Ds-by-Dd matrix that is then applied to every element of src,
        after which the results are placed into dst . The optional vector shiftvec, if non-NULL, must
        be a Ds-by-1 array, which is added to each result before the result is placed in dst.
        In our case of an affine transformation, there are two ways to use cvTransform() that
        depend on how we’d like to represent our transformation. In the fi rst method, we decompose
        our transformation into the 2-by-2 part (which does rotation, scaling, and
        warping) and the 2-by-1 part (which does the transformation). Here our input is an
        N-by-1 array with two channels, transmat is our local homogeneous transformation,
        and shiftvec contains any needed displacement. The second method is to use our usual
        2-by-3 representation of the affi ne transformation. In this case the input array src is a
        three-channel array within which we must set all third-channel entries to 1 (i.e., the
        points must be supplied in homogeneous coordinates). Of course, the output array will
        still be a two-channel array.

    */

    /* 
        Perspective Transformation
        
        Dimostrazione pratica: https://www.youtube.com/watch?v=PtCQH93GucA

        Per applicarlo alle immagini: cvWarpPerspective()

        void cvWarpPerspective(
            const CvArr*    src,
            CvArr*          dst,
            const CvMat*    map_matrix,
            int             flags = CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS,
            CvScalar        fillval = cvScalarAll(0)
        );

        OTTENERE LA MAP_MATRIX

        CvMat* cvGetPerspectiveTransform(
            const CvPoint2D32f*     pts_src,
            const CvPoint2D32f*     pts_dst,
            CvMat*                  map_matrix
        );

        Stavolta peró l'array deve essere di 4 punti


        Per una lista di punti possiamo utilizzare

        void cvPerspectiveTransform(
            const CvArr*    src,
            CvArr*          dst,
            const CvMar*    mat
        );
    */


   /*
        CatToPolar and PolarToCat

        void cvCartToPolar(
            const CvArr*    x,
            const CvArr*    y,
            CvArr*  magnitude,
            CvArr*  angle = NULL,
            int angle_in_degrees = 0
        );  

        void cvPolarToCart(
            const CvArr*    magnitude,
            const CvArr*    angle,
            CvArr*          x,
            CvArr*          y,
            int angle_in_degrees = 0
        );

   */


    /*
        LOG-POLAR TRANSFORM

        Spiegazione log-polar: https://sthoduka.github.io/imreg_fmt/docs/log-polar-transform/        

        void cvLogPolar(
            const CvArr*    src,
            CvArr*          dst,
            CvPoint2D32f    center,
            double          m,
            int             flags = CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS
        );

        Le immagini sorgente e destinazione possono essere ad uno / tre canali a colori o grayscale.
        Center indica il punto centrale della trasformazione log-polar.
        m é il fattore di scala da dare a rho.
        Se voglio passare da logPolar a cartesiane devo mettere al posto di CV_WARP_FILL_OUTLIERS, CV_WARP_INVERSE_MAP.

    */

    IplImage* imgCartesian = cvLoadImage(argv[1]);
    imgCartesian->origin = 0; //Origine nel punto top-left
    IplImage* imgLogPolar = cvCreateImage(cvGetSize(imgCartesian),imgCartesian->depth,imgCartesian->nChannels);
    IplImage* imgInverseLogPolar = cvCreateImage(cvGetSize(imgCartesian),imgCartesian->depth,imgCartesian->nChannels);
    cvLogPolar(imgCartesian,imgLogPolar,cvPoint2D32f(0,0),50);
    cvLogPolar(imgLogPolar,imgInverseLogPolar,cvPoint2D32f(0,0),50,CV_INTER_LINEAR | CV_WARP_INVERSE_MAP);
    cvShowImage("Dst",imgLogPolar);
    cvWaitKey();
    cvShowImage("Dst",imgInverseLogPolar);





    cvWaitKey();
    cvDestroyWindow("Src");
    cvDestroyWindow("Dst");
    cvReleaseImage(&img);
    cvReleaseImage(&imgDst);
    cvReleaseImage(&imgSobel);
    cvReleaseImage(&imgSobel_x);
    cvReleaseImage(&imgSobel_y);
    cvReleaseImage(&imgLaplace);
    cvReleaseImage(&imgCanny);
    cvReleaseImage(&imgHough);
    cvReleaseImage(&imgHoughCircle);
    cvReleaseImage(&img_srcRemap);
    cvReleaseImage(&img_dstRemap);
    cvReleaseImage(&src);
    cvReleaseImage(&dst);
    cvReleaseImage(&imgLogPolar);

    cvReleaseMemStorage(&storage); //Libero la memoria allocata con cvCreateMemStorage

    
    return 0;
}