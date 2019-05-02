//g++ -std=c++11 mouseEvents.c `pkg-config --libs --cflags opencv` -o mouseEvents

#include "highgui.h"
#include "cv.h"


void my_mouse_callback(int event,int x,int y,int flags,void* param);

CvRect box;
bool drawing_box = false;

void draw_box(IplImage* img,CvRect rect)
{
    cvRectangle(
        img,
        cvPoint(box.x,box.y),
        cvPoint(box.x+box.width,box.y+box.height),
        cvScalar(0xff,0x00,0x00));
}

int main()
{
    //Callback del mouse
    /*
        void CvMouseCallback(
            int event,
            int x,
            int y,
            int flags,
            void* param
            );

        event è una costante che specifica l'azione da compiere
    */
   //Settare il callback
   /*
        void cvSetMouseCallback(
            const char* window_name,
            CvMouseCallback on_mouse,
            void* param = NULL
        );

        //Param sono le informazioni che devono essere passate al callback tutte le volte che viene richiamato
   */

    //Programma per usare il mouse per disegnare boxes sullo schermo

    return 0;
}