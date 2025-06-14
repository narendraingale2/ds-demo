#include<stdio.h>

#include "model.h"
#include "utility.h"
#include "shape.h"

extern GLfloat cameraZ;
extern FILE *gpFile;
extern point_t point_vertices[100];

void drawScene1()
{

    gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(4.0f, 2.5f, -2.0f);
    drawMoon();
    glLoadIdentity();
    drawPoints(point_vertices, 800);
}