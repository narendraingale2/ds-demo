#include<windows.h>

// OpenGl realated header files
#include<gl/GL.h>
#include<gl/GLU.h>

#include"utility.h"

void drawRandomPoints(int count) {
    glPointSize(5.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < count; ++i) {
        float x = getRandomCoord(-10.0f, 10.0f);
        float y = getRandomCoord(-10.0f, 10.0f);
        float z = getRandomCoord(-10.0f, 10.0f);
        glVertex3f(x, y, z);
    }
    glEnd();
}