#include<stdio.h>

#include "model.h"
#include "utility.h"
#include "shape.h"

extern GLfloat cameraZ;
extern FILE *gpFile;

void drawScene1()
{

    fprintf(gpFile, "cameraZ = %f \n", cameraZ);
    gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(4.0f, 2.5f, 0.0f);
    drawMoon();
    glLoadIdentity();
    drawRandomPoints(10);
}