#include<stdio.h>

#include "model.h"
#include "utility.h"
#include "shape.h"

extern GLfloat cameraZ;
extern FILE *gpFile;
extern point_t point_vertices[100];

void drawScene1()
{

    // Drawing stars
    glPushMatrix();
        glLoadIdentity();
        drawPoints(point_vertices, 800);
    glPopMatrix();

    // Drawing moon
    glPushMatrix();
        glTranslatef(4.0f, 2.5f, -2.0f);
        drawMoon();
    glPopMatrix();
}