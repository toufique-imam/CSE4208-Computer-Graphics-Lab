#include "Human.h"

Human::Human() {
    setHead(0, 0);
    setHeadAngle(0, 0, 0, 0);

    setUpHand(0, 0, 0);
    set_Up_Left_Hand_Angle(0, 0, 0, 0);
    set_Up_Right_Hand_Angle(0, 0, 0, 0);

    setUpLeg(0, 0, 0);
    set_Up_Left_Leg_Angle(0, 0, 0, 0);
    set_Up_Right_Leg_Angle(0, 0, 0, 0);

    setDownHand(0, 0, 0);
    set_Down_Left_Hand_Angle(0, 0, 0, 0);
    set_Down_Right_Hand_Angle(0, 0, 0, 0);

    setDownLeg(0, 0, 0);
    set_Down_Left_Leg_Angle(0, 0, 0, 0);
    set_Down_Right_Leg_Angle(0, 0, 0, 0);
}

void Human::setColor(Cube dummy) {
    GLfloat mat_shininess[] = {dummy.shines[0]};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, dummy.surfaceLights[0][0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dummy.surfaceLights[1][0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, dummy.surfaceLights[2][0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}
void Human::drawHead() {
    Cube dummy;
    dummy.setSurfaceLights(dummy.offYellow);
    dummy.shines[0] = 50;

    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();
    float golaH = (headH * 40.0) / 100.0;
    float golaR = (headR * 60.0) / 100.0;

    glPushMatrix();
    dummy.setSurfaceLights(dummy.darkyellow);
    setColor(dummy);
    glTranslatef(0, 0, golaH + headH);
    glutSolidSphere(headR, 60, 60);
    glPopMatrix();

    //face
    glPushMatrix();
    setColor(dummy);
    glTranslatef(0, 0, golaH);
    gluCylinder(quadratic, headR, headR, headH, 60, 60);
    glPopMatrix();

    //gola
    glPushMatrix();
    setColor(dummy);
    gluCylinder(quadratic, golaR, golaR, golaH, 60, 60);
    glPopMatrix();
}

void Human::drawBat() {
    GLdouble upHandRadius = sqrt((upHandX * upHandY * 1.0) / (2.0 * acos(-1)));
    GLdouble downHandRadius = sqrt((downHandX * downHandY * 1.0) / (2.0 * acos(-1)));

    float batHandleRadius = downHandRadius * .8;
    float batHandleHeight = downHandZ + downHandZ * .3;
    float batBodyY = upLegY + upLegY * .5;
    float batBodyZ = upLegZ + upLegZ * .6;
    float batBodyX = upLegX * .4;

    //handle
    glPushMatrix();
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, IDS[ID_GRIP]);
        gluCylinder(gluNewQuadric(), batHandleRadius, batHandleRadius, batHandleHeight, 60, 60);

        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glBindTexture(GL_TEXTURE_2D, IDS[ID_WOOD]);
        glEnable(GL_TEXTURE_2D);

        glTranslatef(0, 0, -batBodyZ / 2.0);
        glScalef(batBodyX, batBodyY, batBodyZ);
        glutSolidCube(1);
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

}
void Human::drawLeg(float downAngles[]) {
    GLdouble upLegRadius = sqrt((upLegX * upLegY * 1.0) / (2.0 * acos(-1)));
    GLdouble downLegRadius = sqrt((downLegX * downLegY * 1.0) / (2.0 * acos(-1)));
    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();

    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, IDS[ID_WHITE_CLOTH]);
    glPushMatrix();
    {
        gluCylinder(quadratic, upLegRadius, upLegRadius, upLegZ, 60, 60);
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluSphere(quadratic, upLegY / 2.0, 60, 10);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(downAngles[0], downAngles[1], downAngles[2], downAngles[3]);
        glTranslatef(0, 0, -downLegZ);
        gluCylinder(quadratic, downLegRadius, downLegRadius, downLegZ, 60, 60);
    }
    glPopMatrix();

    //glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    {
        glRotatef(downAngles[0], downAngles[1], downAngles[2], downAngles[3]);
        glTranslatef(0, 0, -downLegZ+upLegY/2.0);
        gluSphere(quadratic, upLegY / 2.0, 60, 10);
    }
    glPopMatrix();
}
void Human::drawLegs() {
    Cube dummy;
    dummy.setSurfaceLights(dummy.browns);
    dummy.shines[0] = 40;
    setColor(dummy);

    GLdouble upLegRadius = sqrt((upLegX * upLegY * 1.0) / (2.0 * acos(-1)));
    GLdouble downLegRadius = sqrt((downLegX * downLegY * 1.0) / (2.0 * acos(-1)));

    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();
    float padding = (bodyX * 20.0) / 100.0;

    //leg right
    glPushMatrix();
    {
        glTranslatef(padding, 0, downLegZ + upLegZ);
        glRotatef(upRightLegAngle[0], upRightLegAngle[1], upRightLegAngle[2], upRightLegAngle[3]);
        glTranslatef(0, 0, -upLegZ);
        drawLeg(downRightLegAngle);
    }
    glPopMatrix();

    //leg left
    glPushMatrix();
    {
        glTranslatef(bodyX - padding, 0, downLegZ + upLegZ);
        glRotatef(upLeftLegAngle[0], upLeftLegAngle[1], upLeftLegAngle[2], upLeftLegAngle[3]);
        glTranslatef(0, 0, -upLegZ);
        drawLeg(downLeftLegAngle);
    }
    glPopMatrix();
}
void Human::drawHand(float downAngles[]) {
    GLdouble upHandRadius = sqrt((upHandX * upHandY * 1.0) / (2.0 * acos(-1)));
    GLdouble downHandRadius = sqrt((downHandX * downHandY * 1.0) / (2.0 * acos(-1)));
    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();

    //hand up
    glPushMatrix();
    {
        gluCylinder(quadratic, upHandRadius, upHandRadius, upHandZ, 60, 60);
    }
    glPopMatrix();

    //hand socket
    glPushMatrix();
    {
        gluSphere(quadratic, upHandY / 2.0, 60, 10);
    }
    glPopMatrix();
    float coff = 2.0 * downHandZ * cos(downAngles[0]);
    //hand down
    glPushMatrix();
    {
        glRotatef(downAngles[0], downAngles[1], downAngles[2], downAngles[3]);
        glTranslatef(0, 0, -downHandZ);
        gluCylinder(quadratic, downHandRadius, downHandRadius, downHandZ, 60, 60);
    }
    glPopMatrix();
}
void Human::drawHands() {
    Cube dummy;
    dummy.setSurfaceLights(dummy.offwhite1);
    dummy.shines[0] = 40;
    setColor(dummy);

    GLdouble upHandRadius = sqrt((upHandX * upHandY * 1.0) / (2.0 * acos(-1)));
    GLdouble downHandRadius = sqrt((downHandX * downHandY * 1.0) / (2.0 * acos(-1)));

    //right hand
    glPushMatrix();
    {
        glTranslatef(-upHandRadius, 0, 0);
        glRotatef(upRightHandAngle[0], upRightHandAngle[1], upRightHandAngle[2], upRightHandAngle[3]);
        glTranslatef(0, 0, -upHandZ);
        drawHand(downRightHandAngle);
        if (withBat) {
            glPushMatrix();
            {
                glTranslatef(bodyX / 2.0, 0, -upHandZ);
                drawBat();
            }
            glPopMatrix();
        }
    }
    glPopMatrix();

    //left hand
    glPushMatrix();
    {
        glTranslatef(bodyX + upHandRadius, 0, 0);
        glRotatef(upLeftHandAngle[0], upLeftHandAngle[1], upLeftHandAngle[2], upLeftHandAngle[3]);
        glTranslatef(0, 0, -upHandZ);
        drawHand(downLeftHandAngle);
    }
    glPopMatrix();
}
void Human::drawBody() {
    Cube dummy;
    dummy.setSurfaceLights(dummy.blue);
    dummy.shines[0] = 40;

    GLdouble upHandRadius = sqrt((upHandX * upHandY * 1.0) / (2.0 * acos(-1)));

    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();

    dummy.setValue(bodyX, bodyY, bodyZ);
    //body
    glPushMatrix();
    {
        setColor(dummy);
        dummy.drawCube();
    }
    glPopMatrix();
    //hand socket right
    dummy.setSurfaceLights(dummy.browns);
    glPushMatrix();
    {
        setColor(dummy);
        glTranslatef(-upHandRadius, bodyY / 2.0, bodyZ);
        gluSphere(quadratic, upHandY / 2.0, 60, 10);
    }
    glPopMatrix();
    //hand socket left
    glPushMatrix();
    {
        setColor(dummy);
        glTranslatef(bodyX + upHandRadius, bodyY / 2.0, bodyZ);
        gluSphere(quadratic, upHandY / 2.0, 60, 10);
    }
    glPopMatrix();
}
void Human::printData() {
    cout << "head " << headH << " " << headR << "\n";
    cout << "Body " << bodyX << " " << bodyY << " " << bodyZ << "\n";
    cout << "uH " << upHandX << " " << upHandY << " " << upHandZ << "\n";
    cout << "dH " << downHandX << " " << downHandY << " " << downHandZ << "\n";
    cout << "uL " << upLegX << " " << upLegY << " " << upLegZ << "\n";
    cout << "uL " << downLegX << " " << downLegY << " " << downLegZ << "\n";
}
void Human::drawHuman() {
    //head
    //printData();
    glPushMatrix();
    {
        glTranslatef(bodyX / 2, bodyY / 2, upLegZ + downLegZ + bodyZ);
        // //glTranslatef(bodyX / 2, bodyY / 2, upLegZ+downLegZ);
        //glRotatef(headAngle[0], headAngle[1], headAngle[2], headAngle[3]);
        drawHead();
    }
    glPopMatrix();

    //hand
    glPushMatrix();
    {
        glTranslatef(0, bodyY / 2, upLegZ + downLegZ + bodyZ);
        drawHands();
    }
    glPopMatrix();

    //legs
    glPushMatrix();
    {
        glTranslatef(0, bodyY / 2, 0);
        drawLegs();
    }
    glPopMatrix();

    // //body
    glPushMatrix();
    {
        glTranslatef(0, 0, upLegZ + downLegZ);
        drawBody();
    }
    glPopMatrix();
}
