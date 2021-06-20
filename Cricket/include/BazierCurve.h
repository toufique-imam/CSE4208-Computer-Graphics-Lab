#ifndef BAZIERCURVE_H
#define BAZIERCURVE_H
#define PI acos(-1)
#include "Cube.h"

class BazierCurve {
  public:
    int wired = 0;
    int shcpt = 1;
    const int L_BELL = 29;
    const int L_FLAG = 4;
    const int nt = 40;  //number of slices along x-direction
    const int ntheta = 20;

    GLfloat ctrlpointsBell[30][3] = {
        {-3.60, 0.52, 0.00},
        {-4.00, 0.20, 0.00},
        {-3.40, 0.50, 0.00},
        {-3.00, 0.50, 0.00},
        {-2.60, 0.50, 0.00},
        {-2.20, 1.00, 0.00},
        {-1.80, 1.00, 0.00},
        {-1.40, 1.00, 0.00},
        {-1.00, 1.00, 0.00},
        {-0.60, 1.40, 0.00},
        {-0.20, 1.40, 0.00},
        {0.20, 1.40, 0.00},
        {0.60, 1.50, 0.00},
        {1.00, 0.00, 0.00},
        {1.40, 0.00, 0.00},
        {1.80, 0.00, 0.00},
        {2.20, 0.00, 0.00},
        {2.60, 1.50, 0.00},
        {3.00, 1.40, 0.00},
        {3.40, 1.40, 0.00},
        {3.80, 1.40, 0.00},
        {4.20, 1.00, 0.00},
        {4.60, 1.00, 0.00},
        {5.00, 1.00, 0.00},
        {5.40, 1.00, 0.00},
        {5.80, 0.50, 0.00},
        {6.20, 0.50, 0.00},
        {6.60, 0.50, 0.00},
        {7.20, 0.20, 0.00},
        {6.80, 0.52, 0.00}
    };

    GLfloat ctrlPointsFlag[5][3] = {{1, 4, 0}, {1.5, 4.5, 0}, {2.5, 3.5, 0}, {3, 4, 0}};

    BazierCurve();
    //control points
    long long nCr(int n, int r) {
        if (r > n / 2)
            r = n - r;  // because C(n, r) == C(n, n - r)
        long long ans = 1;
        int i;

        for (i = 1; i <= r; i++) {
            ans *= n - r + i;
            ans /= i;
        }

        return ans;
    }
    void BezierCurveBell(double t, float xy[2]) {
        double y = 0;
        double x = 0;
        t = t > 1.0 ? 1.0 : t;
        for (int i = 0; i <= L_BELL; i++) {
            int ncr = nCr(L_BELL, i);
            double oneMinusTpow = pow(1 - t, double(L_BELL - i));
            double tPow = pow(t, double(i));
            double coef = oneMinusTpow * tPow * ncr;
            x += coef * ctrlpointsBell[i][0];
            y += coef * ctrlpointsBell[i][1];
        }
        xy[0] = float(x);
        xy[1] = float(y);

        //return y;
    }
    void BezierCurveFlag(double t, float xy[2]) {
        double y = 0;
        double x = 0;
        t = t > 1.0 ? 1.0 : t;
        for (int i = 0; i <= L_FLAG; i++) {
            int ncr = nCr(L_FLAG, i);
            double oneMinusTpow = pow(1 - t, double(L_FLAG - i));
            double tPow = pow(t, double(i));
            double coef = oneMinusTpow * tPow * ncr;
            x += coef * ctrlPointsFlag[i][0];
            y += coef * ctrlPointsFlag[i][1];
        }
        xy[0] = float(x);
        xy[1] = float(y);

        //return y;
    }

    void bellBezier() {
        int i, j;
        float x, y, z, r;      //current coordinates
        float x1, y1, z1, r1;  //next coordinates
        float theta;

        const float startx = 0, endx = ctrlpointsBell[L_BELL][0];
        //number of angular slices
        const float dx = (endx - startx) / nt;  //x step size
        const float dtheta = 2 * PI / ntheta;   //angular step size

        float t = 0;
        float dt = 1.0 / nt;
        float xy[2];
        BezierCurveBell(t, xy);
        x = xy[0];
        r = xy[1];
        //rotate about z-axis
        float p1x, p1y, p1z, p2x, p2y, p2z;
        for (i = 0; i < nt; ++i) {  //step through x
            theta = 0;
            t += dt;
            BezierCurveBell(t, xy);
            x1 = xy[0];
            r1 = xy[1];

            //draw the surface composed of quadrilaterals by sweeping theta
            glBegin(GL_QUAD_STRIP);
            for (j = 0; j <= ntheta; ++j) {
                theta += dtheta;
                double cosa = cos(theta);
                double sina = sin(theta);
                y = r * cosa;
                y1 = r1 * cosa;  //current and next y
                z = r * sina;
                z1 = r1 * sina;  //current and next z

                //edge from point at x to point at next x
                glVertex3f(x, y, z);

                if (j > 0) {
                    setNormal(p1x, p1y, p1z, p2x, p2y, p2z, x, y, z);
                } else {
                    p1x = x;
                    p1y = y;
                    p1z = z;
                    p2x = x1;
                    p2y = y1;
                    p2z = z1;
                }
                glVertex3f(x1, y1, z1);

                //forms quad with next pair of points with incremented theta value
            }
            glEnd();
            x = x1;
            r = r1;
        }  //for i
    }
    void showControlPointsBell() {
        glPointSize(5.0);
        glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        for (int i = 0; i <= L_BELL; i++)
            glVertex3fv(&ctrlpointsBell[i][0]);
        glEnd();
    }
    void showControlPointsFlag() {
        glPointSize(5.0);
        glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        for (int i = 0; i <= L_FLAG; i++)
            glVertex3fv(&ctrlPointsFlag[i][0]);
        glEnd();
    }
    void drawBell() {
        glPushMatrix();
        if (shcpt) {
            Cube c;
            c.setSurfaceLights(c.green);
            glPushMatrix();
            {
                setMatLight(c);
                showControlPointsBell();
            }
            glPopMatrix();
        }

        if (wired) {
            glPolygonMode(GL_FRONT, GL_LINE);
            glPolygonMode(GL_BACK, GL_LINE);

        } else {
            glPolygonMode(GL_FRONT, GL_FILL);
            glPolygonMode(GL_BACK, GL_FILL);
        }
        bellBezier();
        glPopMatrix();
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
    }

    void computeBezierPoints(float t, float& x, float& y, float& z) {
        int i, n = L_FLAG - 1;

        float bernstein_polynomial;

        x = 0;
        y = 0;
        z = 0;

        for (i = 0; i < L_FLAG; i++) {
            bernstein_polynomial = nCr(L_FLAG, i) * pow(t, i) * pow(1 - t, n - i);

            x += bernstein_polynomial * ctrlPointsFlag[i][0];
            y += bernstein_polynomial * ctrlPointsFlag[i][1];
            z += bernstein_polynomial * ctrlPointsFlag[i][2];
        }
    }

    void flagBezier() {
        float t;
        float ax, ay, az;
        int number_of_bezier_points = 20;
        glBegin(GL_LINE_STRIP);
        {
            for (int i = 0; i <= 20; i++) {
                t = float(i) / float(number_of_bezier_points);
                computeBezierPoints(t, ax, ay, az);
                glVertex3f(ax, ay, az);
            }
        }
        glEnd();
    }
    void DrawCircle(float r, int num_segments) {
        float x = 0, y = 0;
        glBegin(GL_TRIANGLE_FAN);  //BEGIN CIRCLE
        glVertex3f(x, y, 0);           // center of circle
        for (int i = 0; i <= num_segments; i++) {
            glVertex3f( (x + (r * cos(i * 2 * PI / 20))),  (y + (r * sin(i * 2 * PI / 20))), 0);
        }
        glEnd();  //END
    }
    void drawFlag(float theta) {
        Cube c;
        ctrlPointsFlag[1][0] += 50 * sin(theta * PI / 180.0);
        ctrlPointsFlag[1][1] += 25 * sin(theta * PI / 180.0);

        ctrlPointsFlag[2][0] -= 50 * sin((theta + 30) * PI / 180.0);
        ctrlPointsFlag[2][1] -= 50 * sin((theta + 30) * PI / 180.0);

        ctrlPointsFlag[3][0] -= 25 * sin((theta - 30) * PI / 180.0);
        ctrlPointsFlag[3][1] += sin((theta - 30) * PI / 180.0);

        glPushMatrix();
        {
            c.setColor(0, 255, 0);
            setMatLight(c);
            glPointSize(5);
            //glColor3f(0, 1, 0);
            for (int i = 0; i < 50; i++) {
                glTranslatef(0, -0.8, 0);

                flagBezier();
            }
        }
        glPopMatrix();
    }
};

#endif  // BAZIERCURVE_H
