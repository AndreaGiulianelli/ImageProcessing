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

    //Cosi unisco sobel x e y
    cvAddWeighted(imgSobel_x,0.5,imgSobel_y,0.5,0.0,imgSobel);
    cvShowImage("Dst",imgSobel);
    cvWaitKey();

    cvDestroyWindow("Src");
    cvDestroyWindow("Dst");
    cvReleaseImage(&img);
    cvReleaseImage(&imgDst);
    cvReleaseImage(&imgSobel);

    
    return 0;
}