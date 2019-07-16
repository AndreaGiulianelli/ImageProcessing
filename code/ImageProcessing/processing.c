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
        
    */
    
    return 0;
}