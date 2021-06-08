#ifndef SPHERE_H
#define SPHERE_H
#include "Cube.h"
#define M_PI acos(-1)
class Sphere
{
    double r;int lats,longs;
    Cube dummy;
    public:
        Sphere(double r , int lats , int longs);
        void drawSphere();
        void setLight();
        void setSphereColor(int color[]){
            dummy.setSurfaceLights(color);
        }
        void setShine(int shine){
            dummy.shines[0] = shine;
        }

    protected:

    private:
};

#endif // SPHERE_H
