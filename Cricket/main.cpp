#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "BazierCurve.h"
#include "BmpLoader.h"
#include "Cube.h"
#include "DotMatrixDisplay.h"
#include "Human.h"
#include "Stadium.h"
#include <glm/glm.hpp>
#define error(x) cerr << #x << "=" << x << ";\n";


bool animationOn = true;

int windowWidth = 1000, windowHeight = 1000;
int angleNow = 95;

float r1 = 255, g1 = 0, b1 = 0;
float r2 = 0, g2 = 255, b2 = 0;

int viewPositionT[5][3];
int viewPositionCenter[5][3];
int viewIndex = 0;

int lightOn[5];

int fieldSize = 2000;
int pitchX = 100;
int pitchY = 600;
int stadiumHeight = 500;
GLfloat light_position_down_left[] = {-fieldSize / 2, -fieldSize / 2, stadiumHeight + stadiumHeight - 50, 1.0};
GLfloat light_position_down_right[] = {fieldSize / 2, -fieldSize / 2, stadiumHeight + stadiumHeight - 50, 1.0};
GLfloat light_position_down_spot[] = {0, -fieldSize / 2, 100, 1.0};
GLfloat light_position_up_left[] = {-fieldSize / 2, fieldSize / 2, stadiumHeight + stadiumHeight - 50, 1.0};
GLfloat light_position_up_right[] = {fieldSize / 2, fieldSize / 2, stadiumHeight + stadiumHeight - 50, 1.0};

bool helpFlag = 0;

int rightFront = 0, bowlerReached = 0, bowlerPosY = 0,
    incrementBowlerPos = 5, maxPos = 100, releaseBall = 0, celebMax = 250;

int batsmanMoves = 0;
int strikeState = 0;
int strikeDir = 0;
bool stampOut = 0;
float ballLoc[3];
float ballVelocity[3];
bool startBall = 0;
int handAngle = 0;
int increment = 5;
int runScored = 0;
int bowledOut = 0;
int position_score1[3];
int position_score2[3];
bool ballStroke = 0;
int celebration = 0;
bool celebReached = 0;
bool goBack = 0;
bool celebEnded = 0;
bool ambient=1, specular=1, diffuse=1;
void viewInit() {
    /*
    default view
    */
    viewPositionT[0][0] = -17, viewPositionT[0][1] = 425, viewPositionT[0][2] = 105;
    viewPositionCenter[0][0] = -52, viewPositionCenter[0][1] = -875, viewPositionCenter[0][2] = 35;
    /*
    bowler View 1
    */
    viewPositionT[1][0] = -55, viewPositionT[1][1] = -487, viewPositionT[1][2] = 118;
    viewPositionCenter[1][0] = 123, viewPositionCenter[1][1] = 325, viewPositionCenter[1][2] = 30;
    /*
    bowler View 2
    */
    viewPositionT[2][0] = 200, viewPositionT[2][1] = -487, viewPositionT[2][2] = 118;
    viewPositionCenter[2][0] = -22, viewPositionCenter[2][1] = 325, viewPositionCenter[2][2] = 30;
    /*
    Birds eye view
    */
    viewPositionT[3][0] = 1890, viewPositionT[3][1] = -487, viewPositionT[3][2] = 2713;
    viewPositionCenter[3][0] = -942, viewPositionCenter[3][1] = -420, viewPositionCenter[3][2] = -1035;
    /*
    left bird view
    */
    viewPositionT[4][0] = 1090, viewPositionT[4][1] = -482, viewPositionT[4][2] = 768;
    viewPositionCenter[4][0] = -257, viewPositionCenter[4][1] = 220, viewPositionCenter[4][2] = -120;
}
void resetAll() {
    rightFront = 0, bowlerReached = 0, bowlerPosY = 10,
    incrementBowlerPos = 5, maxPos = 100, releaseBall = 0;
    batsmanMoves = 0;
    strikeState = 0;
    strikeDir = 0;
    ballLoc[2] = 50;
    ballLoc[0] = -20;
    ballLoc[1] = 0;
    ballVelocity[1] = 9;
    ballVelocity[2] = -1;
    ballVelocity[0] = 0.2;
    startBall = 0;
    increment = 5;
    stampOut = 0;
    ballStroke = 0;
    celebration = 0;
    celebReached = 0;
    celebEnded = 0;
    goBack = 0;
    for (int i = 0; i < 4; i++)
        lightOn[i] = 1;
}

void createLight(int idx, int lightNum, GLfloat light_position[]) {
    GLfloat no_light[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[] = {0.8, 0.8, .8, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};

    if (!ambient) {
        light_ambient[0] = 0.0;
        light_ambient[1] = 0.0;
        light_ambient[2] = 0.0;
    }
    if (!diffuse) {
        light_diffuse[0] = 0.0;
        light_diffuse[1] = 0.0;
        light_diffuse[2] = 0.0;
    }
    if (!specular) {
        light_specular[0] = 0.0;
        light_specular[1] = 0.0;
        light_specular[2] = 0.0;
    }
    if (lightOn[idx]) {
        glEnable(lightNum);
        glLightfv(lightNum, GL_AMBIENT, light_ambient);
        glLightfv(lightNum, GL_DIFFUSE, light_diffuse);
        glLightfv(lightNum, GL_SPECULAR, light_specular);
        glLightfv(lightNum, GL_POSITION, light_position);

    } else
        glDisable(lightNum);
    glDisable(GL_LIGHT5);
}
void spot_light() {
    GLfloat no_light[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[] = {0.9, 0.9, .9, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};

    if (!ambient) {
        light_ambient[0] = 0.0;
        light_ambient[1] = 0.0;
        light_ambient[2] = 0.0;
    }
    if (!diffuse) {
        light_diffuse[0] = 0.0;
        light_diffuse[1] = 0.0;
        light_diffuse[2] = 0.0;
    }
    if (!specular) {
        light_specular[0] = 0.0;
        light_specular[1] = 0.0;
        light_specular[2] = 0.0;
    }

    if (lightOn[4]) {
        glEnable(GL_LIGHT6);
        glLightfv(GL_LIGHT6, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT6, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT6, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT6, GL_POSITION, light_position_down_spot);

        GLfloat spot_direction1[] = {0.0, 0.0, 1.0};
        glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spot_direction1);
        glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 40.0);

        //glEnable(GL_LIGHT3);
        //glLightfv(GL_LIGHT7, GL_AMBIENT, light_ambient);
        //glLightfv(GL_LIGHT7, GL_DIFFUSE, light_diffuse);
        //glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
        //glLightfv(GL_LIGHT3, GL_POSITION, light_position2);

        //GLfloat spot_direction2[] = {0.0, 0.0, -1.0};
        //glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction2);
        //glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 40.0);
    } else {
        glDisable(GL_LIGHT6);
        //glDisable(GL_LIGHT3);
    }
}

void animate(int) {
    if (helpFlag) {
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
        if (stampOut && !celebEnded) {
            if (!celebReached)
                bowlerPosY += 2 * incrementBowlerPos;
            else {
                if (goBack) {
                    bowlerPosY -= incrementBowlerPos;
                } else if (celebration == 10) {
                    //go back
                    goBack = 1;
                } else {
                    celebration++;
                }
            }
        } else {
            if (!bowlerReached) {
                bowlerPosY += incrementBowlerPos;
            } else if (bowlerPosY >= maxPos) {
                if (releaseBall < 9) {
                    releaseBall++;
                    bowlerPosY += 3;
                } else {
                    releaseBall = 9;
                    bowlerPosY = maxPos + incrementBowlerPos;
                }
            }
        }
        glutPostRedisplay();  ////Tell GLUT that the scene has changed
        if (startBall)
            glutTimerFunc(30, animate, 1);
        else
            glutTimerFunc(100, animate, 1);
    } else {
        glutTimerFunc(100, animate, 1);
    }
}

//moves object
void drawBall() {
    if (ballLoc[2] < 10) {
        cout << "Colided " << ballLoc[1] << "\n";
        ballVelocity[2] = -2 * ballVelocity[2];
    }
    if (ballLoc[1] > pitchY - 50 && ballLoc[1] < pitchY - 10) {
        if (strikeState) {
            cout << "HIT " << ballLoc[0] << " " << ballLoc[1] << " " << ballLoc[2] << "\n";

            if (!ballStroke)
                runScored++;
            ballStroke = 1;
            if (strikeDir == -1) {
                ballVelocity[0] = 10;
                ballVelocity[1] = -10;
                ballVelocity[2] = 10;

            } else if (strikeDir == 1) {
                ballVelocity[1] = -10;
                ballVelocity[2] = 10;

            } else if (strikeDir == 2) {
                ballVelocity[0] = -10;
                ballVelocity[1] = -10;
                ballVelocity[2] = 10;
            }
        }
    }
    if (ballLoc[1] >= pitchY) {
        startBall = 0;
        bowledOut++;
        cout << "OUT " << ballLoc[0] << " " << ballLoc[1] << " " << ballLoc[2] << "\n";
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

    glPushMatrix();
    {
        //glEnable(GL_TEXTURE_2D);
        //glBindTexture(GL_TEXTURE_2D, IDS[ID_BALL]);

        Cube dummy;
        dummy.setColor(255, 255, 255);
        glTranslatef(ballLoc[0], ballLoc[1] - pitchY / 2 + 5, ballLoc[2]);
        setMatLight(dummy);
        //dummy.setValue(10 , 10 , 10);
        //dummy.drawCube();
        //glutSolidSphere(10, 20, 20);

        GLUquadric* quad = gluNewQuadric();
        gluQuadricTexture(quad, true);
        gluSphere(quad, 5, 20, 20);
        //glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}

int calculateBowlerState() {
    int state;
    if (celebEnded)
        state = 3;
    else if (!bowlerReached) {
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
            if (stampOut) {
                if (goBack) {
                    if (rightFront)
                        state = 1;
                    else
                        state = 0;
                    if (bowlerPosY <= maxPos) {
                        state = 3;
                        goBack = 0;
                        celebReached = 0;
                        celebration = 0;
                        celebEnded = 1;
                    }
                } else {
                    if (celebReached)
                        state = 4;
                    else {
                        if (rightFront)
                            state = 1;
                        else
                            state = 0;
                        if (bowlerPosY >= celebMax) {
                            celebReached = 1;
                        }
                    }
                }
            } else {
                state = 3;
            }
        }
    }
    return state;
}

void createBowler() {
    int state = calculateBowlerState();
    //error(state);
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
    } else if (state == 4) {
        //celebration++;
        glTranslatef(0, bowlerPosY, 0);
        bowler = Human::celebBowler(celebration);
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

//todo add body rotation
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
void createUmpire(bool isUmpire) {
    Human umpire = Human::generalHumanConfig();
    umpire.setBatStatus(false);
    glPushMatrix();
    if (isUmpire && stampOut && !celebEnded && !celebReached) {
        Human::humanBatsmanLeftConfig(umpire, 0);
        Human::humanUmpireRightConfig(umpire);
    } else {
        Human::humanBatsmanLeftConfig(umpire, 0);
        Human::humanBatsmanRightConfig(umpire, 0);
    }
    umpire.drawHuman();
    glPopMatrix();
}

//doesn't move objects
void createField() {
    Cube cube(1, 1, 1);
    //field

    glPushMatrix();
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, IDS[ID_GRASS]);

        cube.setRepeat(4);
        cube.setSurfaceLights(cube.green);
        glTranslatef(-fieldSize / 2, -fieldSize / 2, 0);
        glScalef(fieldSize, fieldSize, 2);
        cube.drawCube();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}

void createPitch() {
    Cube cube(1, 1, 1);
    cube.setRepeat(1);
    cube.setSurfaceLights(cube.offwhite2);

    //field
    glPushMatrix();
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, IDS[ID_PITCH]);

        glTranslatef(-pitchX / 2, -pitchY / 2, 4);
        glScalef(pitchX, pitchY, 2);
        cube.drawCube();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}

void drawBoundary() {
    Cube cube(1, 1, 1);
    cube.setSurfaceLights(cube.white);

    glPushMatrix();
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, IDS[ID_BANNER2]);

        GLUquadricObj* quadratic;
        quadratic = gluNewQuadric();
        gluQuadricTexture(quadratic, TRUE);

        setMatLight(cube);
        gluCylinder(quadratic, fieldSize / 2 - 100,
                    fieldSize / 2 - 100, 50, 10, 1);
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}

void drawStampMark() {
    Cube cube(1, 1, 1);
    cube.setSurfaceLights(cube.white);

    glPushMatrix();
    {
        glTranslatef(-pitchX / 2 - 25, 0, 0);
        glScalef(pitchX + 50, 2, 2);
        cube.drawCube();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-pitchX / 2 + 20, -20, 0);
        glScalef(2, pitchX + 50, 2);
        cube.drawCube();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(pitchX / 2 - 20, -20, 0);
        glScalef(2, pitchX + 50, 2);
        cube.drawCube();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-pitchX / 2 - 25, pitchX, 0);
        glScalef(pitchX + 50, 2, 2);
        cube.drawCube();
    }
    glPopMatrix();
}
void drawSmallBoundary() {
    Cube cube(1, 1, 1);
    cube.setSurfaceLights(cube.white);

    glPushMatrix();
    {
        GLUquadricObj* quadratic;
        quadratic = gluNewQuadric();
        //gluQuadricTexture(quadratic, TRUE);

        setMatLight(cube);
        gluCylinder(quadratic, fieldSize / 4,
                    fieldSize / 4, 10, 60, 1);
    }
    glPopMatrix();
}
void drawStadium() {
    Cube cube(1, 1, 1);
    Stadium stadium(10);
    glPushMatrix();
    {
        stadium.setColor(255, 0, 0);
        glTranslatef(1000, -fieldSize / 2, 0);
        glRotatef(90, 0, 0, 1);
        glScalef(50, 2000, 50);
        stadium.drawStadium();
    }
    glPopMatrix();

    glPushMatrix();
    {
        stadium.setColor(255, 0, 0);
        glTranslatef(fieldSize / 2, 1000, 0);
        glRotatef(180, 0, 0, 1);
        glScalef(50, 2000, 50);
        stadium.drawStadium();
    }
    glPopMatrix();

    glPushMatrix();
    {
        stadium.setColor(255, 0, 0);
        glTranslatef(-1000, fieldSize / 2, 0);
        glRotatef(270, 0, 0, 1);
        glScalef(50, 2000, 50);
        stadium.drawStadium();
    }
    glPopMatrix();

    glPushMatrix();
    {
        stadium.setColor(255, 0, 0);
        glTranslatef(-fieldSize / 2, -1000, 0);
        glRotatef(360, 0, 0, 1);
        glScalef(50, 2000, 50);
        stadium.drawStadium();
    }
    glPopMatrix();
}
void light1() {
    GLfloat no_light[] = {0, 0, 0, 1.0};

    GLfloat light_ambient[] = {.60, .60, .60, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {-30, 15, 15, 1.0};

    glLightfv(GL_LIGHT5, GL_POSITION, light_position);
    glLightfv(GL_LIGHT5, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT5, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT5, GL_SPECULAR, light_specular);
    glEnable(GL_LIGHT5);
}
void material_prop(double dr, double dg, double db, int amb = 0, bool emi = false, int side = 0) {
    GLfloat mat_ambient[] = {dr / 2.0, dg / 2.0, db / 2.0, 1.0};
    if (amb == 1)
        GLfloat mat_ambient[] = {dr, dg, db, 1.0};
    GLfloat mat_diffuse[] = {dr, dg, db, 1.0};
    GLfloat mat_specular[] = {.5, .5, .5, 1.0};
    GLfloat mat_shininess[] = {60};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    if (side == 2) {
        glMaterialfv(GL_BACK, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_BACK, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_BACK, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_BACK, GL_SHININESS, mat_shininess);
    }

    if (emi == true) {
        GLfloat mat_emission[] = {dr, dg, db, 1.0};
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    } else {
        GLfloat mat_emission[] = {0, 0, 0, 0.0};
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
}
void drawText(GLfloat trans_x, GLfloat trans_y, GLfloat trans_z, void* font, const char* textstring, int length, double dr, double dg, double db) {
    glPushMatrix();
    material_prop(dr, dg, db, 1);

    glRasterPos3f(trans_x, trans_y, trans_z);
    for (int i = 0; i < length; i++) {
        glutBitmapCharacter(font, (int)textstring[i]);
    }
    glPopMatrix();
}

void showHelps() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(90, w / h, 0.1, 2000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glViewport(0, 0, w, h);

    light1();

    glPushMatrix();

    gluLookAt(-15, 15, 15, 5, 15, 15, 0, 0, 1);

    std::string text;
    text = "KEY OPTIONS";
    drawText(-1.5, 17.5, 24, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "N";
    drawText(-1.5, 21.5, 22, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);
    text = "->  Move Left to your position";
    drawText(-1.5, 15.5, 22, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "M";
    drawText(-1.5, 21.5, 21, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);
    text = "->  Move right to your position";
    drawText(-1.5, 15.5, 21, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "J";
    drawText(-1.5, 21.5, 20, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);
    text = "->  Left Hit";
    drawText(-1.5, 15.5, 20, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "K";
    drawText(-1.5, 21.5, 19, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);
    text = " ->  Straight Hit";
    drawText(-1.5, 15.5, 19, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "L";
    drawText(-1.5, 21.5, 18, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);
    text = "->  Right Hit";
    drawText(-1.5, 15.5, 18, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "Q/q";
    drawText(-1.5, 21.5, 17, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);
    text = "->  Looking Right/Left";
    drawText(-1.5, 15.5, 17, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "W/w";
    drawText(-1.5, 21.5, 16, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);
    text = "->  Looking forward/backward";
    drawText(-1.5, 15.5, 16, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "E/e";
    drawText(-1.5, 21.5, 15, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);
    text = "->  Looking Up/Down";
    drawText(-1.5, 15.5, 15, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "Z/z";
    drawText(-1.5, 21.5, 14, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);
    text = "->  Turning Up/Down";
    drawText(-1.5, 15.5, 14, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "X/x";
    drawText(-1.5, 21.5, 13, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);
    text = "->  Turning Left/Right";
    drawText(-1.5, 15.5, 13, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "C/c";
    drawText(-1.5, 21.5, 12, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);
    text = "->  TUrning Forward/Backward";
    drawText(-1.5, 15.5, 12, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "1/2/3/4";
    drawText(-1.5, 21.5, 11, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);
    text = "->  Light1/2/3/4 off/on";
    drawText(-1.5, 15.5, 11, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "V/v";
    drawText(-1.5, 21.5, 10, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);
    text = "->  Reset View/Change View";
    drawText(-1.5, 15.5, 10, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "+/-";
    drawText(-1.5, 21.5, 9, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);
    text = "->  Change FOV";
    drawText(-1.5, 15.5, 9, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "r";
    drawText(-1.5, 21.5, 8, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);
    text = "->  Reset";
    drawText(-1.5, 15.5, 8, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    text = "Press Any Key to continue...";
    drawText(-1.5, 10, 7, GLUT_BITMAP_TIMES_ROMAN_24, text.data(), text.size(), 0, 191.0 / 255.0, 55.0 / 255.0);

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void drawPoll(GLfloat positionx, GLfloat positiony, GLfloat positionz, int angle) {
    Cube cube(1, 1, 1);
    cube.setSurfaceLights(cube.offwhite1);
    glPushMatrix();
    {
        GLUquadricObj* quadratic;
        quadratic = gluNewQuadric();
        gluQuadricTexture(quadratic, true);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, IDS[ID_METAL]);

        setMatLight(cube);
        glTranslatef(positionx, positiony, 0);
        gluCylinder(quadratic, 10, 10, positionz + stadiumHeight - 100, 10, 10);
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, IDS[ID_FLOOD_LIGHT]);

        setMatLight(cube);
        glTranslatef(positionx - 150, positiony, positionz + stadiumHeight - 100);
        cube.setRepeat(4);
        //glRotatef(angle , -1 , 0 , -1);
        if (angle) {
            glTranslatef(300, 0, 0);
            glRotatef(180, 0, 0, 1);
        }
        glScalef(300, 20, 400);

        cube.drawCube();

        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}

void drawPolls() {
    drawPoll(light_position_down_left[0] + 50, light_position_down_left[1] + 50, stadiumHeight, 0);
    drawPoll(light_position_down_right[0] - 50, light_position_down_right[1] + 50, stadiumHeight, 0);
    drawPoll(light_position_up_left[0] + 50, light_position_up_left[1] - 50, stadiumHeight, 1);
    drawPoll(light_position_up_right[0] - 50, light_position_up_right[1] - 50, stadiumHeight, 1);
}
int theta = 0;
//int thetaMin = 0, thetaMax = 360;
int thetaIncr = 2;

void drawFlag(GLfloat positionx, GLfloat positiony, GLfloat positionz) {
    Cube cube(1, 1, 1);
    cube.setSurfaceLights(cube.offwhite1);
    glPushMatrix();
    {
        GLUquadricObj* quadratic;
        quadratic = gluNewQuadric();
        gluQuadricTexture(quadratic, true);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, IDS[ID_METAL]);

        setMatLight(cube);
        glTranslatef(positionx, positiony, 0);
        gluCylinder(quadratic, 10, 10, positionz, 10, 10);
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
    BazierCurve flag;

    glPushMatrix();
    {
        // glEnable(GL_TEXTURE_2D);
        // glBindTexture(GL_TEXTURE_2D, IDS[ID_FLOOD_LIGHT]);
        //
        theta += thetaIncr;
        //if (theta >= thetaMax)
        //  thetaIncr = -thetaIncr;
        //if (theta <= thetaMin)
        //   thetaIncr = -thetaIncr;
        //error(theta);
        glTranslatef(positionx, positiony, positionz - 40);
        //cube.setSurfaceLights(cube.green);
        //setMatLight(cube);
        glScalef(1, 1, 3.5);
        glRotatef(90, 1, 0, 0);
        flag.drawFlag(theta);

        //glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

    // glPushMatrix();
    // {
    //     glTranslatef(10, 10, 10);
    //     cube.setColor(255, 0, 0);
    //     setMatLight(cube);
    //     glPointSize(5);
    //     glTranslatef(positionx - 20, positiony - 10, positionz - 80);
    //     glRotatef(90, 1, 0, 0);
    //     flag.DrawCircle(20, 60);
    // }
    // glPopMatrix();
}

string my_to_string(int x) {
    string ans = "";
    if (x == 0)
        return "0";
    int sign = 0;
    if (x < 0) {
        sign = 1;
        x = -x;
    }
    while (x > 0) {
        ans += char(x % 10 + '0');
        x = x / 10;
    }
    reverse(ans.begin(), ans.end());
    if (sign)
        ans = "-" + ans;
    return ans;
}

void drawScrore() {
    DotMatrixDisplay dotMatrixDisplay;
    dotMatrixDisplay.setColor(255, 0, 0);
    dotMatrixDisplay.setScale(1);
    string scoreRun = "HIT - " + my_to_string(runScored);
    string scoreMiss = "OUT - " + my_to_string(bowledOut);
    Cube container;

    glPushMatrix();
    {
        glTranslatef(position_score1[0], position_score1[1], position_score1[2]);
        glScalef(3, 3, 3);
        dotMatrixDisplay.drawMessage(scoreRun);
    }
    glPopMatrix();
    container.setValue(1, 1, 1);
    //drawContainer

    glPushMatrix();
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, IDS[ID_SCORE_BOARD]);

        container.setSurfaceLights(container.white);

        glTranslatef(-150, position_score1[1] - 10, 300);
        glScalef(300, 1, 200);
        container.setRepeat(2);
        container.drawCube();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

    glPushMatrix();
    {
        GLUquadricObj* quadratic;
        quadratic = gluNewQuadric();
        gluQuadricTexture(quadratic, true);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, IDS[ID_METAL]);

        setMatLight(container);
        glTranslatef(-0, position_score1[1] - 20, 0);
        gluCylinder(quadratic, 10, 10, 400, 10, 10);
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(position_score2[0], position_score1[1], position_score2[2]);
        glScalef(3, 3, 3);
        dotMatrixDisplay.drawMessage(scoreMiss);
    }
    glPopMatrix();
}

void createStamp(bool batsmanStamp) {
    Cube dummy;
    dummy.setSurfaceLights(dummy.white);
    glPushMatrix();
    {
        BazierCurve bazierCurve;
        bazierCurve.wired = 0;
        bazierCurve.shcpt = 0;
        if (stampOut && batsmanStamp) {
            glTranslatef(-2, -5, 10);
        } else {
            glTranslatef(-2, 0, 52);
        }

        glScalef(1.5, 2, 2);
        bazierCurve.drawBell();
    }
    glPopMatrix();
    for (int i = -1; i < 2; i++) {
        glPushMatrix();
        {
            GLUquadricObj* quadratic;
            quadratic = gluNewQuadric();
            gluQuadricTexture(quadratic, true);

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, IDS[ID_BALL]);

            setMatLight(dummy);
            glTranslatef(5 * i, 0, 2);
            if (stampOut && batsmanStamp) {
                glRotatef(10 * i, 0, 1, 0);
                glRotatef(10 * (i == 0), -1, 0, 0);
            }
            gluCylinder(quadratic, 1.5, 1.5, 50, 60, 60);

            glDisable(GL_TEXTURE_2D);
        }
        glPopMatrix();
    }
}
void playCricket() {
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
        viewPositionT[viewIndex][0], viewPositionT[viewIndex][1], viewPositionT[viewIndex][2],
        viewPositionCenter[viewIndex][0], viewPositionCenter[viewIndex][1], viewPositionCenter[viewIndex][2],
        0, 0, 1);
    createLight(0, GL_LIGHT0, light_position_down_left);
    createLight(1, GL_LIGHT1, light_position_down_right);
    createLight(2, GL_LIGHT2, light_position_up_left);
    createLight(3, GL_LIGHT3, light_position_up_right);

    Cube cube(1, 1, 1);
    //field
    glPushMatrix();
    {
        createField();
    }
    glPopMatrix();

    //pitch
    glPushMatrix();
    {
        createPitch();
    }
    glPopMatrix();

    //display Score
    glPushMatrix();
    {
        drawScrore();
    }
    glPopMatrix();

    //ball
    if (startBall) {
        glPushMatrix();
        {
            drawBall();
        }
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
        //cube.drawCube();
    }
    glPopMatrix();

    //bowler
    glPushMatrix();
    {
        glTranslatef(-40, -(pitchY - pitchY / 3), 2);
        createBowler();
    }
    glPopMatrix();

    //umpire
    glPushMatrix();
    {
        glTranslatef(0, -(pitchY - pitchY / 3) + 100, 2);
        createUmpire(true);
    }
    glPopMatrix();
    //fielder1
    for (int i = -1; i < 2; i++) {
        if (!i)
            continue;
        for (int j = -1; j < 2; j++) {
            if (!j)
                continue;
            glPushMatrix();
            {
                glTranslatef(i * fieldSize / 4, j * fieldSize / 4, 2);

                if (j > 0) {
                    glRotatef(180, 0, 0, 1);
                }
                createUmpire(false);
            }
            glPopMatrix();
        }
    }
    for (int i = -1; i < 2; i++) {
        if (!i)
            continue;
        glPushMatrix();
        {
            glTranslatef(i * fieldSize / 3, 0, 2);

            if (i > 0) {
                glRotatef(90, 0, 0, 1);
            } else {
                glRotatef(90, 0, 0, -1);
            }
            createUmpire(false);
        }
        glPopMatrix();
    }
    //batsman
    glPushMatrix();
    {
        glTranslatef(0, pitchY / 2 - 60, 2);
        glTranslatef(batsmanMoves * 4 + 10, 0, 0);
        glRotatef(90, 0, 0, 1);
        createBatsman();
    }
    glPopMatrix();

    glPushMatrix();
    {
        drawBoundary();
    }
    glPopMatrix();

    glPushMatrix();
    {
        drawStadium();
    }
    glPopMatrix();
    glPushMatrix();
    {
        drawPolls();
    }
    glPopMatrix();

    glPushMatrix();
    {
        //glRotatef(30, 0, 0, 1);
        drawFlag(light_position_down_left[0] + 250, light_position_down_left[1] + 250, stadiumHeight);
    }
    glPopMatrix();
    //white markings
    glPushMatrix();
    {
        drawSmallBoundary();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0, pitchY / 2 - 100, 10);
        drawStampMark();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0, -pitchY / 2, 10);
        drawStampMark();
    }
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}
void displayTest() {
    if (!helpFlag) {
        showHelps();
    } else {
        playCricket();
    }
}

void keyboardCallback(unsigned char key, int x, int y) {
    printf("%c\n", key);
    if (helpFlag == 0) {
        helpFlag = 1;
    } else {
        switch (key) {
        case 'a':
            ambient = !ambient;
            break;
        case 's':
            specular = !specular;
            break;
        case 'd':
            diffuse = !diffuse;
            break;

        case 'v':
            viewIndex++;
            viewIndex %= 5;
            break;
        case 'V':
            viewIndex = 0;
            viewInit();
            break;
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
        case '5':
            lightOn[4] = !lightOn[4];
            break;
        case 'z':
            viewPositionT[viewIndex][2] += 5;
            break;
        case 'Z':
            viewPositionT[viewIndex][2] -= 5;
            break;
        case 'C':
            viewPositionT[viewIndex][1] -= 5;
            break;
        case 'c':
            viewPositionT[viewIndex][1] += 5;
            break;
        case 'x':
            viewPositionT[viewIndex][0] += 5;
            break;
        case 'X':
            viewPositionT[viewIndex][0] -= 5;
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
            viewPositionCenter[viewIndex][0] += 5;
            break;
        case 'w':
            viewPositionCenter[viewIndex][1] += 5;
            break;
        case 'e':
            viewPositionCenter[viewIndex][2] += 5;
            break;
        case 'Q':
            viewPositionCenter[viewIndex][0] -= 5;
            break;
        case 'W':
            viewPositionCenter[viewIndex][1] -= 5;
            break;
        case 'E':
            viewPositionCenter[viewIndex][2] -= 5;
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
    }
    printf("%d %d %d\n", viewPositionT[viewIndex][0], viewPositionT[viewIndex][1], viewPositionT[viewIndex][2]);
    printf("%d %d %d\n", viewPositionCenter[viewIndex][0], viewPositionCenter[viewIndex][1], viewPositionCenter[viewIndex][2]);
    //printf("%d %d %d\n", light1, light2, light3);
    glutPostRedisplay();
}

void display_work() {
    glutInitWindowPosition(100, 0);
    windowHeight = 1000;
    windowWidth = 1000;
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Cricket 1607040");

    position_score1[0] = 35;
    position_score1[1] = -fieldSize / 2 - 100;
    position_score1[2] = 450;
    position_score2[0] = 40;
    position_score2[1] = -fieldSize / 2 - 100;
    position_score2[2] = 360;

    for (int i = 1; i <= 12; i++) {
        loadTexture(textureFileName[i], i);
    }

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHTING);
    glEnable(GL_BLEND);

    //glutReshapeFunc(resize);
    glutTimerFunc(100, animate, 1);
    glutKeyboardFunc(keyboardCallback);

    //glEnable(GL_COLOR_MATERIAL);

    // light();
    glutDisplayFunc(displayTest);
}

int main(int argc, char** argv) {
    DotMatrixDisplay dotMatrixDisplay;
    resetAll();
    viewInit();

    initTexture();

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    int type = 0;
    display_work();
    glutMainLoop();
    return 0;
}
