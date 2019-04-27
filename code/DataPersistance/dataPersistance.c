//g++ -std=c++11 dataPersistance.c `pkg-config --libs --cflags opencv` -o dataPersistance

#include "highgui.h"
#include "cv.h"

int main()
{
    //Salvare una Matrice CvMat
    float the_matrix_data[5][5] = {
    {1.5,0,0,0,0},
    {0,1.0,0,0,0},
    {0,0,1.0,0,0},
    {0,0,0,1.0,0},
    {0,0,0,0,1.0} };

    CvMat A = cvMat(5,5,CV_32F,the_matrix_data);

    cvSave("my_matrix.xml",&A);


    //Caricare in memoria una matrice salvata
    CvMat* A1 = (CvMat*) cvLoad("my_matrix.xml");


    //Scrivere file con più tipi di dato: CvFileStorage (pag. 100 del libro)

    return 0;
}
