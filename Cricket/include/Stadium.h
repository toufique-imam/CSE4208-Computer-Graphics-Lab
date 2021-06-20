#ifndef STADIUM_H
#define STADIUM_H
#include "Cube.h"

class Stadium {
    int partitions;
    int color[3];
  public:
    Stadium() {
        partitions = 6;
    }
    Stadium(int x) {
        partitions = x;
    }
    void setColor(int r, int g, int b) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }
    void drawStadium() {
        Cube c;
        c.setColor(color[0], color[1], color[2]);
        for(int i=1; i<=partitions; i++) {
            glPushMatrix();
            {
                glTranslatef(-i , 0 , 0);
                c.setValue(1, 1, i);
                c.drawCube();
            }
            glPopMatrix();
        }
    }
};

#endif // STADIUM_H
