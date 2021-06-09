#ifndef SEVENSEGMENTDISPLAY_H
#define SEVENSEGMENTDISPLAY_H
#include <Cube.h>

class SevenSegmentDisplay {
    Cube segments[2];
    int typeOfIndex[10];
    int positionIndex[10][3];
    int scale;

    int color[3];

    int hasTexture = 0, textureID;

    map<char, int> charMap;

   public:
    int _size_x = 8;
    int _size_y = 2;
    int _size_z = 22;

    SevenSegmentDisplay();
    void drawChar(char c);
    void setColor(int r, int g, int b) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }
    void setTexture(int has, int ID) {
        hasTexture = has;
        textureID = ID;
    }

    void setScale(int x = 1) {
        scale = x;
    }

    void drawMessage(string x) {
        int newLine = 0;
        int paddingX = 0;
        for (int i = x.size() - 1; i > -1; i--) {
            if (x[i] == '\n') {
                newLine++;
                paddingX = 0;
                continue;
            }
            if (x[i] != ' ' && charMap[x[i]] == 0) {
                continue;
            }
            glPushMatrix();
            {
                glTranslatef((_size_x + 2) * paddingX++, 0, newLine * (_size_z + 5));
                glScalef(scale, scale, scale);
                drawChar(x[i]);
            }
            glPopMatrix();
        }
    }
};

#endif  // SEVENSEGMENTDISPLAY_H
