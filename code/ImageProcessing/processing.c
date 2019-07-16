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
    
    return 0;
}