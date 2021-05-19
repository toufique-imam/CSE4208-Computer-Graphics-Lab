#include "Cylinder.h"


void Cylinder::drawCylinder(){
    Cube cylinder(radius, 1.0, height);
    cylinder.setSurfaceLights(color);
    for(int i=0; i<360; i+=3)
    {
        glPushMatrix();
        {
            glRotatef(i , 0 , 0 ,1);
            cylinder.drawCube(false , false);
        }
        glPopMatrix();
    }
}
