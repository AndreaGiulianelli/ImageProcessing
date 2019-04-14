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
    cvSetImageROI(src,cvRect(x,y,width,height));
    cvAddS(src,cvScalar(add),src);
    cvResetImageROI(src);
    cvNamedWindow("Roi_Add",1);
    cvShowImage("Roi_Add",src);
    cvWaitKey();

    return 0;
}