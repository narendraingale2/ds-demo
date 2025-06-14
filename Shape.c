#include "shape.h"
#include "POINTS.h"

void drawPoints(point_t points[], int length) {
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < length; ++i) {
        glLoadIdentity();
        glTranslatef(points[i].x, points[i].y, points[i].z);
        glColor3f(points[i].c.red, points[i].c.red, points[i].c.red);
        gluSphere(quadric, 0.005f, 30, 30);
        
    }
    glEnd();
}