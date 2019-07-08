//g++ -std=c++11 buttons.c `pkg-config --libs --cflags opencv` -o buttons
#include "highgui.h"

void switch_callback(int position)
{
    if(position == 0)
    {
        //switch_off_function();
        printf("OFF\n");
    }
    else
    {
        //switch_on_function();
        printf("ON\n");
    }
    
}

int g_switch_value = 0;

int main()
{
    //OpenCV non da la possibilita di creare bottoni... Quindi si usano slider con due posizioni
    cvNamedWindow("Demo Window",CV_WINDOW_AUTOSIZE);

    cvCreateTrackbar("Switch","Demo Window",&g_switch_value,1,switch_callback);

    while(1)
    {
        if(cvWaitKey(15)==27) break;
    }

    return 0;
}