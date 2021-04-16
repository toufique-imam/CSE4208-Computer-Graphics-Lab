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
}
