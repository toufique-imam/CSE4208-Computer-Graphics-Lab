#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "BmpLoader.h"
#include "Cube.h"
#include "Human.h"
#include "TextureLoader.h"
#define error(x) cerr << #x << " " << x << "\n";
/*
Birds eye view?
170 96
32 1034 1116
8 225 190
*/
/*
-50 988 348
-22 325 235
*/
/*
batsman View
-73 270
36 1494 198
18 225 200
*/

/*
bowler View
*/
/*
605 773 193
133 410 165
*/

bool animationOn = true;

int windowWidth = 1000, windowHeight = 1000;
int centerX = -22, centerY = 325, centerZ = 235;

int Txval = -50, Tyval = 988, Tzval = 348, angleNow = 95;

float r1 = 255, g1 = 0, b1 = 0;
float r2 = 0, g2 = 255, b2 = 0;

int lightOn[4];

int fieldSize = 2000;
int pitchX = 100;
int pitchY = 600;
int stadiumHeight = 500;
GLfloat light_position_down_left[] = {-fieldSize / 2, -fieldSize / 2, stadiumHeight + stadiumHeight - 50, 1.0};
GLfloat light_position_down_right[] = {fieldSize / 2, -fieldSize / 2, stadiumHeight + stadiumHeight - 50, 1.0};
GLfloat light_position_up_left[] = {-fieldSize / 2, fieldSize / 2, stadiumHeight + stadiumHeight - 50, 1.0};
GLfloat light_position_up_right[] = {fieldSize / 2, fieldSize / 2, stadiumHeight + stadiumHeight - 50, 1.0};

int rightFront = 0, bowlerReached = 0, bowlerPosY = 0,
    incrementBowlerPos = 5, maxPos = 100, releaseBall = 0;

int batsmanMoves = 0;
int strikeState = 0;
int strikeDir = 0;
bool stampOut = 0;
float ballLoc[3];
float ballVelocity[3];
bool startBall = 0;
int handAngle = 0;
int increment = 5;

void resetAll() {
    rightFront = 0, bowlerReached = 0, bowlerPosY = 10,
    incrementBowlerPos = 5, maxPos = 100, releaseBall = 0;
    batsmanMoves = 0;
    strikeState = 0;
    strikeDir = 0;
    ballLoc[2] = 50;
    ballLoc[0] = -20;
    ballLoc[1] = 0;
    ballVelocity[1] = 7.5;
    ballVelocity[2] = -1;
    ballVelocity[0] = 0.2;
    startBall = 0;
    increment = 5;
    stampOut = 0;
    for (int i = 0; i < 4; i++)
        lightOn[i] = 1;
}
void createLight(int idx, int lightNum, GLfloat light_position[]) {
    GLfloat no_light[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[] = {0.8, 0.8, .8, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};

    if (lightOn[idx]) {
        glEnable(lightNum);
        glLightfv(lightNum, GL_AMBIENT, light_ambient);
        glLightfv(lightNum, GL_DIFFUSE, light_diffuse);
        glLightfv(lightNum, GL_SPECULAR, light_specular);
        glLightfv(lightNum, GL_POSITION, light_position);

    } else
        glDisable(lightNum);
}
void animate(int) {
    rightFront ^= 1;
    {
        if (strikeState) {
            handAngle += increment;
            if (handAngle >= 50) {
                increment = -5;
            }
            if (handAngle <= 0) {
                if (strikeState) {
                    strikeState = 0;
                    strikeDir = 0;
                }
                increment = 5;
            }
        }
    }

    if (!bowlerReached) {
        bowlerPosY += incrementBowlerPos;
    } else if (bowlerPosY >= maxPos) {
        if (releaseBall < 9) {
            releaseBall++;
            bowlerPosY += 1;
        } else {
            releaseBall = 9;
            bowlerPosY = maxPos + incrementBowlerPos;
        }
    }
    //printf("%d %d %d\n", bowlerPosY, bowlerReached, releaseBall);
    glutPostRedisplay();  ////Tell GLUT that the scene has changed
    if (startBall)
        glutTimerFunc(30, animate, 1);
    else
        glutTimerFunc(100, animate, 1);
}
void setColor(Cube dummy) {
    dummy.setSurfaceShine(60);
    GLfloat mat_shininess[] = {dummy.shines[0]};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, dummy.surfaceLights[0][0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dummy.surfaceLights[1][0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, dummy.surfaceLights[2][0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}
void drawBall() {
    if (ballLoc[2] < 10) {
        cout << "Colided " << ballLoc[1] << "\n";
        ballVelocity[2] = -2 * ballVelocity[2];
    }
    if (ballLoc[1] > pitchY - 50 && ballLoc[1] < pitchY - 10) {
        if (strikeState) {
            if (strikeDir == -1) {
                ballVelocity[0] = 4;
                ballVelocity[1] = -4;
                ballVelocity[2] = 4;

            } else if (strikeDir == 1) {
                ballVelocity[1] = -4;
                ballVelocity[2] = 4;

            } else if (strikeDir == 2) {
                ballVelocity[0] = -4;
                ballVelocity[1] = -4;
                ballVelocity[2] = 4;
            }
        }
    }
    if (ballLoc[1] >= pitchY) {
        startBall = 0;
        cout << "OUT " << ballLoc[1] << " " << pitchY << "\n";
        stampOut = 1;
    }
    if (abs(ballLoc[1]) < fieldSize / 2 &&
            abs(ballLoc[2] < fieldSize / 2) &&
            abs(ballLoc[0]) < fieldSize / 2) {
        ballLoc[0] += ballVelocity[0];
        ballLoc[1] += ballVelocity[1];
        ballLoc[2] += ballVelocity[2];
    } else {
        startBall = 0;
    }
    // cout << ballLoc[0] << " " << ballLoc[1] << " " << ballLoc[2] << " " << strikeState << " " << strikeDir << "\n";

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID_BALL);
    glPushMatrix();
    {
        Cube dummy;
        dummy.setColor(255, 0, 0);
        glTranslatef(ballLoc[0], ballLoc[1] - pitchY / 2 + 5, ballLoc[2]);
        setColor(dummy);
        //dummy.setValue(10 , 10 , 10);
        //dummy.drawCube();
        //glutSolidSphere(10, 20, 20);

        GLUquadric* quad = gluNewQuadric();
        gluQuadricTexture(quad, true);
        gluSphere(quad, 5, 20, 20);
    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

int calculateBowlerState() {
    int state;
    if (!bowlerReached) {
        error(bowlerPosY);

        if (rightFront)
            state = 0;
        else
            state = 1;
        if (bowlerPosY >= maxPos)
            bowlerReached = 1;
    } else {
        if (releaseBall < 9) {
            state = 2;
        } else {
            state = 3;
        }
    }
    return state;
}

void createBowler() {
    int state = calculateBowlerState();
    //cout<<state<<"\n";
    Human bowler;
    glPushMatrix();
    if (state == 0) {  //running left now
        glTranslatef(0, bowlerPosY, 0);
        bowler = Human::runningBowler(1);
        bowler.setBatStatus(false);
        bowler.drawHuman();
    } else if (state == 1) {  //running right now
        glTranslatef(0, bowlerPosY, 0);
        bowler = Human::runningBowler(0);
        bowler.setBatStatus(false);
        bowler.drawHuman();
    } else if (state == 2) {  //bowling
        glTranslatef(0, bowlerPosY, 0);
        bowler = Human::bowlingBowler(releaseBall, startBall, rightFront);
        bowler.setBatStatus(false);
        bowler.drawHuman();

    } else {  // standing
        glTranslatef(0, bowlerPosY, 0);
        bowler = Human::generalHumanConfig();
        bowler.setBatStatus(false);
        bowler.drawHuman();
    }
    glPopMatrix();
}

void createBatsman() {
    Human batsman = Human::generalHumanConfig();
    batsman.setBatStatus(true);
    glPushMatrix();
    //glRotatef(45 , 0 , 0 , 1);
    if (strikeState) {
        if (strikeDir == -1) {
            Human::offCutLeftHandConfig(batsman, handAngle);
            Human::offCutRightHandConfig(batsman, handAngle);

            Human::runningLeftLegConfig(0, batsman);
            Human::runningRightLegConfig(0, batsman);
        } else if (strikeDir == 1) {
            Human::straightCutLeftHandConfig(batsman, handAngle);
            Human::straightCutRightHandConfig(batsman, handAngle);

        } else if (strikeDir == 2) {
            Human::onCutLeftHandConfig(batsman, handAngle);
            Human::onCutRightHandConfig(batsman, handAngle);

            Human::runningLeftLegConfig(1, batsman);
            Human::runningRightLegConfig(1, batsman);
        }
    } else {
        Human::humanBatsmanLeftConfig(batsman, handAngle);
        Human::humanBatsmanRightConfig(batsman, handAngle);
    }
    batsman.drawHuman();
    glPopMatrix();
}

void createField() {
    Cube cube(1, 1, 1);
    //field

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID_GRASS);
    glPushMatrix();
    {
        cube.setRepeat(4);
        cube.setSurfaceLights(cube.green);
        glTranslatef(-fieldSize / 2, -fieldSize / 2, 0);
        glScalef(fieldSize, fieldSize, 2);
        cube.drawCube();
    }
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D , 0);
    glDisable(GL_TEXTURE_2D);
}
void createPitch() {
    Cube cube(1, 1, 1);
    cube.setRepeat(1);
    cube.setSurfaceLights(cube.offwhite2);

    //field
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID_PITCH);
    glPushMatrix();
    {
        glTranslatef(-pitchX / 2, -pitchY / 2, 4);
        glScalef(pitchX, pitchY, 2);
        cube.drawCube();
    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawBoundary() {
    Cube cube(1, 1, 1);
    cube.setSurfaceLights(cube.offwhite2);
    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();
    gluQuadricTexture(quadratic, true);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID_BANNER2);
    glPushMatrix();
    {
        setColor(cube);
        gluCylinder(quadratic, fieldSize / 2 - 50,
                    fieldSize / 2, 100, 20, 20);
    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawStadium() {
    Cube cube(1, 1, 1);
    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();
    gluQuadricTexture(quadratic, true);
    glPushMatrix();
    {
        cube.setColor(200, 200, 0);
        setColor(cube);
        gluCylinder(quadratic, fieldSize / 2 + 50,
                    fieldSize / 2 + 100, 500, 20, 20);
    }
    glPopMatrix();
}

void drawPoll(GLfloat positionx, GLfloat positiony, GLfloat positionz) {
    Cube cube(1, 1, 1);
    cube.setSurfaceLights(cube.offwhite1);
    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();
    gluQuadricTexture(quadratic, true);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID_METAL);
    glPushMatrix();
    {
        setColor(cube);
        glTranslatef(positionx, positiony, 0);
        gluCylinder(quadratic, 10, 10, positionz + stadiumHeight - 100, 10, 10);
    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID_FLOOD_LIGHT);
    glPushMatrix();
    {
        setColor(cube);
        glTranslatef(positionx - 150, positiony, positionz + stadiumHeight - 100);
        cube.setRepeat(4);
        glScalef(300, 20, 400);
        cube.drawCube();
    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawPolls() {
    drawPoll(light_position_down_left[0] + 50, light_position_down_left[1] + 50, stadiumHeight);
    drawPoll(light_position_down_right[0] - 50, light_position_down_right[1] + 50, stadiumHeight);
    drawPoll(light_position_up_left[0] + 50, light_position_up_left[1] - 50, stadiumHeight);
    drawPoll(light_position_up_right[0] - 50, light_position_up_right[1] - 50, stadiumHeight);
}

void createStamp(bool batsmanStamp) {
    Cube dummy;
    dummy.setSurfaceLights(dummy.white);
    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();
    gluQuadricTexture(quadratic, true);
    for (int i = -1; i < 2; i++) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ID_BALL);
        glPushMatrix();
        {
            setColor(dummy);
            glTranslatef(5 * i, 0, 2);
            if (stampOut && batsmanStamp) {
                glRotatef(10 * i, 0, 1, 0);
                glRotatef(10 * (i == 0), -1, 0, 0);
            }
            gluCylinder(quadratic, 1.5, 1.5, 50, 60, 60);
        }
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }
}
void displayTest() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(angleNow, 1, 0.1, 4000);
    //glFrustum(10, w, 10 , h , 10 , 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        Txval, Tyval, Tzval,
        centerX, centerY, centerZ,
        0, 0, 1);

    // lightDownLeft();
    // lightDownRight();
    // lightFrontLeft();
    // lightFrontRight();
    createLight(0, GL_LIGHT0, light_position_down_left);
    createLight(1, GL_LIGHT1, light_position_down_right);
    createLight(2, GL_LIGHT2, light_position_up_left);
    createLight(3, GL_LIGHT3, light_position_up_right);

    Cube cube(1, 1, 1);
    //field
    createField();

    //pitch
    createPitch();

    //ball
    if (startBall) {
        glPushMatrix();
        drawBall();
        glPopMatrix();
    }

    glPushMatrix();
    {
        glTranslatef(0, -(pitchY / 2) + 30, 0);
        createStamp(false);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0, (pitchY / 2) - 30, 0);
        createStamp(true);
    }
    glPopMatrix();

    glPushMatrix();
    {
        cube.setValue(10, 10, 10);
        glTranslatef(0, 0, 6);
        cube.setColor(155, 255, 0);
        cube.drawCube();
    }
    glPopMatrix();

    //bowler
    glPushMatrix();
    glTranslatef(-20, -(pitchY - pitchY / 3), 2);
    createBowler();
    glPopMatrix();

    //batsman
    glPushMatrix();
    glTranslatef(0, pitchY / 2 - 50, 2);
    glTranslatef(batsmanMoves * 4 + 10, 0, 0);
    glRotatef(90, 0, 0, 1);
    createBatsman();
    glPopMatrix();

    glPushMatrix();
    {
        drawBoundary();
    }
    glPopMatrix();

    glPushMatrix();
    {
        //drawStadium();
    }
    glPopMatrix();
    glPushMatrix();
    {
        drawPolls();
    }
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void keyboardCallback(unsigned char key, int x, int y) {
    printf("%c\n", key);
    switch (key) {
    case '1':
        lightOn[0] = !lightOn[0];
        break;
    case '2':
        lightOn[1] = !lightOn[1];
        break;
    case '3':
        lightOn[2] = !lightOn[2];
        break;
    case '4':
        lightOn[3] = !lightOn[3];
        break;
    case 'z':
        Tzval += 5;
        break;
    case 'Z':
        Tzval -= 5;
        break;
    case 'C':
        Tyval -= 5;
        break;
    case 'c':
        Tyval += 5;
        break;
    case 'x':
        Txval += 5;
        break;
    case 'X':
        Txval -= 5;
        break;
    case '=':
        angleNow -= 5;
        break;
    case '+':
        angleNow -= 5;
        break;
    case '-':
        angleNow += 5;
        break;
    case 'q':
        centerX += 5;
        break;
    case 'w':
        centerY += 5;
        break;
    case 'e':
        centerZ += 5;
        break;
    case 'Q':
        centerX -= 5;
        break;
    case 'W':
        centerY -= 5;
        break;
    case 'E':
        centerZ -= 5;
        break;
    case 'n':
        batsmanMoves++;
        break;
    case 'm':
        batsmanMoves--;
        break;
    case 'k':
        if (strikeState == 0) {
            strikeState = 1;
            strikeDir = 1;
        }
        break;
    case 'j':
        if (strikeState == 0) {
            strikeState = 1;
            strikeDir = -1;
        }
        break;

    case 'l':
        if (strikeState == 0) {
            strikeState = 1;
            strikeDir = 2;
        }
        break;
    case 'r':
        resetAll();
        break;
    }
    printf("%d %d %d\n", Txval, Tyval, Tzval);
    printf("%d %d %d\n", centerX, centerY, centerZ);
    //printf("%d %d %d\n", light1, light2, light3);
    glutPostRedisplay();
}

void display_work() {
    glutInitWindowPosition(200, 200);
    windowHeight = 1000;
    windowWidth = 1000;
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Cricket");

    glGenTextures(6, IDS);
    for (int i = 0; i < 10; i++) {
        IDS[i] = i;
    }
    loadTexture(textureFileName[ID_BALL], ID_BALL);
    loadTexture(textureFileName[ID_GRASS], ID_GRASS);
    loadTexture(textureFileName[ID_GRIP], ID_GRIP);
    loadTexture(textureFileName[ID_PITCH], ID_PITCH);
    //loadTexture(textureFileName[ID_WHITE_CLOTH], ID_WHITE_CLOTH);
    loadTexture(textureFileName[ID_WOOD], ID_WOOD);
    loadTexture(textureFileName[ID_BANNER2], ID_BANNER2);
    loadTexture(textureFileName[ID_FLOOD_LIGHT], ID_FLOOD_LIGHT);
    loadTexture(textureFileName[ID_METAL], ID_METAL);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    //glutReshapeFunc(resize);
    glutTimerFunc(100, animate, 1);
    glutKeyboardFunc(keyboardCallback);
    glEnable(GL_LIGHTING);
    //glEnable(GL_COLOR_MATERIAL);

    // light();
    glutDisplayFunc(displayTest);
}

int main(int argc, char** argv) {
    resetAll();

    initTexture();

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_SINGLE);

    int type = 0;
    display_work();
    glutMainLoop();
    return 0;
}
