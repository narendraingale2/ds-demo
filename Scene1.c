#include<stdio.h>

#include "model.h"
#include "utility.h"
#include "shape.h"

extern GLfloat cameraZ;
extern FILE *gpFile;
extern point_t point_vertices[100];
extern BOOL gbRotateBoy;
extern GLfloat boyAngle;
extern GLfloat location[16];
extern GLuint texture_inner_wall;

void drawScene1()
{

    // Drawing stars
    glPushMatrix();
        drawPoints(point_vertices, 800);
    glPopMatrix();

    // Drawing moon
    glPushMatrix();
        glTranslatef(5.0f, 4.5f, -6.0f);
        //glRotatef(-110.0f, 0.0f, 1.0f, 0.0f);
        //glRotatef(-180.0f, 0.0f, 0.0f, 1.0f);
	    for(int i = 0; i<16; i++)
            fprintf(gpFile,"location[%d] = %f\n",i, location[i]);
        drawMoon();
    glPopMatrix();
}

void drawScene2()
{
    // back wall
    glPushMatrix();
		glTranslatef(0.0f, 0.0f, -16.0f);
        glScalef(8.0f, 7.0f, 1.0f);
        //glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, texture_inner_wall);
        drawQuad();
        glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    // side wall
    glPushMatrix();
		glTranslatef(-5.0f, 0.0f, -8.0f);
        glScalef(2.0f, 4.0f, 1.0f);
        glRotatef(75.0f, 0.0f, 1.0f, 0.0f);
        glColor4f(166.0f/255.0f, 194.0f/255.0f, 170.0f/255.0f, 1.0f);
        drawQuad();
    glPopMatrix();

    // side wall
    glPushMatrix();
		glTranslatef(5.0f, 0.0f, -8.0f);
        glScalef(2.0f, 4.0f, 1.0f);
        glRotatef(-75.0f, 0.0f, 1.0f, 0.0f);
        glColor4f(166.0f/255.0f, 194.0f/255.0f, 170.0f/255.0f, 1.0f);
        drawQuad();
    glPopMatrix();

    // floor
    glPushMatrix();
		glTranslatef(0.0f, -4.0f, -8.0f);
        glScalef(8.0f, 6.0f, 1.0f);
        glRotatef(-80.0f, 1.0f, 0.0f, 0.0f);
        glColor4f(150.0f/255.0f, 75.0f/255.0f, 0.0f, 1.0f);
        drawQuad();
    glPopMatrix();

    // draw girl
    glPushMatrix();
        if(gbRotateBoy == TRUE)
            glRotatef(boyAngle, 0.0f, 1.0f, 0.0f);
		glTranslatef(2.0f, -1.5f, -6.2f);
        glScalef(0.4f, 0.5f, 1.0f);
        glRotatef(30, 0.0f, 1.0f, 0.0f);
        drawGirl();
    glPopMatrix();

}