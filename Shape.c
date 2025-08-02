#include<stdio.h>

#include "shape.h"
#include "POINTS.h"
extern FILE *gpFile;
extern GLfloat location[16];
GLfloat after_loacation[16];

void drawPoints(point_t points[], int length) {

    for (int i = 0; i < length; ++i) {
        glPointSize(points[i].size);
        glPushMatrix();
            glTranslatef(points[i].x, points[i].y, points[i].z);
        glColor3f(points[i].c.red, points[i].c.red, points[i].c.red);
        gluSphere(quadric, 0.005f, 30, 30);
        glPopMatrix();
        
    }
}

void drawCube()
{

    glBegin(GL_QUADS);
        // Front
        glTexCoord2f(1.0, 1.0); // right-right
        glVertex3f(-2.0f, 0.0f, 2.0f);
	    glTexCoord2f(0.0, 1.0); // right-right
        glVertex3f( 2.0f, 0.0f, 2.0f);
	    glTexCoord2f(0.0, 0.0); // right-right
        glVertex3f( 2.0f, 3.0f, 2.0f);
	    glTexCoord2f(1.0, 0.0); // right-right
        glVertex3f(-2.0f, 3.0f, 2.0f);

        // Back
        glTexCoord2f(1.0, 1.0); // right-right
        glVertex3f(-2.0f, 0.0f, -2.0f);
	    glTexCoord2f(0.0, 1.0); // right-right
        glVertex3f( 2.0f, 0.0f, -2.0f);
	    glTexCoord2f(0.0, 0.0); // right-right
        glVertex3f( 2.0f, 3.0f, -2.0f);
	    glTexCoord2f(1.0, 0.0); // right-right
        glVertex3f(-2.0f, 3.0f, -2.0f);

        // Left
        glTexCoord2f(1.0, 1.0); // right-right
        glVertex3f(-2.0f, 0.0f, -2.0f);
	    glTexCoord2f(0.0, 1.0); // right-right
        glVertex3f(-2.0f, 0.0f,  2.0f);
	    glTexCoord2f(0.0, 0.0); // right-right
        glVertex3f(-2.0f, 3.0f,  2.0f);
	    glTexCoord2f(1.0, 0.0); // right-right
        glVertex3f(-2.0f, 3.0f, -2.0f);

        // Right
        glTexCoord2f(1.0, 1.0); // right-right
        glVertex3f(2.0f, 0.0f, -2.0f);
	    glTexCoord2f(0.0, 1.0); // right-right
        glVertex3f(2.0f, 0.0f,  2.0f);
	    glTexCoord2f(0.0, 0.0); // right-right
        glVertex3f(2.0f, 3.0f,  2.0f);
	    glTexCoord2f(1.0, 0.0); // right-right
        glVertex3f(2.0f, 3.0f, -2.0f);

        // Top
        glTexCoord2f(1.0, 1.0); // right-right
        glVertex3f(-2.0f, 3.0f,  2.0f);
	    glTexCoord2f(0.0, 1.0); // right-right
        glVertex3f( 2.0f, 3.0f,  2.0f);
	    glTexCoord2f(0.0, 0.0); // right-right
        glVertex3f( 2.0f, 3.0f, -2.0f);
	    glTexCoord2f(1.0, 0.0); // right-right
        glVertex3f(-2.0f, 3.0f, -2.0f);
        

    glEnd();

}

void drawTriangle()
{
    glBegin(GL_TRIANGLES);
        // Front
        glBegin(GL_TRIANGLES);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 0.0f);
        glEnd();
    glEnd();

}

void drawQuad()
{
    glBegin(GL_QUADS);
        glTexCoord2f(1.0, 1.0); // right-right
	    glVertex3f(1.0f, 1.0f, 0.0f);
	    glTexCoord2f(0.0, 1.0); // right-right
	    glVertex3f(-1.0f, 1.0f, 0.0f);
	    glTexCoord2f(0.0, 0.0); // right-right
	    glVertex3f(-1.0f, -1.0f, 0.0f);
	    glTexCoord2f(1.0, 0.0); // right-right
	    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}

void drawButterFlyQuad()
{
    glBegin(GL_QUADS);
        glTexCoord2f(1.0, 1.0); // right-right
	    glVertex3f(1.0f, 1.0f, 0.0f);
	    glTexCoord2f(0.0, 1.0); // right-right
	    glVertex3f(0.0f, 1.0f, 0.0f);
	    glTexCoord2f(0.0, 0.0); // right-right
	    glVertex3f(0.0f, 0.0f, 0.0f);
	    glTexCoord2f(1.0, 0.0); // right-right
	    glVertex3f(1.0f, 0.0f, 0.0f);
    glEnd();
    
}