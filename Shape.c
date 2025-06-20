#include "shape.h"
#include "POINTS.h"


void drawPoints(point_t points[], int length) {
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    for (int i = 0; i < length; ++i) {
        glPointSize(points[i].size);
        //glBegin(GL_POINTS);
        glLoadIdentity();
        glTranslatef(points[i].x, points[i].y, points[i].z);
        glColor3f(points[i].c.red, points[i].c.red, points[i].c.red);
        gluSphere(quadric, 0.005f, 30, 30);
        //glVertex3f(points[i].x, points[i].y, points[i].z);
        //glEnd();
        
    }
}