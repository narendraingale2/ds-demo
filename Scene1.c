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
extern BOOL animateEye;
extern BOOL rotate_left;
extern GLfloat girl_walk_z;
extern GLfloat girl_walk_y;

void drawScene1()
{

    // Drawing stars
    glPushMatrix();
        drawPoints(point_vertices, 800);
    glPopMatrix();

    // Drawing moon
    glPushMatrix();
        glTranslatef(5.0f, 4.5f, -6.0f);
        drawMoon();
    glPopMatrix();
}

void drawScene2()
{
    // back wall
    glTranslatef(0.0f, 0.0f, -8.0f);
    glPushMatrix();
		glTranslatef(0.0f, 0.0f, -16.0f);
        glScalef(20.0f, 10.0f, 1.0f);
        //glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, texture_inner_wall);
        drawQuad();
        glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    // side wall
    glPushMatrix();
		glTranslatef(-10.0f, 0.0f, -6.0f);
        glScalef(8.0f, 8.0f, 1.0f);
        glRotatef(75.0f, 0.0f, 1.0f, 0.0f);
        glColor4f(166.0f/255.0f, 194.0f/255.0f, 170.0f/255.0f, 1.0f);
        drawQuad();
    glPopMatrix();

    // side wall
    glPushMatrix();
		glTranslatef(10.0f, 0.0f, -6.0f);
        glScalef(8.0f, 8.0f, 1.0f);
        glRotatef(-75.0f, 0.0f, 1.0f, 0.0f);
        glColor4f(166.0f/255.0f, 194.0f/255.0f, 170.0f/255.0f, 1.0f);
        drawQuad();
    glPopMatrix();

    // floor
    glPushMatrix();
		glTranslatef(0.0f, -5.0f, -8.0f);
        glScalef(20.0f, 40.0f, 1.0f);
        glRotatef(-88.0f, 1.0f, 0.0f, 0.0f);
        glColor4f(150.0f/255.0f, 75.0f/255.0f, 0.0f, 1.0f);
        drawQuad();
    glPopMatrix();

    // draw girl
    glPushMatrix();
        /*if(animateEye == TRUE)
            glRotatef(20, 0.0f, 1.0f, 0.0f);
        else
            glRotatef(-20, 0.0f, 1.0f, 0.0f);
        */
		glTranslatef(2.0f, -2.0f, -6.2f);
        glScalef(0.4f, 0.5f, 1.0f);
        /*if(animateEye == TRUE)
            glRotatef(30, 0.0f, 1.0f, 0.0f);
        else
            glRotatef(-30, 0.0f, 1.0f, 0.0f);
       */ 
        /*if(rotate_left == TRUE)
            glRotatef(30, 0.0f, 1.0f, 0.0f);
        else 
            glRotatef(-10, 0.0f, 1.0f, 0.0f);
        */
        glTranslatef(0.0f, girl_walk_y, girl_walk_z);
        if(animateEye == TRUE)
            drawGirl(TRUE);
        else 
            drawGirl(FALSE);
    glPopMatrix();

}

void drawScene3()
{

			glPushMatrix();
				drawScene1();
			glPopMatrix();

            glPushMatrix();
                glTranslatef(0.0f, -1.0f, 0.0f);
                glScalef(0.4f, 0.2f, 1.0f);
                if(animateEye == TRUE)
                    drawGirl(TRUE);
                else 
                    drawGirl(FALSE);
            glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0f, -2.0f, 0.0f);
				glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
				glScalef(8.0f, 2.0f, 1.0f);
				drawGround();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(4.0f, 0.6f, 0.0f);
				glScalef(4.0, 6.0f, 0.0f);
				drawColoredTree();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-5.0f, 0.5f, 0.0f);
				glScalef(4.0, 6.0f, 0.0f);
				drawCocoTree();
			glPopMatrix();

    
}