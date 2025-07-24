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
        //glTranslatef(5.0f, 4.5f, -6.0f);
        //glRotatef(-110.0f, 0.0f, 1.0f, 0.0f);
        //glRotatef(-180.0f, 0.0f, 0.0f, 1.0f);
        drawMoon();
    glPopMatrix();
}