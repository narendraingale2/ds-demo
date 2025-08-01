#include "shape.h"
#include "POINTS.h"


void drawPoints(point_t points[], int length) {

    //glEnable(GL_POINT_SMOOTH);
    //glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

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
    /*glBegin(GL_TRIANGLES);
        // Front
        glVertex3f(-2.0f, 3.0f, 2.0f);
        glVertex3f( 2.0f, 3.0f, 2.0f);
        glVertex3f( 0.0f, 5.0f, 2.0f);

        // Back
        glVertex3f(-2.0f, 3.0f, -2.0f);
        glVertex3f( 2.0f, 3.0f, -2.0f);
        glVertex3f( 0.0f, 5.0f, -2.0f);
    glEnd();

    glBegin(GL_QUADS);
        // Left roof side
        glVertex3f(-2.0f, 3.0f, -2.0f);
        glVertex3f(-2.0f, 3.0f,  2.0f);
        glVertex3f( 0.0f, 5.0f,  2.0f);
        glVertex3f( 0.0f, 5.0f, -2.0f);

        // Right roof side
        glVertex3f(2.0f, 3.0f, -2.0f);
        glVertex3f(2.0f, 3.0f,  2.0f);
        glVertex3f(0.0f, 5.0f,  2.0f);
        glVertex3f(0.0f, 5.0f, -2.0f);
    glEnd();*/
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