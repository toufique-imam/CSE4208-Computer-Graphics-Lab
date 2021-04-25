#include "Room.h"

Room::Room()
{
    //ctor
    a = b = c = 1.0;
}
void Room::assignColors(int i, int c[])
{
    colors[i][0] = c[0];
    colors[i][1] = c[1];
    colors[i][2] = c[2];
}

void Room::genColor()
{
    Cube c;
    assignColors(0, c.offwhite1);   //front
    assignColors(1, c.offwhite2);   //up
    assignColors(2, c.darkyellow);  //right
    assignColors(3, c.darkyellow);  //left
    assignColors(4, c.offwhite1);   //back
    assignColors(5, c.blueash);     //floor
}

void Room::drawRoom()
{
    genColor();
    glPushMatrix();
    Cube cb(a, b, c);
    int filterSurface[] = {0,0,1,1,1,0};
    cb.setfilterSurface(filterSurface);
    cb.setSurfaceLights(colors);
    cb.drawCube(false);
    glPopMatrix();

    glPushMatrix();
    drawTileLines();
    glPopMatrix();

    drawWallLeft();
    drawWallRight();
    glPushMatrix();
    glTranslatef(0, -45, 0);
    drawFan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 60, 0);
    drawFan();
    glPopMatrix();
    drawLightFront();
    drawLightLeft();
    drawLightRight();
    drawClock();
}

Room::Room(int ax, int bx, int cx, int t)
{
    a = ax;
    b = bx;
    c = cx;
    tileSize = t;
}

Room::Room(float ax, float bx, float cx, float t)
{
    a = ax;
    b = bx;
    c = cx;
    tileSize = t;
}

void Room::drawTileLines()
{
    float nowY = 0;
    glBegin(GL_LINES);
    GLfloat dark[] = {0 , 0 , 0 , 1};
    GLfloat mat_shininess[] = {40};

    glMaterialfv(GL_FRONT, GL_AMBIENT, dark);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dark);
    glMaterialfv(GL_FRONT, GL_SPECULAR, dark);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    for (int i = 0; nowY < b; i++)
    {
        glColor3f(0, 0, 0);
        glVertex3f(0, nowY, 1);
        glVertex3f(a, nowY, 1);
        nowY += tileSize;
    }
    glEnd();

    float nowX = 0;
    glBegin(GL_LINES);
    for (int i = 0; nowX < a; i++)
    {
        glColor3f(0, 0, 0);
        glVertex3f(nowX, 0, 1);
        glVertex3f(nowX, b, 1);
        nowX += tileSize;
    }
    glEnd();
}

void Room::drawWallLeft()
{
    drawDoor();
    Cube cube;
    cube.setValue(1.0, b, c/2.0);
    cube.setSurfaceLights(colors[3]);
    glPushMatrix();
    glTranslatef(a, b, c/2);
    glRotatef(180, 0,0,1);
    cube.drawCube(false);
    glPopMatrix();

    cube.setValue(1.0, b/10, c/2);
    glPushMatrix();
    glTranslatef(a, 0, 0);
    cube.drawCube(false);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(a, b/10+b/5, 0);
    cube.drawCube(false);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(a, b-b/10, 0);
    cube.drawCube(false);
    glPopMatrix();
    float anow = 1, bnow = b-b/5-(3.0*b)/10.0, cnow = c/4.0;
    cube.setValue(anow, bnow, cnow);
    glPushMatrix();
    glTranslatef(a, (2.0*b)/5.0, 0);
    cube.drawCube(false);
    glPopMatrix();

    Window w(bnow, cnow);
    glPushMatrix();
    glTranslatef(a, (2.0*b)/5.0, c/4);
    w.drawCageWindow();
    glPopMatrix();
}

void Room::drawWallRight()
{
    Cube cube;
    cube.setValue(1.0, b, c/2.0);
    cube.setSurfaceLights(colors[3]);
    glPushMatrix();
    glTranslatef(0, 0, c/2);
    cube.drawCube(false);
    glPopMatrix();

    cube.setValue(1.0, (2*b/5.0), c/2);
    glPushMatrix();
    cube.drawCube(false);
    glPopMatrix();

    cube.setValue(1.0, b/10, c/2);
    glPushMatrix();
    glTranslatef(0, b-b/10, 0);
    cube.drawCube(false);
    glPopMatrix();

    float anow = 1, bnow = b-b/5-(3.0*b)/10.0, cnow = c/4.0;
    cube.setValue(anow, bnow, cnow);
    glPushMatrix();
    glTranslatef(0, (2.0*b)/5.0, 0);
    cube.drawCube(false);
    glPopMatrix();

    glPushMatrix();
    Window w(bnow, cnow);
    glTranslatef(0, (2.0*b)/5.0, c/4);
    w.drawCageWindow();
    glPopMatrix();
}

void Room::drawDoor()
{
    glPushMatrix();
    Cube ch(1.0f, b / 5.0f, c / 2.0f);
    glTranslatef(a, b / 10, 0);
    ch.setSurfaceLights(ch.browns);
    ch.drawCube(false);
    glPopMatrix();


    //draw knob up
    glPushMatrix();
    Cylinder knob (2,2);
    glTranslatef(a-2, b / 10+b / 5.0-5, c/4+7);
    glRotatef(90, 0, 1,0);
    knob.setCylinderColor(ch.darkyellow);
    knob.drawCylinder();
    glPopMatrix();

    //draw knob down
    glPushMatrix();
    glTranslatef(a-2, b / 10+b / 5.0-5, c/4-7);
    glRotatef(90, 0, 1,0);
    knob.drawCylinder();
    glPopMatrix();

    //draw knob handle
    glPushMatrix();
    ch.setValue(1, 1, 14);
    glTranslatef(a-3, b / 10+b / 5.0-5, c/4-7);

    ch.setSurfaceLights(ch.darkyellow);
    ch.drawCube(false);
    glPopMatrix();

}

void Room::drawFan()
{
    Cube fanWings(50, 15, 1);
    //stand
    glPushMatrix();
    Cylinder fanStand(1, 50);
    fanStand.setCylinderColor(fanWings.black);
    glTranslatef(a / 2, b / 2, c - 50);
    fanStand.drawCylinder();
    glPopMatrix();
    //body
    Cylinder fanBody(15, 10);
    fanBody.setCylinderColor(fanWings.white);
    glPushMatrix();
    glTranslatef(a / 2, b / 2, c - 55);
    fanBody.drawCylinder();
    glPopMatrix();

    fanWings.setSurfaceLights(fanWings.black);
    glPushMatrix();
    glTranslatef(a / 2, b / 2, c - 50);
    glRotatef(angle, 0, 0, 1);
    fanWings.drawCube(false);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(a / 2, b / 2, c - 50);
    glRotatef((90 + angle) % 360, 0, 0, 1);
    fanWings.drawCube(false);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(a / 2, b / 2, c - 50);
    glRotatef((180 + angle) % 360, 0, 0, 1);
    fanWings.drawCube(false);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(a / 2, b / 2, c - 50);
    glRotatef((270 + angle) % 360, 0, 0, 1);
    fanWings.drawCube(false);
    glPopMatrix();
}

void Room::drawLightFront()
{

    Cube lightShade(70, 10, 1);
    glPushMatrix();
    {
        lightShade.setSurfaceLights(lightShade.blueash);
        glTranslatef(a/2-35, 10, c-10);
        glRotatef(110, 1, 0, 0);
        lightShade.drawCube(false);
    }
    glPopMatrix();

    glPushMatrix();

    glTranslatef(a/2-30,5, c-15);
    glRotatef(90, 0, 1, 0);
    Cylinder light(5, 60);
    light.setCylinderColor(lightShade.white);
    light.drawCylinder();

    glPopMatrix();
}

void Room::drawLightLeft()
{
    Cube lightShade(10, 70, 2);
    glPushMatrix();
    {
        lightShade.setSurfaceLights(lightShade.blueash);
        glTranslatef(a-2, b/2+20, c - 10);
        glRotatef(70+90, 0, 1, 0);
        lightShade.drawCube(false);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(a - 5, b / 2 + 27, c - 20);
    glRotatef(270, 1, 0, 0);
    Cylinder light(5, 60);
    light.setCylinderColor(lightShade.white);
    light.drawCylinder();

    glPopMatrix();
}

void Room::drawLightRight()
{
    Cube lightShade(10, 70, 2);
    glPushMatrix();
    {
        lightShade.setSurfaceLights(lightShade.blueash);
        glTranslatef(2, b / 2 + 20, c - 10);
        glRotatef(20, 0, 1, 0);
        lightShade.drawCube(false);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, b / 2 + 27, c - 20);
    glRotatef(270, 1, 0, 0);
    Cylinder light(5, 60);
    light.setCylinderColor(lightShade.white);
    light.drawCylinder();

    glPopMatrix();
}

void Room::drawClock()
{
    Cube cx(20, 1, 40);
    cx.setSurfaceLights(cx.white);
    glPushMatrix();
    glTranslatef(30, 2, c -50);
    cx.drawCube(false, false);
    glPopMatrix();

    cx.setValue(24, 1, 44);
    cx.setSurfaceLights(cx.black);
    glPushMatrix();
    glTranslatef(28, 1, c -51);
    cx.drawCube(false, false);
    glPopMatrix();

    //hour
    glPushMatrix();
    cx.setValue(12, 1, 1);
    glTranslatef(40, 3, c - 30);
    glRotatef(-90, 0, 1, 0);

    cx.setSurfaceLights(cx.black);
    cx.drawCube(false, false);
    glPopMatrix();

    //minute
    glPushMatrix();
    cx.setValue(8, 1, 1);
    glTranslatef(40, 3, c - 30);
    glRotatef(70, 0, 1, 0);
    cx.setSurfaceLights(cx.black);
    cx.drawCube(false, false);
    glPopMatrix();
}
