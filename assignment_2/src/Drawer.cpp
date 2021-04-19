#include "Drawer.h"

void Drawer::drawDrawer() {
    //draw drawerInside
    Cube c;
    c.setSurfaceColors(c.browns);
    glPushMatrix();
    c.setValue(sizex - 2, sizey, sizez);
    c.drawCube(false);
    glPopMatrix();

    //draw the door1
    glPushMatrix();
    glTranslatef(sizex - 2, 0, 0);
    c.setValue(2, sizey / 2, sizez);
    c.drawCube(false);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(sizex - 2, sizey / 2, 0);
    c.setValue(2, sizey / 2, sizez);
    c.drawCube(false);
    glPopMatrix();

    //
    c.setSurfaceColors(c.darkyellow);
    glPushMatrix();
    glTranslatef(sizex - .5, sizey / 2, 0);
    c.setValue(2, 1, sizez);
    c.drawCube(false);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sizex - .5, sizey / 2 + 1, 0);
    c.drawCube(false);
    glPopMatrix();

    //door knob

    glPushMatrix();
        Cylinder cylinder(3 ,3);
        glTranslatef(sizex-1, sizey / 2-5, sizez/2);
        glRotatef(90 , 0 , 1 , 0);
        cylinder.setCylinderColor(c.darkyellow);
        cylinder.drawCylinder();
    glPopMatrix();

}

void Drawer::drawBookself()
{
    //draw body
    glPushMatrix();
    Cube cb(sizex, sizey, sizez);
    int filterSurface[] = {0, 0, 0, 1, 0, 0};
    cb.setfilterSurface(filterSurface);
    cb.setSurfaceColors(cb.browns);
    cb.drawCube(false);
    glPopMatrix();
    //draw shelf
    int posz = (sizez)/3;
    cb.setSurfaceColors(cb.browns);
    glPushMatrix();
    glTranslatef(0, 0, 2+posz);
    cb.setValue(sizex, sizey, 2);
    cb.drawCube(false);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 4+posz+posz);
    cb.setValue(sizex, sizey, 2);
    cb.drawCube(false);
    glPopMatrix();

    //books
    int bookCount = (sizey-2) / 6;
    cb.setValue(sizex-4, 5, posz-5);
    for(int i=0; i<bookCount; i++)
    {
        glPushMatrix();
        glTranslatef(2, 2+i*6, 4+posz+posz+1);
        cb.genRandomColor(i+1);
        cb.drawCube(false);
        glPopMatrix();
    }

    for(int i=0; i<bookCount; i++)
    {
        glPushMatrix();
        glTranslatef(2, 2+i*6, 2+posz+1);
        cb.genRandomColor(bookCount-i+1);
        cb.drawCube(false);
        glPopMatrix();
    }

    for(int i=0; i<bookCount; i++)
    {
        glPushMatrix();
        glTranslatef(2, 2+i*6, 3);
        cb.genRandomColor(bookCount-i);
        cb.drawCube(false);
        glPopMatrix();
    }
}

