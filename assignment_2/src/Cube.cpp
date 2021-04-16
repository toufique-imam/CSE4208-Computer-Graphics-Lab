#include "Cube.h"
#define debug(x) cerr << #x << " " << x << "\n";

Cube::Cube() {
    this->a = this->b = this->c = 1;
    //ctor
    /*
    cube c = cube(5, 5, 5);
    c.drawCube();
    */
}

Cube::Cube(int a, int b, int c) {
    this->a = a;
    this->b = b;
    this->c = c;

    memset(filter, 0, sizeof filter);
}

Cube::Cube(float a, float b, float c) {
    this->a = a;
    this->b = b;
    this->c = c;

    memset(filter, 0, sizeof filter);
}

vector<vector<float> > Cube::generate_cube(float a, float b, float c) {
    vector<vector<float> > ans;
    vector<float> v(3, 0);
    ans.push_back(v);
    //2
    v[0] = a, v[1] = 0, v[2] = 0;
    ans.push_back(v);
    //3
    v[0] = a, v[1] = 0, v[2] = c;
    ans.push_back(v);
    //4
    v[0] = 0, v[1] = 0, v[2] = c;
    ans.push_back(v);
    //5
    v[0] = 0, v[1] = b, v[2] = 0;
    ans.push_back(v);
    //6
    v[0] = a, v[1] = b, v[2] = 0;
    ans.push_back(v);
    //7
    v[0] = a, v[1] = b, v[2] = c;
    ans.push_back(v);
    //8
    v[0] = 0, v[1] = b, v[2] = c;
    ans.push_back(v);

    return ans;
}

void Cube::drawSurface(int points[], bool randomColor, int surfaceIdx) {
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++) {
        if (randomColor)
            glColor3f(cube_colors[points[i]][0], cube_colors[points[i]][1], cube_colors[points[i]][2]);
        else
            glColor3f(surfaceColors[surfaceIdx][0], surfaceColors[surfaceIdx][1], surfaceColors[surfaceIdx][2]);

        glVertex3f(cube_vers[points[i]][0], cube_vers[points[i]][1], cube_vers[points[i]][2]);
    }
    glEnd();

    glBegin(GL_LINES);
    for (int i = 0; i < 4; i++) {
        glColor3f(0, 0, 0);
        glVertex3f(cube_vers[points[i]][0], cube_vers[points[i]][1], cube_vers[points[i]][2]);
    }
    glEnd();
}
void Cube::drawCube(bool randomColor) {
    cube_vers = generate_cube(a, b, c);
    cube_colors = generate_cube(200, 200, 200);
    for (int i = 0; i < 6; i++) {
        if (filter[i] == 0)
            drawSurface(surfaces[i], randomColor, i);
    }
}

void Cube::setSurfaceColors(int colors[][3]) {
    for (int i = 0; i < 6; i++) {
        surfaceColors[i][0] = (1.0f * colors[i][0]) / 255.0;
        surfaceColors[i][1] = (1.0f * colors[i][1]) / 255.0;
        surfaceColors[i][2] = (1.0f * colors[i][2]) / 255.0;
    }
}

void Cube::setSurfaceColors(int colors[]) {
    for (int i = 0; i < 6; i++) {
        surfaceColors[i][0] = (colors[0] * 1.0f) / 255.0;
        surfaceColors[i][1] = (colors[1] * 1.0f) / 255.0;
        surfaceColors[i][2] = (colors[2] * 1.0f) / 255.0;
    }
}

/*
(1.0f/255)*byte_in;
*/

void Cube::setValue(int a, int b, int c) {
    this->a = a;
    this->b = b;
    this->c = c;
    memset(filter, 0, sizeof filter);
}
void Cube::setValue(float a, float b, float c) {
    this->a = a;
    this->b = b;
    this->c = c;
    memset(filter, 0, sizeof filter);
}

void Cube::setfilterSurface(int f[]) {
    for (int i = 0; i < 6; i++) {
        filter[i] = f[i];
    }
}
