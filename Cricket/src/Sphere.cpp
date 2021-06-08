#include "Sphere.h"

Sphere::Sphere(double x, int y, int z)
{
    r = x;
    lats = y;
    longs = z;
}

void Sphere::setLight()
{
    GLfloat mat_shininess[] = {dummy.shines[0]};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, dummy.surfaceLights[0][0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dummy.surfaceLights[1][0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, dummy.surfaceLights[2][0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

}
void Sphere::drawSphere()
{
    const float PI = 3.141592f;
    GLfloat x, y, z, alpha, beta; // Storage for coordinates and angles
    GLfloat radius = 60.0f;
    int gradation = 20;

    for (alpha = 0.0; alpha < PI; alpha += PI/gradation)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (beta = 0.0; beta < 2.01*PI; beta += PI/gradation)
        {
            x = radius*cos(beta)*sin(alpha);
            y = radius*sin(beta)*sin(alpha);
            z = radius*cos(alpha);
            glVertex3f(x, y, z);
            x = radius*cos(beta)*sin(alpha + PI/gradation);
            y = radius*sin(beta)*sin(alpha + PI/gradation);
            z = radius*cos(alpha + PI/gradation);
            glVertex3f(x, y, z);
        }
        glEnd();
    }
}
