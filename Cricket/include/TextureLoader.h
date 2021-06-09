#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<bits/stdc++.h>
using namespace std;
#include "BmpLoader.h"

const static int ID_BALL = 1;
const static int ID_GRASS = 2;
const static int ID_GRIP = 3;
const static int ID_PITCH = 4;
const static int ID_WOOD = 5;
const static int ID_BANNER1 = 6;
const static int ID_BANNER2 = 7;
const static int ID_BANNER3 = 8;
const static int ID_FLOOD_LIGHT = 9;
const static int ID_METAL = 10;
const static int ID_SCORE_BOARD = 11;

static char* textureFileName[20];

static unsigned int IDS[20];

static void loadTexture(const char* filename, int index) {
    BmpLoader bl(filename);

    glGenTextures(1, &IDS[index]);

    glBindTexture(GL_TEXTURE_2D, IDS[index]);
    //cout<<index << " " <<IDS[index]<<"\n";
    glPixelStorei(GL_UNPACK_ALIGNMENT, IDS[index]);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE );

    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData);
}
/*
void LoadTexture(const char*filename) {
    glGenTextures(1, &texID[texIdx]);
    glBindTexture(GL_TEXTURE_2D, texID[texIdx]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, texID[texIdx++]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

*/

static void initTexture() {
    for (int i = 0; i < 20; i++)
        IDS[i] = i;

    textureFileName[ID_BALL] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\ball.bmp";
    textureFileName[ID_GRASS] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\grass_pattern.bmp";
    textureFileName[ID_GRIP] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\grip.bmp";
    textureFileName[ID_PITCH] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\pitch.bmp";
    textureFileName[ID_WOOD] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\wood.bmp";
    textureFileName[ID_BANNER1] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\banner_1.bmp";
    textureFileName[ID_BANNER2] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\banner_2_lg.bmp";
    textureFileName[ID_BANNER3] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\banner_3.bmp";
    textureFileName[ID_FLOOD_LIGHT] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\floodlight.bmp";
    textureFileName[ID_METAL] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\metal_texture.bmp";
    textureFileName[ID_SCORE_BOARD] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\scoreboard.bmp";

}
#endif  // TEXTURELOADER_H
