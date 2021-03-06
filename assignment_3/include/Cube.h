#ifndef CUBE_H
#define CUBE_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

class Cube
{
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
        {0, 1, 5, 4}
    };

    float surfaceLights[3][6][4];
    float surfaceColors[6][4];
    int shines[6];
    int filter[6];

public:
    Cube();
    Cube(int a, int b, int c);
    Cube(float a, float b, float c);

    void setValue(int a, int b, int c);
    void setValue(float a, float b, float c);

    vector<vector<float> > generate_cube(float a, float b, float c);

    void drawSurface(int points[], bool randomColor = true, int surfaceIdx = -1, bool printLines = true);
    void drawCube(bool randomColor = true, bool printLines = true);

    void setSurfaceLightADS(int pos , int colors[] , int intensity);
    void setSurfaceLightADS(int pos , int colors[][3] , int intensity);

    void setSurfaceLights(int colors[][3], int intensityAmbient=20, int intensityDeffuse=80, int intensitySpecular=30){
        setSurfaceLightADS(0 , colors, intensityAmbient);
        setSurfaceLightADS(1 , colors, intensityDeffuse);
        setSurfaceLightADS(2, colors, intensitySpecular);
    }

    void setSurfaceLights(int colors[], int intensityAmbient = 20, int intensityDeffuse = 80, int intensitySpecular = 30) {
        setSurfaceLightADS(0, colors, intensityAmbient);
        setSurfaceLightADS(1, colors, intensityDeffuse);
        setSurfaceLightADS(2, colors, intensitySpecular);
    }

    void setSurfaceShine(int shine){
        for(int i=0;i<6;i++){
            shines[i] = shine;
        }
    }

    void setSurfaceShine(int shine[]) {
        for (int i = 0; i < 6; i++) {
            shines[i] = shine[i];
        }
    }

    void setfilterSurface(int f[]);

    void genRandomColor(int i)
    {
        if(i==0)setSurfaceLights(green);
        else if(i==1)setSurfaceLights(darkyellow);
        else if(i==2)setSurfaceLights(black);
        else if(i==3)setSurfaceLights(offYellow);
        else if(i==4)setSurfaceLights(offwhite1);
        else if(i==5)setSurfaceLights(skyblue);
        else if(i==6)setSurfaceLights(offwhite2);
        else if(i==7)setSurfaceLights(blueash);
        else if(i==9)setSurfaceLights(blue);
        else if(i==8)setSurfaceLights(white);
        else setSurfaceLights(offYellow);

    }
    //defaultLightPercentage
    int light_percentage_20_60_100[3] = {20 , 60 , 100};

    //colors
    int green[3] = {50, 168, 82};
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
    int white[3] = {255, 255, 255};


protected:
private:
};

#endif  // CUBE_H

