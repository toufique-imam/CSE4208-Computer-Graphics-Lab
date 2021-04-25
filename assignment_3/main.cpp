#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Room.h"
#include "Chair.h"
#include "Cube.h"
#include "Drawer.h"
#include "Table.h"
#include "Dias.h"


bool animationOn = true;

int windowWidth = 1000, windowHeight = 1000;
int centerX =  158, centerY =-50, centerZ = 66;

int Txval = 70, Tyval = 244, Tzval = 62, angleNow = 95;

float r1 = 255, g1 = 0, b1 = 0;
float r2 = 0, g2 = 255, b2 = 0;

int angleFan = 0;
int light1=1, light2=1, light3 = 1;
void keyboardCallback(unsigned char key, int x, int y)
{
    printf("%c %d %d\n", key, x, y);
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
        Tyval -= 2;
        break;
    case 's':
        Tyval += 2;
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
    case 'm':
        light1 = light1^1;
        break;
    case 'n':
        light2 = light2^1;
        break;
    case 'b':
        light3 = light3^1;
        break;
    }
    printf("%d %d %d\n", Txval, Tyval, Tzval);
    printf("%d %d %d\n", centerX, centerY, centerZ);
    printf("%d %d %d\n", light1, light2, light3);
    glutPostRedisplay();
}
void animate()
{
    if (animationOn == false)
        return;
    angleFan += 10;
    angleFan%=360;

    glutPostRedisplay();  ////Tell GLUT that the scene has changed
}

void right_light()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 0.8, 0.8, .8, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 20,170 , 180,1.0 };

    if(light1)
    {
        glEnable( GL_LIGHT0);
        glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv( GL_LIGHT0, GL_POSITION, light_position);

    }
    else glDisable(GL_LIGHT0);

}

void left_light()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, .3, 1.0};
    GLfloat light_diffuse[]  = { 0.8, 0.8, .8, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 180,170 , 180,1.0 };
    if(light2)
    {
        glEnable( GL_LIGHT1);
        glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
        glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
        glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    }
    else glDisable(GL_LIGHT1);
}

void spot_light()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 0.9, 0.9, .9, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position1[] = { 100, 70, 180,1.0 };
    GLfloat light_position2[] = { 100, 20, 180,1.0 };
    if(light3)
    {
        glEnable( GL_LIGHT2);
        glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
        glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
        glLightfv( GL_LIGHT2, GL_POSITION, light_position1);

        GLfloat spot_direction1[] = { 0.0, -1.0, 0.0 };
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction1);
        glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 40.0);

        glEnable( GL_LIGHT3);
        glLightfv( GL_LIGHT3, GL_AMBIENT, light_ambient);
        glLightfv( GL_LIGHT3, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT3, GL_SPECULAR, light_specular);
        glLightfv( GL_LIGHT3, GL_POSITION, light_position2);

        GLfloat spot_direction2[] = { 0.0, 0.0, -1.0 };
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction2);
        glLightf( GL_LIGHT3, GL_SPOT_CUTOFF, 40.0);
    }
    else
    {
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT3);
    }
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
   // glPushMatrix();
    //glTranslatef(10, 120, 180);
    left_light();
    right_light();
    spot_light();
  //  glPopMatrix();


    Cube c;
    glPushMatrix();
    Room r(200, 250, 200, 20);
    r.updateAngles(angleFan);
    r.drawRoom();
    glPopMatrix();

    //blackboard-border
    glPushMatrix();
    glTranslatef(75, 0, 75);
    c.setValue(90, 1, 70);
    c.setSurfaceLights(c.browns);
    c.drawCube(false);
    glPopMatrix();

    //blackboard
    glPushMatrix();
    glTranslatef(80, 1, 80);
    c.setValue(80, 1, 60);
    c.setSurfaceLights(c.black);
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

    glTranslatef(5, 65, 0);
    Drawer drawer(50, 60, 100);
    drawer.drawDrawer();

    glPopMatrix();

    //bookshelf
    glPushMatrix();
    glTranslatef(5, 65+75, 1);
    drawer.drawBookself();
    glPopMatrix();

    //dias
    Dias dias(100, 60, 10, 70);

    glPushMatrix();
    {
        glTranslatef(0, 5, 0);
        dias.drawDias();
    }
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
    gluPerspective(angleNow, w / h, 0.1, 1000);
    //glFrustum(0, 500, 0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        Txval, Tyval, Tzval,
        centerX, centerY, centerZ,
        0, 0, 1);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    //glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadratic,20,10,10,320,320);

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
    glutIdleFunc(animate);
    glutKeyboardFunc(keyboardCallback);
    glEnable(GL_LIGHTING);
    // light();
    glutDisplayFunc(classroom);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_SINGLE);
    int type = 0;
    display_work();
    glutMainLoop();
    return 0;
}

