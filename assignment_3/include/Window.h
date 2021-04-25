#ifndef WINDOW_H
#define WINDOW_H
#include "Cube.h"

class Window
{
    int len , wide ;
    int type , cnt;
    public:
        Window();
        Window(int a,int b,int t=1,int ct=5){
            len = a ;
            wide = b;
            type = t;
            cnt = ct;
        }
        void drawCageWindow();
    protected:

    private:
};

#endif // WINDOW_H
