#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Room.h"
#include "Chair.h"
#include "Cube.h"
#include "Drawer.h"
#include "Table.h"

bool animationOn = true;

int windowWidth = 1000, windowHeight = 1000;
int centerX = 0, centerY = 0, centerZ = 0;

int Txval = 188, Tyval = 198, Tzval = 62, angleNow = 95;

float r1 = 255, g1 = 0, b1 = 0;
float r2 = 0, g2 = 255, b2 = 0;

//188 198 62 95
void keyboardCallback(unsigned char key, int x, int y)
{
    printf("%c\n", key);
    switch (key)
    {
    case 'p':
        animationOn = !animationOn;
        break;
    case 'q':
        Tzval += 2;
        break;
    case 'e':
        Tzval -= 2;
        break;
    case 'w':
        Tyval += 2;
        break;
    case 's':
        Tyval -= 2;
        break;
    case 'a':
        Txval += 2;
        break;
    case 'd':
        Txval -= 2;
        break;
    case 'z':
        angleNow += 5;
        break;
    case 'x':
        angleNow -= 5;
        break;
    case 'u':
        centerX += 2;
        //angleX%=360;
        break;
    case 'i':
        centerY += 2;
        //angleY%=360;
        break;
    case 'o':
        centerZ += 2;
        //angleZ%=360;
        break;
    case 'j':
        centerX -= 2;
        //angleX%=360;
        break;
    case 'k':
        centerY -= 2;
        //angleY%=360;
        break;
    case 'l':
        centerZ -= 2;
        //angleZ%=360;
        break;
    }
    printf("%d %d %d\n", Txval, Tyval, Tzval);
    printf("%d %d %d\n", centerX, centerY, centerZ);
    glutPostRedisplay();
}

void animate()
{
    if (animationOn == false)
        return;
    angleNow += .02f;
    if (angleNow >= 360)
    {
        angleNow = 0;
    }

    glutPostRedisplay();  ////Tell GLUT that the scene has changed
}

void classroom()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    //glOrtho(-100 , Txval , -100 , Tyval , -100 , Tzval);

    gluPerspective(angleNow, w / h, 0.1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        Txval, Tyval, Tzval,
        centerX, centerY, centerZ,
        0, 0, 1);
    Cube c;
    glPushMatrix();
    Room r(200, 250, 200, 20);
    r.drawRoom();
    glPopMatrix();

    //blackboard-border
    glPushMatrix();
    glTranslatef(75, 0, 75);
    c.setValue(90, 1, 70);
    c.setSurfaceColors(c.browns);
    c.drawCube(false);
    glPopMatrix();

    //blackboard
    glPushMatrix();
    glTranslatef(80, 1, 80);
    c.setValue(80, 1, 60);
    c.setSurfaceColors(c.black);
    c.drawCube(false);
    glPopMatrix();

    //tables
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            glPushMatrix();
            int translateX = 8 + 70 + j * 40;
            int translateY = 100 + i * 45;
            glTranslatef(translateX, translateY, 0);
            //cerr<< i*3+j <<" "<< translateX<<" "<<translateY<<"\n";
            Table t(30, 25, 40, 20, 10, 2, 25);
            t.drawTable();
            glPopMatrix();
        }
    }

    //chairs
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int translateX = 8 + 70 + j * 40 + 10 + 2.5;
            int translateY = 100 + 25 * (i + 1) + 20 * i + 3;

            glPushMatrix();
            glTranslatef(translateX, translateY, 0);
            glRotatef(180, 0, 0, 1);
            glTranslatef(-15, -15, 0);
            //cerr<< i*3+j <<" "<< translateX<<" "<<translateY<<"\n";
            Chair chair_now(48, 25, 15, 15);
            chair_now.drawChair();
            glPopMatrix();
        }
    }
    //drawer
    glPushMatrix();
    glTranslatef(5, 20, 0);
    Drawer d(50, 60, 100);
    d.drawDrawer();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void displayTest()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    //    gluPerspective(angleY, w / h, 0.1, 1000);
    glFrustum(0, 500, 0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        Txval, Tyval, Tzval,
        0, 0, 0,
        1, 0, 0);

    Room r(100, 100, 100, 20);
    r.drawRoom();

    glFlush();
    glutSwapBuffers();
}

void display_work()
{
    glutInitWindowPosition(200, 200);
    windowHeight = 600;
    windowWidth = 1000;
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("ClassRoom-Demo");

    glShadeModel(GL_FLAT);

    glEnable(GL_DEPTH_TEST);

    glutKeyboardFunc(keyboardCallback);

    glutDisplayFunc(classroom);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    int type = 0;
    display_work();
    glutMainLoop();
    return 0;
}
