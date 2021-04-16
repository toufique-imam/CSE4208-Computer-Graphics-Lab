#include "Chair.h"

Chair::Chair() {
    //ctor
}

void Chair::drawChair() {
    Cube c;
    glPushMatrix();
    c.setValue(1, 1, chairBigLegLen);
    c.setSurfaceColors(c.darkyellow);
    //glTranslatef(Txval,Tyval,0);
    c.drawCube(false);
    glPopMatrix();

    //side-stand1
    glPushMatrix();
    c.setValue(seatY, 1, 1);
    glTranslatef(0, 0, chairBigLegLen - 3);
    c.drawCube(false);
    glPopMatrix();

    //side-stand2
    glPushMatrix();
    c.setValue(seatY, 1, 1);
    glTranslatef(0, 0, chairBigLegLen - 8);
    c.drawCube(false);
    glPopMatrix();

    //stand2
    glPushMatrix();
    c.setValue(1, 1, chairBigLegLen);
    glTranslatef(seatY, 0, 0);
    c.drawCube(false);
    glPopMatrix();

    //seat
    glPushMatrix();
    c.setValue(seatX+1, seatY+1, 1);
    glTranslatef(0, 0, chairSmallLegLen);
    c.drawCube(false);
    glPopMatrix();

    //stand3
    glPushMatrix();
    c.setValue(1, 1, chairSmallLegLen);
    glTranslatef(0, seatY,0);  //1?
    c.drawCube(false);
    glPopMatrix();

    //stand4
    glPushMatrix();
    glTranslatef(seatX, seatY, 0);
    c.drawCube(false);
    glPopMatrix();

    //sub-stand1
    glPushMatrix();
    c.setValue(1, seatY, 1);
    glTranslatef(0, 0, 5);
    c.drawCube(false);
    glPopMatrix();

    //sub-stand2
    glPushMatrix();
    glTranslatef(seatX, 0, 5);
    c.drawCube(false);
    glPopMatrix();
}
