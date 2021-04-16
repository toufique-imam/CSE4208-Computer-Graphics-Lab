#ifndef DRAWER_H
#define DRAWER_H
#include "Cube.h"

class Drawer {
    int sizex, sizey, sizez;

   public:
    Drawer() {}
    Drawer(int x, int y, int z) {
        sizex = x;
        sizey = y;
        sizez = z;
    }
    void drawDrawer();

   protected:
   private:
};

#endif  // DRAWER_H
