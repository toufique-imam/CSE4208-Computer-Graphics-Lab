#ifndef CYLINDER_H
#define CYLINDER_H
#include "Cube.h"

class Cylinder
{
    float radius , height;
    int color[3];
    public:
        Cylinder(){}
        Cylinder(int r , int h){
            radius = r;
            height = h;
        }
        Cylinder(float r , float h){
            radius = r;
            height = h;
        }
        void drawCylinder();
        void setCylinderColor(int c[]){
            color[0] = c[0];
            color[1] = c[1];
            color[2] = c[2];
        }

    protected:

    private:
};

#endif // CYLINDER_H
