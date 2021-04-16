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
    cb.setSurfaceColors(colors);
    cb.drawCube(false);
    glPopMatrix();

    glPushMatrix();
    drawTileLines();
    glPopMatrix();

    drawWallLeft();
    drawWallRight();
    //drawDoor();

    //todo make windows
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
    for (int i = 0; nowY < b; i++)
    {
        glColor3f(0, 0, 0);
        glVertex3f(0, nowY, 0);
        glVertex3f(a, nowY, 0);
        nowY += tileSize;
    }
    glEnd();

    float nowX = 0;
    glBegin(GL_LINES);
    for (int i = 0; nowX < a; i++)
    {
        glColor3f(0, 0, 0);
        glVertex3f(nowX, 0, 0);
        glVertex3f(nowX, b, 0);
        nowX += tileSize;
    }
    glEnd();
}

void Room::drawWallLeft()
{
    drawDoor();
    Cube cube;
    cube.setValue(1.0, b, c/2.0);
    cube.setSurfaceColors(colors[3]);
    glPushMatrix();
    glTranslatef(a, 0, c/2);
    cube.drawCube(false);
    glPopMatrix();

    cube.setValue(1.0 , b/10 , c/2);
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
    float anow = 1 , bnow = b-b/5-(3.0*b)/10.0 , cnow = c/4.0;
    cube.setValue(anow , bnow , cnow);
    glPushMatrix();
        glTranslatef(a , (2.0*b)/5.0 , 0);
        cube.drawCube(false);
    glPopMatrix();

    Window w(bnow , cnow);
    glPushMatrix();
        glTranslatef(a , (2.0*b)/5.0 , c/4);
        w.drawCageWindow();
    glPopMatrix();
}

void Room::drawWallRight(){
    Cube cube;
    cube.setValue(1.0, b, c/2.0);
    cube.setSurfaceColors(colors[3]);
    glPushMatrix();
        glTranslatef(0, 0, c/2);
        cube.drawCube(false);
    glPopMatrix();

    cube.setValue(1.0 , (2*b/5.0) , c/2);
    glPushMatrix();
        cube.drawCube(false);
    glPopMatrix();

    cube.setValue(1.0 , b/10 , c/2);
    glPushMatrix();
        glTranslatef(0, b-b/10, 0);
        cube.drawCube(false);
    glPopMatrix();

    float anow = 1 , bnow = b-b/5-(3.0*b)/10.0 , cnow = c/4.0;
    cube.setValue(anow , bnow , cnow);
    glPushMatrix();
        glTranslatef(0 , (2.0*b)/5.0 , 0);
        cube.drawCube(false);
    glPopMatrix();

    Window w(bnow , cnow);
    glPushMatrix();
        glTranslatef(0 , (2.0*b)/5.0 , c/4);
        w.drawCageWindow();
    glPopMatrix();
}

void Room::drawDoor()
{
    glPushMatrix();
    Cube ch(1.0f, b / 5.0f, c / 2.0f);
    glTranslatef(a, b / 10, 0);
    ch.setSurfaceColors(ch.browns);
    ch.drawCube(false);
    glPopMatrix();
}
