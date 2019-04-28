//g++ -std=c++11 matrix.c `pkg-config --libs --cflags opencv` -o matrix
#include "highgui.h"
#include "cv.h"


/*
------STRUTTURA INTERNA DELLA MATRICE IN OPENCV--------

- HEADER DELLA MATRICE 

typedef struct CvMat {
    int type; //Tipo di dato interno all matrice (profondita in bit) ad esempio CV8UC3 sono tre interi signed da 8 bit
    int step; //La lunghezza della riga in bytes
    int* refcount; // for internal use only
    union {
        uchar* ptr;
        short* s;
        int*
        i;
        float* fl;
        double* db;
    } data;
    union {
        int rows;
        int height; //Altezza della matrice
    };
    union {
        int cols;
        int width; //Larghezza della matrice
    };
} CvMat;


*/


int main()
{
    //Pag 51
    //Per creare una matrice si possono usare:
    /*
        -cvMat() --> passi tu il puntatore a data
        -cvCreateMat() ---> crea l'header e alloca memoria
        -cvCreateMatHeader() --> crea solo l'header della matrice senza allocare spazio per le informazioni
        -cvCreateData() ---> gestisce l'allocazione della memoria
    */
   //Alla fine bisogna rilasciare la memoria con cvReleaseMat(CvMat**)
   //Inoltre se vogliamo clonare una matrice si puoìò usare cvCloneMat(CvMat**)

    float vals[] = {0.8,-0.56,0.5,0.87};

    CvMat rotmat;
    cvInitMatHeader(&rotmat,2,2,CV32FC1,vals);


    //Accedere agli elementi della matrice
    CvMat* mat = cvCreateMat(5,5,CV_32FC1);
    float element_3_2 = CV_MAT_ELEM(*mat,float,3,2);
    
    //Settare un elemento
    element_3_2 = 7.7;
    *((float*)CV_MAT_ELEM_PTR(*mat,3,2)) = element_3_2;

    

    return 0;
}