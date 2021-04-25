#ifndef DIAS_H
#define DIAS_H
#include"Cube.h";


class Dias
{
    int len , wide , height , TX;
    public:
        Dias();
        Dias(int a , int b,int c , int tx){
            len = a , wide = b , height = c;
            TX = tx;
        }
        void drawDias();

    protected:
    private:
};

#endif // DIAS_H
