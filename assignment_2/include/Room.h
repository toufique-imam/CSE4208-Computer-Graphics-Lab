#ifndef ROOM_H
#define ROOM_H
#include "Cube.h"

class Room {
    float a, b, c;
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

   protected:
   private:
    void assignColors(int i, int color[]);
};

#endif  // ROOM_H
