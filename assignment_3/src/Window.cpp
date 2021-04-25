#include "Window.h"

Window::Window()
{
    //ctor
}

void Window::drawCageWindow()
{
    int gaps = (len - cnt)/(cnt+1);

    Cube c;
    c.setValue(2, len, 2);
    c.setSurfaceLights(c.blueash);
    glPushMatrix();
    c.drawCube(false);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, wide);
    c.drawCube(false);
    glPopMatrix();

    c.setValue(2, 2, wide);

    glPushMatrix();
    c.drawCube(false);
    glPopMatrix();


    glPushMatrix();
    glTranslatef( 0, len, 0);
    c.drawCube(false);
    glPopMatrix();

    c.setValue(2, 2, wide);
    for(int i=0; i<cnt; i++)
    {
        glPushMatrix();
        glTranslatef(0, gaps*(i+1)+2*i, 0);
        c.drawCube(false);
        glPopMatrix();
    }
    c.setValue(2 , len , 2);
    glPushMatrix();
        glTranslatef(0 , 0 , wide/3);
        c.drawCube(false);
    glPopMatrix();

    c.setValue(2 , len , 2);
    glPushMatrix();
        glTranslatef(0 , 0 , 2*wide/3);
        c.drawCube(false);
    glPopMatrix();
}
