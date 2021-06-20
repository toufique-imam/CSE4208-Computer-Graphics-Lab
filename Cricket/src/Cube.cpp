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
    v[0] = 0, v[1] = 0, v[2] = c;
    ans.push_back(v);
    //4
    v[0] = a, v[1] = 0, v[2] = c;
    ans.push_back(v);

    //5
    v[0] = 0, v[1] = b, v[2] = 0;
    ans.push_back(v);
    //6
    v[0] = a, v[1] = b, v[2] = 0;
    ans.push_back(v);
    //7
    v[0] = 0, v[1] = b, v[2] = c;
    ans.push_back(v);
    //8
    v[0] = a, v[1] = b, v[2] = c;
    ans.push_back(v);

    return ans;
}

void Cube::drawSurface(int points[], int surfaceIdx) {
    GLfloat mat_shininess[] = {shines[surfaceIdx]};
    glPushMatrix();
    glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, surfaceLights[0][surfaceIdx]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, surfaceLights[1][surfaceIdx]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, surfaceLights[2][surfaceIdx]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

    setNormal(
        cube_vers[points[0]][0], cube_vers[points[0]][1], cube_vers[points[0]][2],
        cube_vers[points[1]][0], cube_vers[points[1]][1], cube_vers[points[1]][2],
        cube_vers[points[2]][0], cube_vers[points[2]][1], cube_vers[points[2]][2]);
    for (int i = 0; i < 4; i++) {
        glVertex3f(cube_vers[points[i]][0], cube_vers[points[i]][1], cube_vers[points[i]][2]);
        glTexCoord2f(cords[i][0]*repeat*1.0f, cords[i][1]*repeat*1.0f);
    }
    glEnd();
    glPopMatrix();
}
void Cube::drawCube() {
    setSurfaceShine(60);
    cube_vers = generate_cube(a, b, c);

    for (int i = 0; i < 6; i++) {
        if (filter[i] == 0)
            drawSurface(surfaces[i], i);
    }
}

void Cube::setSurfaceLightADS(int pos, int colors[], int intensity) {
    for (int i = 0; i < 6; i++) {
        surfaceColors[i][0] = (colors[0] * 1.0f) / 255.0;
        surfaceColors[i][1] = (colors[1] * 1.0f) / 255.0;
        surfaceColors[i][2] = (colors[2] * 1.0f) / 255.0;
        surfaceColors[i][3] = 1;
    }
    for (int i = 0; i < 6; i++) {
        surfaceLights[pos][i][0] = (colors[0] * 1.0f * intensity) / (255.0 * 100.0);
        surfaceLights[pos][i][1] = (colors[1] * 1.0f * intensity) / (255.0 * 100.0);
        surfaceLights[pos][i][2] = (colors[2] * 1.0f * intensity) / (255.0 * 100.0);
        surfaceLights[pos][i][3] = 1;
    }
}
void Cube::setSurfaceLightADS(int pos, int colors[][3], int intensity) {
    for (int i = 0; i < 6; i++) {
        surfaceColors[i][0] = (colors[i][0] * 1.0f) / 255.0;
        surfaceColors[i][1] = (colors[i][1] * 1.0f) / 255.0;
        surfaceColors[i][2] = (colors[i][2] * 1.0f) / 255.0;
        surfaceColors[i][3] = 1;
    }

    for (int i = 0; i < 6; i++) {
        surfaceLights[pos][i][0] = (colors[i][0] * 1.0f * intensity) / (255.0 * 100.0);
        surfaceLights[pos][i][1] = (colors[i][1] * 1.0f * intensity) / (255.0 * 100.0);
        surfaceLights[pos][i][2] = (colors[i][2] * 1.0f * intensity) / (255.0 * 100.0);
        surfaceLights[pos][i][3] = 1;
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
