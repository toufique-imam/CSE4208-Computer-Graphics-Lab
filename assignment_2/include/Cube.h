#ifndef CUBE_H
#define CUBE_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

class Cube {
    float a, b, c;
    vector<vector<float> > cube_vers;
    vector<vector<float> > cube_colors;
    int surfaces[6][4] =
        {
            {0, 3, 2, 1},
            {2, 3, 7, 6},
            {0, 4, 7, 3},
            {1, 2, 6, 5},
            {4, 5, 6, 7},
            {0, 1, 5, 4}};

    float surfaceColors[6][3];

    int filter[6];

   public:
    Cube();
    Cube(int a, int b, int c);
    Cube(float a, float b, float c);

    void setValue(int a, int b, int c);
    void setValue(float a, float b, float c);

    vector<vector<float> > generate_cube(float a, float b, float c);

    void drawSurface(int points[], bool randomColor = true, int surfaceIdx = -1);
    void drawCube(bool randomColor = true);

    void setSurfaceColors(int colors[]);
    void setSurfaceColors(int colors[][3]);
    void setfilterSurface(int f[]);

    //colors
    int browns[3] = {105, 17, 10};
    int darkyellow[3] = {196, 136, 6};
    int black[3] = {0, 0, 0};
    int woodColor[3] = {133, 94, 64};
    int offwhite1[3] = {252, 242, 225};
    int offwhite2[3] = {255, 225, 176};
    int offYellow[3] = {252, 188, 83};
    int skyblue[3] = {3, 213, 255};
    int blue[3] = {29, 122, 222};
    int blueash[3] = {109, 126, 153};

   protected:
   private:
};

#endif  // CUBE_H
