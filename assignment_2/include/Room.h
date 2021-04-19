#ifndef ROOM_H
#define ROOM_H
#include "Cube.h"
#include "Window.h"
#include "Cylinder.h"

class Room {
    float a, b, c;
    int angle = 0 ;
    int colors[6][3];
    float tileSize;

   public:
    Room();
    Room(int a, int b, int c, int tileSize);
    Room(float a, float b, float c, float tileSize);
    void drawRoom();
    void genColor();
    void drawTileLines();
    void drawDoor();
    void drawWallLeft();
    void drawWallRight();
    void drawFan();
    void drawLight();
    void drawClock();
    void updateAngles(int val){
        angle = (angle+val);
        angle%=360;
    }

   protected:
   private:
    void assignColors(int i, int color[]);
};

#endif  // ROOM_H
