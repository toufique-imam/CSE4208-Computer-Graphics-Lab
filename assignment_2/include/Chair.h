#ifndef CHAIR_H
#define CHAIR_H
#include "Cube.h"

class Chair {
    int chairBigLegLen, chairSmallLegLen, seatY, seatX;
   public:
    Chair();
    Chair(int bl, int sl, int sx, int sy) {
        chairBigLegLen = bl;
        chairSmallLegLen = sl;
        seatX = sx;
        seatY = sy;
    }
    void drawChair();

   protected:
   private:
};

#endif  // CHAIR_H
