#ifndef HUMAN_H
#define HUMAN_H
#include "Cube.h"

class Human
{
public:
        float headR, headH;
    //head is
    float bodyX, bodyY, bodyZ;
    float upHandX, upHandY, upHandZ;
    float downHandX, downHandY, downHandZ;
    float upLegX, upLegY, upLegZ;
    float downLegX, downLegY, downLegZ;

    float headAngle[4];
    float upLeftHandAngle[4], downLeftHandAngle[4];
    float upRightHandAngle[4], downRightHandAngle[4];

    float upLeftLegAngle[4], downLeftLegAngle[4];
    float upRightLegAngle[4], downRightLegAngle[4];
    float ballPosition[4];
    float ballInHand;
    Human();
    Human(float hR, float hH, float bX, float bY, float bZ, float upHX, float upHY, float upHZ, float downHX, float downHY, float downHZ, float upLX, float upLY, float upLZ, float downLX, float downLY, float downLZ)
    {
        setHead(hR, hH);
        setBody(bX, bY, bZ);
        setUpHand(upHX, upHY, upHZ);
        setDownHand(downHX, downHY, downHZ);
        setUpLeg(upLX, upLY, upLZ);
        setDownLeg(downLX, downLY, downLZ);
    }

    void setHead(float x, float y)
    {
        headR = x;
        headH = y;
        //cerr<<"head"<<headH<<" "<<headR<<"\n";
    }
    void setBody(float x, float y, float z)
    {
        bodyX = x;
        bodyY = y;
        bodyZ = z;

        //cerr<<"body"<<bodyX<<" "<<bodyY<<" "<<bodyZ<<"\n";
    }
    void setUpHand(float x, float y, float z)
    {
        upHandX = x;
        upHandY = y;
        upHandZ = z;

        //cerr<<"uh"<<upHandX<<" "<<upHandY<<" "<<upHandZ<<"\n";
    }
    void setDownHand(float x, float y, float z)
    {
        downHandX = x;
        downHandY = y;
        downHandZ = z;

        // cerr<<"dh"<<downHandX<<" "<<downHandY<<" "<<downHandZ<<"\n";
    }
    void setUpLeg(float x, float y, float z)
    {
        upLegX = x;
        upLegY = y;
        upLegZ = z;

        //cerr<<"ul"<<upLegX<<" "<<upLegY<<" "<<upLegZ<<"\n";
    }
    void setDownLeg(float x, float y, float z)
    {
        downLegX = x;
        downLegY = y;
        downLegZ = z;

        //cerr<<"dl"<<downLegX<<" "<<downLegY<<" "<<downLegZ<<"\n";
    }

    void drawHead();
    void drawBody();
    void drawLegs();
    void drawHands();
    void drawHand(float angles[]);
    void drawLeg(float angles[]);
    void drawHuman();
    void setColor(Cube dummy);
    void printData();
    bool withBat;
    void setBatStatus(bool hasBat){
        withBat = hasBat;
    }
    void setBallAngles(float position[]){
        ballPosition[0] = position[0];
        ballPosition[1] = position[1];
        ballPosition[2] = position[2];
    }
    void setballState(int ballState){
        ballInHand = 1;
    }
    void drawBall();
    void drawBat();

    void setHeadAngle(float angle, float x, float y, float z)
    {
        headAngle[0] = angle;
        headAngle[1] = x;
        headAngle[2] = y;
        headAngle[3] = z;
    }

    void set_Up_Right_Hand_Angle(float angle, float x, float y, float z)
    {
        upRightHandAngle[0] = angle;
        upRightHandAngle[1] = x;
        upRightHandAngle[2] = y;
        upRightHandAngle[3] = z;
    }
    void set_Up_Left_Hand_Angle(float angle, float x, float y, float z)
    {
        upLeftHandAngle[0] = angle;
        upLeftHandAngle[1] = x;
        upLeftHandAngle[2] = y;
        upLeftHandAngle[3] = z;
    }

    void set_Down_Right_Hand_Angle(float angle, float x, float y, float z)
    {
        downRightHandAngle[0] = angle;
        downRightHandAngle[1] = x;
        downRightHandAngle[2] = y;
        downRightHandAngle[3] = z;
    }

    void set_Down_Left_Hand_Angle(float angle, float x, float y, float z)
    {
        downLeftHandAngle[0] = angle;
        downLeftHandAngle[1] = x;
        downLeftHandAngle[2] = y;
        downLeftHandAngle[3] = z;
    }

    void set_Up_Left_Leg_Angle(float angle, float x, float y, float z)
    {
        upLeftLegAngle[0] = angle;
        upLeftLegAngle[1] = x;
        upLeftLegAngle[2] = y;
        upLeftLegAngle[3] = z;
    }
    void set_Up_Right_Leg_Angle(float angle, float x, float y, float z)
    {
        upRightLegAngle[0] = angle;
        upRightLegAngle[1] = x;
        upRightLegAngle[2] = y;
        upRightLegAngle[3] = z;
    }

    void set_Down_Right_Leg_Angle(float angle, float x, float y, float z)
    {
        downRightLegAngle[0] = angle;
        downRightLegAngle[1] = x;
        downRightLegAngle[2] = y;
        downRightLegAngle[3] = z;
    }
    void set_Down_Left_Leg_Angle(float angle, float x, float y, float z)
    {
        downLeftLegAngle[0] = angle;
        downLeftLegAngle[1] = x;
        downLeftLegAngle[2] = y;
        downLeftLegAngle[3] = z;
    }

    void set_Up_Right_Hand_Angle(float angles[4])
    {
        upRightHandAngle[0] = angles[0];
        upRightHandAngle[1] = angles[1];
        upRightHandAngle[2] = angles[2];
        upRightHandAngle[3] = angles[3];
    }
    void set_Up_Left_Hand_Angle(float angles[4])
    {
        upLeftHandAngle[0] = angles[0];
        upLeftHandAngle[1] = angles[1];
        upLeftHandAngle[2] = angles[2];
        upLeftHandAngle[3] = angles[3];
    }

    void set_Down_Right_Hand_Angle(float angles[4])
    {
        downRightHandAngle[0] = angles[0];
        downRightHandAngle[1] = angles[1];
        downRightHandAngle[2] = angles[2];
        downRightHandAngle[3] = angles[3];
    }

    void set_Down_Left_Hand_Angle(float angles[4])
    {
        downLeftHandAngle[0] = angles[0];
        downLeftHandAngle[1] = angles[1];
        downLeftHandAngle[2] = angles[2];
        downLeftHandAngle[3] = angles[3];
    }

    void set_Up_Left_Leg_Angle(float angles[4])
    {
        upLeftLegAngle[0] = angles[0];
        upLeftLegAngle[1] = angles[1];
        upLeftLegAngle[2] = angles[2];
        upLeftLegAngle[3] = angles[3];
    }
    void set_Up_Right_Leg_Angle(float angles[4])
    {
        upRightLegAngle[0] = angles[0];
        upRightLegAngle[1] = angles[1];
        upRightLegAngle[2] = angles[2];
        upRightLegAngle[3] = angles[3];
    }

    void set_Down_Right_Leg_Angle(float angles[4])
    {
        downRightLegAngle[0] = angles[0];
        downRightLegAngle[1] = angles[1];
        downRightLegAngle[2] = angles[2];
        downRightLegAngle[3] = angles[3];
    }
    void set_Down_Left_Leg_Angle(float angles[4])
    {
        downLeftLegAngle[0] = angles[0];
        downLeftLegAngle[1] = angles[1];
        downLeftLegAngle[2] = angles[2];
        downLeftLegAngle[3] = angles[3];
    }
    void setPercentage(float percent){
        setHead(headR*percent, headH*percent);
        setBody(bodyX*percent, bodyY*percent, bodyZ*percent);
        setUpHand(upHandX*percent, upHandY*percent, upHandZ*percent);
        setDownHand(downHandX*percent, downHandY*percent, downHandZ*percent);
        setUpLeg(upLegX*percent, upLegY*percent, upLegZ*percent);
        setDownLeg(downLegX*percent, downLegY*percent, downLegZ*percent);
    }
    float runBackLegAngle[2][4] =
    {
        {30, -1, 0, 0},
        {10, -1, 0, 0}
    };
    float runFrontLegAngle[2][4] =
    {
        {75, 1, 0, 0},
        {90, -1, 0, 0}
    };
    float runBackHandAngle[2][4] =
    {
        {65, 1, 0, 0},
        {60, 1, 0, 0}
    };
    float runFrontHandAngle[2][4] =
    {
        {30, -1, 0, 0},
        {30, 1, 0, 0}
    };
    static Human generalHumanConfig() {
        Human human;
        human.setHead(10, 25);
        human.setBody(30, 25, 70);
        human.setUpHand(10, 10, 35);
        human.setDownHand(10, 10, 30);
        human.setUpLeg(15, 20, 45);
        human.setDownLeg(10, 18, 50);
        human.setPercentage(.4);
        return human;
    }
    static void runningLeftLegConfig(bool isLeft, Human& human) {
        if (isLeft) {
            human.set_Up_Left_Leg_Angle(human.runFrontLegAngle[0]);
            human.set_Down_Left_Leg_Angle(human.runFrontLegAngle[1]);
        } else {
            human.set_Up_Left_Leg_Angle(human.runBackLegAngle[0]);
            human.set_Down_Left_Leg_Angle(human.runBackLegAngle[1]);
        }
    }
    static void runningRightLegConfig(bool isLeft, Human& human) {
        if (isLeft) {
            human.set_Up_Right_Leg_Angle(human.runBackLegAngle[0]);
            human.set_Down_Right_Leg_Angle(human.runBackLegAngle[1]);
        } else {
            human.set_Up_Right_Leg_Angle(human.runFrontLegAngle[0]);
            human.set_Down_Right_Leg_Angle(human.runFrontLegAngle[1]);
        }
    }
    static void runningLeftHandConfig(bool isLeft, Human& human) {
        if (isLeft) {
            human.set_Up_Left_Hand_Angle(human.runBackHandAngle[0]);
            human.set_Down_Left_Hand_Angle(human.runBackHandAngle[1]);
        } else {
            human.set_Up_Left_Hand_Angle(human.runFrontHandAngle[0]);
            human.set_Down_Left_Hand_Angle(human.runFrontHandAngle[1]);
        }
    }
    static void runningRightHandConfig(bool isLeft, Human& human) {
        if (isLeft) {
            human.set_Up_Right_Hand_Angle(human.runFrontHandAngle[0]);
            human.set_Down_Right_Hand_Angle(human.runFrontHandAngle[1]);
        } else {
            human.set_Up_Right_Hand_Angle(human.runBackHandAngle[0]);
            human.set_Down_Right_Hand_Angle(human.runBackHandAngle[1]);
        }
    }

    static Human runningBowler(bool isLeft) {
        Human human = generalHumanConfig();
        human.setHeadAngle(30, 1, 0, 0);
        runningLeftHandConfig(isLeft, human);
        runningRightHandConfig(isLeft, human);

        runningLeftLegConfig(isLeft, human);
        runningRightLegConfig(isLeft, human);
        return human;
    }
    static Human bowlingBowler(int state , bool &startBall , int rightFront) {
        Human human = generalHumanConfig();
        float headAngle = 10 * state;
        float RightHandAngle = 90 + 35 * (state - 1);
        human.setHeadAngle(headAngle, 0, 1, 0);
        //cout<<"angle " <<RightHandAngle<<"\n";
        if (RightHandAngle < 180) {
            human.set_Up_Right_Hand_Angle(RightHandAngle, -1, 0, 0);
        } else if (RightHandAngle < 270 && RightHandAngle > 180) {
            human.set_Up_Right_Hand_Angle(RightHandAngle, -1, 1, 0);
            startBall = 1;
        } else {
            human.set_Up_Right_Hand_Angle(RightHandAngle, -1, 0, 0);
        }
        // human.set_Up_Right_Hand_Angle(RightHandAngle, -1, 0, 0);
        //runningHandConfig(rightFront^1 , human);
        if (state < 5) {
            if (state % 2) {
                runningLeftLegConfig(!rightFront, human);
                runningRightLegConfig(!rightFront, human);
                runningLeftHandConfig(rightFront, human);
            } else {
                runningLeftLegConfig(rightFront, human);
                runningRightLegConfig(rightFront, human);
                runningLeftHandConfig(!rightFront, human);
            }
        } else {
            if (state % 2) {
                runningLeftLegConfig(rightFront, human);
                runningRightLegConfig(rightFront, human);
                runningLeftHandConfig(!rightFront, human);
            } else {
                runningLeftLegConfig(!rightFront, human);
                runningRightLegConfig(!rightFront, human);
                runningLeftHandConfig(rightFront, human);
            }
        }
        //human.set_Up_Left_Hand_Angle(RightHandAngle , 1, 0 , 0);
        return human;
    }

    static void offCutLeftHandConfig(Human& human , float handAngle) {
        human.set_Up_Left_Hand_Angle(handAngle + 20, 1, 0, -1);
        human.set_Down_Left_Hand_Angle(45, 0, 1, 1);
    }

    static void offCutRightHandConfig(Human& human , float handAngle) {
        human.set_Up_Right_Hand_Angle(handAngle + 20, 1, 0, -1);
        human.set_Down_Right_Hand_Angle(30, 0, -1, 1);
    }

    static void onCutLeftHandConfig(Human& human, float handAngle) {
        human.set_Up_Left_Hand_Angle(handAngle + 20, 1, 0, 1);
        human.set_Down_Left_Hand_Angle(45, 0, 1, 1);
    }

    static void onCutRightHandConfig(Human& human, float handAngle) {
        human.set_Up_Right_Hand_Angle(handAngle + 20, 1, 0, 1);
        human.set_Down_Right_Hand_Angle(30, 0, -1, 0);
    }

    static void straightCutLeftHandConfig(Human& human , float handAngle) {
        human.set_Up_Left_Hand_Angle(handAngle + 20, 1, 1, 0);
        human.set_Down_Left_Hand_Angle(45, -1, 1, 0);
    }

    static void straightCutRightHandConfig(Human& human, float handAngle) {
        human.set_Up_Right_Hand_Angle(handAngle + 20, 1, 1, 0);
        human.set_Down_Right_Hand_Angle(30, 0, -1, 0);
    }

    static void humanBatsmanLeftConfig(Human& human, float handAngle) {
        human.set_Up_Left_Hand_Angle(handAngle + 20, 1, 0, 0);
        human.set_Down_Left_Hand_Angle(45, 0, 1, 0);
    }

    static void humanBatsmanRightConfig(Human& human, float handAngle) {
        human.set_Up_Right_Hand_Angle(handAngle + 20, 1, 0, 0);
        human.set_Down_Right_Hand_Angle(30, 0, -1, 0);
    }
};

#endif  // HUMAN_H
