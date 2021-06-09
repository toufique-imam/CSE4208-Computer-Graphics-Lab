#include "SevenSegmentDisplay.h"

SevenSegmentDisplay::SevenSegmentDisplay() {
    hasTexture = 0;

    segments[0].setValue(8, 2, 2);
    segments[1].setValue(2, 2, 10);

    for (int i = 0; i < 10; i++)
        typeOfIndex[i] = 1;
    typeOfIndex[0] = 0;
    typeOfIndex[3] = 0;
    typeOfIndex[6] = 0;

    positionIndex[0][0] = 0;
    positionIndex[0][1] = 0;
    positionIndex[0][2] = 20;

    positionIndex[1][0] = 0;
    positionIndex[1][1] = 0;
    positionIndex[1][2] = 12;

    positionIndex[2][0] = 0;
    positionIndex[2][1] = 0;
    positionIndex[2][2] = 2;

    positionIndex[3][0] = 0;
    positionIndex[3][1] = 0;
    positionIndex[3][2] = 0;

    positionIndex[4][0] = 6;
    positionIndex[4][1] = 0;
    positionIndex[4][2] = 2;

    positionIndex[5][0] = 6;
    positionIndex[5][1] = 0;
    positionIndex[5][2] = 12;

    positionIndex[6][0] = 0;
    positionIndex[6][1] = 0;
    positionIndex[6][2] = 10;

    {
        charMap['0'] = 0x7E;
        charMap['1'] = 0x30;
        charMap['2'] = 0x6D;
        charMap['3'] = 0x79;
        charMap['4'] = 0x33;
        charMap['5'] = 0x5B;
        charMap['6'] = 0x5F;
        charMap['7'] = 0x70;
        charMap['8'] = 0x7F;
        charMap['9'] = 0x7B;
        charMap[' '] = 0x00;
        charMap['A'] = 0x77;
        charMap['a'] = 0x7D;
        charMap['B'] = 0x7F;
        charMap['b'] = 0x1F;
        charMap['C'] = 0x4E;
        charMap['c'] = 0x0D;
        charMap['D'] = 0x7E;
        charMap['d'] = 0x3D;
        charMap['E'] = 0x4F;
        charMap['e'] = 0x6f;
        charMap['F'] = 0x47;
        charMap['f'] = 0x47;
        charMap['G'] = 0x5E;
        charMap['g'] = 0x7B;
        charMap['H'] = 0x37;
        charMap['h'] = 0x17;
        charMap['I'] = 0x30;
        charMap['i'] = 0x10;
        charMap['J'] = 0x3C;
        charMap['j'] = 0x38;
        charMap['K'] = 0x37;
        charMap['k'] = 0x17;
        charMap['L'] = 0x0E;
        charMap['l'] = 0x06;
        charMap['M'] = 0x55;
        charMap['m'] = 0x55;
        charMap['N'] = 0x15;
        charMap['n'] = 0x15;
        charMap['O'] = 0x7E;
        charMap['o'] = 0x1D;
        charMap['P'] = 0x67;
        charMap['p'] = 0x67;
        charMap['Q'] = 0x73;
        charMap['q'] = 0x73;
        charMap['R'] = 0x77;
        charMap['r'] = 0x05;
        charMap['S'] = 0x5B;
        charMap['s'] = 0x5B;
        charMap['T'] = 0x46;
        charMap['t'] = 0x0F;
        charMap['U'] = 0x3E;
        charMap['u'] = 0x1C;
        charMap['V'] = 0x27;
        charMap['v'] = 0x23;
        charMap['W'] = 0x3F;
        charMap['w'] = 0x2B;
        charMap['X'] = 0x25;
        charMap['x'] = 0x25;
        charMap['Y'] = 0x3B;
        charMap['y'] = 0x33;
        charMap['Z'] = 0x6D;
        charMap['z'] = 0x6D;
    }
}

void SevenSegmentDisplay::drawChar(char c) {
    int now = charMap[c];
    for (int i = 0; i < 7; i++) {
        if (now & (1 << i)) {
            int indexNow = 6-i;
            int typeNow = typeOfIndex[indexNow];
            if (hasTexture) {
                //todo texture code
            }
            glPushMatrix();
            {
                glTranslatef(positionIndex[indexNow][0], positionIndex[indexNow][1], positionIndex[indexNow][2]);
                segments[typeNow].setColor(color[0], color[1], color[2]);
                segments[typeNow].drawCube();
            }
            glPopMatrix();
            if (hasTexture) {
                //todo texture code
            }
        }
    }
}
