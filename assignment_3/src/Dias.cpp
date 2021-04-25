#include "Dias.h"

Dias::Dias()
{
    //ctor
}

void Dias::drawDias()
{
    Cube body(len, wide/3, height);

    body.setSurfaceLights(body.woodColor);

    for(int i=0; i<3; i++)
    {
        glPushMatrix();
        {
            int tx = TX, ty = 2 + i*wide/3, tz = height;
            glTranslatef(tx, ty, tz);
            body.drawCube(false);
        }
        glPopMatrix();
    }

    //now draw the piller

    body.setValue(height, height, height+1);

    //rg-up
    glPushMatrix();
    {
        int tx = TX+height, ty = height, tz = 0;
        glTranslatef(tx, ty, tz);
        body.drawCube(false);
    }
    glPopMatrix();

    //rg-down
    glPushMatrix();
    {
        int tx = TX+height, ty = wide-height, tz = 0;
        glTranslatef(tx, ty, tz);
        body.drawCube(false);
    }
    glPopMatrix();

    //lt-down
    glPushMatrix();
    {
        int tx = TX+len-height, ty = wide-height, tz = 0;
        glTranslatef(tx, ty, tz);
        body.drawCube(false);
    }
    glPopMatrix();

    //lt-up
    glPushMatrix();
    {
        int tx = TX+len-height, ty = height, tz = 0;
        glTranslatef(tx, ty, tz);
        body.drawCube(false);
    }
    glPopMatrix();
}
