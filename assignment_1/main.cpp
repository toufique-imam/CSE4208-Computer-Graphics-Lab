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

void myCube()
{
    cube_vers = generate_cube(3 , 4 ,5);
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



void triangle()
{
    glBegin(GL_TRIANGLES);//Denotes the beginning of a group of vertices that define one or more primitives.
    glColor3f(1.0,1.0,1.0);
    glVertex2f(2.0,2.0);

    glColor3f(0.0,1.0,0.0);
    glVertex2f(2.0,0.0);

    glColor3f(0.0,1.0,0.0);
    glVertex2f(0.0,0.0);
    glEnd();	//Terminates a list of vertices that specify a primitive initiated by glBegin.

}

void myRectangle()
{
    glBegin(GL_QUADS);//Denotes the beginning of a group of vertices that define one or more primitives.
    glColor3f(r1,g1,b1);
    glVertex2f(0.0,0.0);
    glVertex2f(2.0,0.0);

    glColor3f(r2,g2,b2);
    glVertex2f(2.0,1.0);
    glVertex2f(0.0,1.0);
    glEnd();	//Terminates a list of vertices that specify a primitive initiated by glBegin.

}

void display1(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(tMinX, tMaxX, tMinY, tMaxY);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glViewport(0, 0,windowWidth,windowHeight);
    glPushMatrix();
    myRectangle();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(Txval,Tyval,0);
    glRotatef(90,0,0,1);
    myRectangle();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}
void display2(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(tMinX, tMaxX, tMinY, tMaxY);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glViewport(0, 0,windowWidth,windowHeight);

    glPushMatrix();
    glTranslatef(Txval,Tyval,0);
    glRotatef(angleNow,0,0,1);
    triangle();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
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
    myCube();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void display_work_1()
{
    glutInitWindowPosition(50,50);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Rectangle-Demo");

    glShadeModel( GL_SMOOTH );

    glEnable( GL_DEPTH_TEST );
    glutKeyboardFunc(keyboardCallback);
    glutDisplayFunc(display1);

}
void display_work_2()
{
    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Traingle-Demo");

    glShadeModel( GL_FLAT );

    glEnable( GL_DEPTH_TEST );

    windowWidth = 400, windowHeight = 300;
    //glutTimerFunc(25, animate, 0);  //Add a timer
    glutIdleFunc(animate);
    glutKeyboardFunc(keyboardCallback);
    glutDisplayFunc(display2);

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

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    int type = 0;
    while(true)
    {
        printf("Lab work 1: Rectangle Demo\n");
        printf("Lab work 2: Triangle animation Demo\n");
        printf("Lab work 3: Cube Demo\n");
        printf("Press other to exit\n");
        cin>>type;
        if(type==1)
            display_work_1();
        else if(type==2)
            display_work_2();
        else if(type==3)
            display_work_3();
        else if(type==4){
            display_work_1();
            display_work_2();
            display_work_3();
        }
        glutMainLoop();
    }
    return 0;
}

