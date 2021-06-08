#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "BmpLoader.h"

const static int ID_BALL = 1;
const static int ID_GRASS = 2;
const static int ID_GRIP = 3;
const static int ID_PITCH = 4;
const static int ID_PLAYER_HEAD_1 = 5;
const static int ID_PLAYER_HEAD_2 = 6;
const static int ID_WHITE_CLOTH = 7;
const static int ID_WOOD = 8;
const static int ID_BANNER1 = 9;
const static int ID_BANNER2 = 10;
const static int ID_FLOOD_LIGHT = 11;
const static int ID_METAL = 12;

static char* textureFileName[20];

static unsigned int IDS[20];

static void loadTexture(const char* filename, int index) {
    BmpLoader bl(filename);

    glBindTexture(GL_TEXTURE_2D, IDS[index]);

    glPixelStorei(GL_UNPACK_ALIGNMENT, IDS[index]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData);
}

static void initTexture() {
    for (int i = 0; i < 20; i++)
        IDS[i] = i;

    textureFileName[1] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\ball.bmp";
    textureFileName[2] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\grass_pattern.bmp";
    textureFileName[3] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\grip.bmp";
    textureFileName[4] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\pitch.bmp";
    textureFileName[5] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\player_head_1.bmp";
    textureFileName[6] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\player_head_2.bmp";
    textureFileName[7] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\white_cloth.bmp";
    textureFileName[8] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\wood.bmp";
    textureFileName[9] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\banner_1.bmp";
    textureFileName[10] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\banner_2.bmp";
    textureFileName[11] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\floodlight.bmp";
    textureFileName[12] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\metal_texture.bmp";
}

#endif  // TEXTURELOADER_H
