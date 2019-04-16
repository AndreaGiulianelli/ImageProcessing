//g++ -std=c++11 aumento.c `pkg-config --libs --cflags opencv` -o aumento
#include "highgui.h"
#include "cv.h"
#include <stdio.h>

int main(int argc,char** argv)
{
    //Aumento il blu in un rettangolo

    IplImage* src;
    if(argc != 2)
    {
        printf("Inserire il numero giusto di parametri");
        exit(1);
    }

    src = cvLoadImage(argv[1],1);
    int x = 50;
    int y = 50;
    int width = 50;
    int height = 50;

    int add = 150;
    /*
    -----PASSO TUTTA L'IMMAGINE E AGGIUNGO COLORE------
    ptr[3*x] ---> Blu
    ptr[3*x+1] ---> Verde
    ptr[3*x+2] ---> Rosso

    for(int y = 0;y < src->height;y++)
    {
        uchar* ptr = (uchar*)(src->imageData + y*src->widthStep);
        for(int x = 0; x<src->width;x++)
        {
            ptr[3*x] = 255;
        }
    }*/

    cvSetImageROI(src,cvRect(x,y,width,height));
    cvAddS(src,cvScalar(add),src);

    /*
        Importante, esiste la funzione cvAddWeighted che esegue la seguente operazione:
            dst(x,y) = alpha * src1(x,y) + beta * src2(x,y) + gamma

        Prototipo:
            void cvAlphaWeighted(const CvArr* src1,double alpha,const CvArr* src2,double beta,double gamma,CvArr* dst);



        Può essere utile per unire due immagini
        Ad esempio:

        int main(int argc, char** argv)
        {
            IplImage *src1, *src2;
            if( argc == 9 && ((src1=cvLoadImage(argv[1],1)) != 0
            )&&((src2=cvLoadImage(argv[2],1)) != 0 ))
            {
                int x = atoi(argv[3]);
                int y = atoi(argv[4]);
                int width = atoi(argv[5]);
                int height = atoi(argv[6]);
                double alpha = (double)atof(argv[7]);
                double beta = (double)atof(argv[8]);
                cvSetImageROI(src1, cvRect(x,y,width,height));
                cvSetImageROI(src2, cvRect(0,0,width,height));
                cvAddWeighted(src1, alpha, src2, beta,0.0,src1);
                cvResetImageROI(src1);
                cvNamedWindow( “Alpha_blend”, 1 );
                cvShowImage( “Alpha_blend”, src1 );
                cvWaitKey();
            }
        return 0;
        }
    */

    cvResetImageROI(src);
    cvNamedWindow("Roi_Add",1);
    cvShowImage("Roi_Add",src);
    cvWaitKey();

    return 0;
}