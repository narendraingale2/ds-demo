#include<windows.h>
#include<stdio.h>

#include "shape.h"
#include "POINTS.h"
extern FILE *gpFile;
extern GLfloat location[16];
GLfloat after_loacation[16];
extern point_t* star_points;
extern int numStars;

void drawPoints(int length) {
    void initializePoints();

    if(star_points == NULL)
    {
        initializePoints(star_points, numStars);
        if(star_points == NULL)
        {
            fprintf(gpFile, "Star Initialization failed\n");
        }
    }


    for (int i = 0; i < numStars; ++i) {
        glPointSize(star_points[i].size);
        glPushMatrix();
            glTranslatef(star_points[i].x, star_points[i].y, star_points[i].z);
        glColor3f(star_points[i].c.red, star_points[i].c.red, star_points[i].c.red);
        gluSphere(quadric, 0.005f, 30, 30);
        glPopMatrix();
        
    }
    
    fprintf(gpFile, "Stars plotted...\n");
}

void initializePoints()
{    
    star_points = (point_t*)malloc(sizeof(point_t) * numStars);

    for(int i = 0; i<numStars; i++)	
    {
    	star_points[i].x = getRandomCoord(-10.0f, 8.0f);
    	star_points[i].y = getRandomCoord(1.0f, 5.0f);
    	star_points[i].z = getRandomCoord(-10.0f, -3.0f);
    	float color = getRandomCoord(05, 0.1);
    	star_points[i].c.red = color;
    	star_points[i].c.blue = color;
    	star_points[i].c.red = color;
    	float size = getRandomCoord(1.0f, 3.0f);
    	star_points[i].size = size;
    }


}

void uninitializeStars()
{
    if(star_points != NULL)
    {
        free(star_points);
        star_points = NULL;
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