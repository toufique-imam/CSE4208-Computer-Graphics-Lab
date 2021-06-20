#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"
#include "Cube.h"
using namespace std;

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
const static int ID_FLAG = 12;

static char* textureFileName[20];

static unsigned int IDS[20];

static void loadTexture(const char* filename, int index) {
    BmpLoader bl(filename);

    glGenTextures(1, &IDS[index]);

    glBindTexture(GL_TEXTURE_2D, IDS[index]);
    //cout<<index << " " <<IDS[index]<<"\n";
    glPixelStoref(GL_UNPACK_ALIGNMENT, IDS[index]);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE );

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData);
}

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
    textureFileName[ID_FLAG] = "E:\\study\\other\\Graphics-lab\\Cricket\\bmp-images\\flag.bmp";

}
static void setNormal(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3) {
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1;
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1;
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz;
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(Nx, Ny, Nz);
}

#endif  // TEXTURELOADER_H
