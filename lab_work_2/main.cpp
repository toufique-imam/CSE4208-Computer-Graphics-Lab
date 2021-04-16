#include<bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;


bool animationOn = true;
float angleNow = 0;

int windowWidth = 500, windowHeight = 500;
int tMinX=-5, tMaxX=5, tMinY=-5, tMaxY=5;

float Txval = 0.0, Tyval = 0.0;


vector< vector<int> > cube_vers;
vector< vector<int> > cube_colors;


float r1=255, g1=0, b1=0;
float r2=0, g2=255, b2=0;

void keyboardCallback( unsigned char key, int x, int y )
{
    printf("%c\n",key);
    switch ( key )
    {
    case 'p':
        animationOn=!animationOn;
        break;
    case 'q':
        exit(1);
        break;
    case 'r':
        Txval+=0.2;
        break;
    case 'l':
        Txval-=0.2;
        break;
    case 'u':
        Tyval+=0.2;
        break;
    case 'd':
        Tyval-=0.2;
        break;

    }
    glutPostRedisplay();
}

void animate()
{
    if(animationOn==false)return;
    angleNow += .02f;
    if (angleNow >= 360)
    {
        angleNow =0;
    }

    glutPostRedisplay();  ////Tell GLUT that the scene has changed
}
vector< vector<int> > generate_cube(int a,int b,int c)
{
    vector< vector<int> >ans;
    vector<int>v(3, 0);
    ans.push_back(v);
    //2
    v[0] = a, v[1] = 0, v[2] = 0;
    ans.push_back(v);
    //3
    v[0] = a, v[1] = 0, v[2] = c;
    ans.push_back(v);
    //4
    v[0] = 0, v[1] = 0, v[2] = c;
    ans.push_back(v);
    //5
    v[0] = 0, v[1] = b, v[2] = 0;
    ans.push_back(v);
    //6
    v[0] = a, v[1] = b, v[2] = 0;
    ans.push_back(v);
    //7
    v[0] = a, v[1] = b, v[2] = c;
    ans.push_back(v);
    //8
    v[0] = 0, v[1] = b, v[2] = c;
    ans.push_back(v);

    return ans;
}

void quad3d(int points[])
{
    glBegin(GL_QUADS);
    for(int i=0; i<4; i++)
    {
        glColor3f(cube_colors[points[i]][0], cube_colors[points[i]][1], cube_colors[points[i]][2]);
        glVertex3f(cube_vers[points[i]][0], cube_vers[points[i]][1], cube_vers[points[i]][2]);

    }
    glEnd();
}

void myCube(int a,int b,int c)
{
    cube_vers = generate_cube(a , b ,c);
    cube_colors = generate_cube(100 , 100 , 100);
    int ara[6][4] =
    {
        {0,3,2,1},
        {2,3,7,6},
        {0,4,7,3},
        {1,2,6,5},
        {4,5,6,7},
        {0,1,5,4}
    };

    for(int i=0; i<6; i++)
    {
        quad3d(ara[i]);
    }
}


void display3(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 60, w / h, 0.1, 100 );


    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    gluLookAt
    (
        8, 8, 8,
        0, 0, 0,
        0, 0, 1
    );

    glPushMatrix();
    glTranslatef(Txval,Tyval,0);
    myCube(3,3,3);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void display4(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 60, w / h, 0.1, 100 );


    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    gluLookAt
    (
        20, 20, 20,
        0, 0, 0,
        0, 0, 1
    );

    //stand1
    glPushMatrix();
        //glTranslatef(Txval,Tyval,0);
        myCube(1,1,15);
    glPopMatrix();

    //side-stand1
    glPushMatrix();
        glTranslatef(0,0,13);
        myCube(5,1,1);
    glPopMatrix();

    //side-stand2
    glPushMatrix();
        glTranslatef(0,0,10);
        myCube(5,1,1);
    glPopMatrix();

    //stand2
    glPushMatrix();
        glTranslatef(5,0,0);
        myCube(1,1,15);
    glPopMatrix();

    //seat
    glPushMatrix();
        glTranslatef(0,0,8);
        myCube(6,5,1);
    glPopMatrix();

    //stand3
    glPushMatrix();
        glTranslatef(0,4,1);
        myCube(1,1,7);
    glPopMatrix();

    //stand4
    glPushMatrix();
        glTranslatef(5,4,1);
        myCube(1,1,7);
    glPopMatrix();

    //sub-stand1
    glPushMatrix();
        glTranslatef(0,0,2);
        myCube(1,5,1);
    glPopMatrix();

    //sub-stand2
    glPushMatrix();
        glTranslatef(5,0,2);
        myCube(1,5,1);
    glPopMatrix();


    glFlush();
    glutSwapBuffers();

}


void display5(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 60, w / h, 0.1, 100 );


    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    gluLookAt
    (
        20, 20, 20,
        0, 0, 0,
        0, 0, 1
    );

    //stand1
    glPushMatrix();
        //glTranslatef(Txval,Tyval,0);
        myCube(1,5,15);
    glPopMatrix();

    //stand2
    glPushMatrix();
        glTranslatef(10,0,0);
        myCube(1,5,15);
    glPopMatrix();


    //seat
    glPushMatrix();
        glTranslatef(0,0,15);
        myCube(11,5,1);
    glPopMatrix();

    //sub-seat-left-up
    glPushMatrix();
        glTranslatef(0,0,7);
        myCube(5,5,1);
    glPopMatrix();

    //sub-seat-left-down
    glPushMatrix();
        glTranslatef(0,0,2);
        myCube(5,5,1);
    glPopMatrix();


    //stand-for-right
    glPushMatrix();
        glTranslatef(5,0,0);
        myCube(1,5,15);
    glPopMatrix();

    //sub-seat-right-up
    glPushMatrix();
        glTranslatef(5,0,11);
        myCube(5,5,1);
    glPopMatrix();

    //sub-seat-right-down
    glPushMatrix();
        glTranslatef(5,0,8);
        myCube(5,5,1);
    glPopMatrix();



    glFlush();
    glutSwapBuffers();

}

void display_work_3()
{
    glutInitWindowPosition(200,200);
    windowHeight = windowWidth = 500;
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Cube-Demo");

    glShadeModel( GL_SMOOTH );

    glEnable( GL_DEPTH_TEST );

    glutKeyboardFunc(keyboardCallback);

    glutDisplayFunc(display3);
}

void display_work_4(){
    glutInitWindowPosition(200,200);
    windowHeight = windowWidth = 500;
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Chain-Demo");

    glShadeModel( GL_SMOOTH );

    glEnable( GL_DEPTH_TEST );

    glutKeyboardFunc(keyboardCallback);

    glutDisplayFunc(display4);
    glutDisplayFunc(display4);
}
void display_work_5(){
    glutInitWindowPosition(200,200);
    windowHeight = windowWidth = 500;
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Table-Demo");

    glShadeModel( GL_SMOOTH );

    glEnable( GL_DEPTH_TEST );

    glutKeyboardFunc(keyboardCallback);

    glutDisplayFunc(display5);
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    int type = 0;
    display_work_4();
    display_work_5();
    glutMainLoop();
    return 0;
}

