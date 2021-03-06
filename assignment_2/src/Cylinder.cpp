#include "Cylinder.h"


void Cylinder::drawCylinder(){
    Cube cylinder(radius, 1.0, height);
    cylinder.setSurfaceColors(color);
    for(int i=0; i<360; i+=6)
    {
        glPushMatrix();
        {
            glRotatef(i , 0 , 0 ,1);
            cylinder.drawCube(false , false);
        }
        glPopMatrix();
    }
}
