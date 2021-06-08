#include "Cylinder.h"


void Cylinder::drawCylinder()
{
    Cube cylinder(radius, 1.0, height);
    cylinder.setSurfaceLights(color);
    /*
    for(int i=0; i<360; i+=3)
    {
        glPushMatrix();
        {
            glRotatef(i , 0 , 0 ,1);
            cylinder.drawCube(false , false);
        }
        glPopMatrix();
    }
    */
    glPushMatrix();
    int shines[] = {100, 100};
    GLfloat mat_shininess[] = {shines[0]};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cylinder.surfaceLights[0][0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cylinder.surfaceLights[0][1]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cylinder.surfaceLights[0][2]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, radius, radius, height, 60, 60);

    glPopMatrix();

}



