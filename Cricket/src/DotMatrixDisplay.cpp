#include "DotMatrixDisplay.h"

DotMatrixDisplay::DotMatrixDisplay() {
    cube.setValue(2, 2, 2);
}

void DotMatrixDisplay::drawChar(char c) {
    int index = c - ' ';
    if(index<0 || index>94)return;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            if (font_5x7[index][i] & (1 << j)) {
                matrix[6-j][4-i] = 1;
            } else {
                matrix[6-j][4-i] = 0;
            }
        }
    }
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j]) {
                glPushMatrix();
                {
                    glTranslatef(j * 2, 0, i * -2);
                    cube.drawCube();
                }
                glPopMatrix();
            }
        }
    }
}
