
#include<stdio.h>
#include "model.h"
#include "utility.h"
#include "shape.h"
extern GLuint texture_colured_tree;
void drawMoon()
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindTexture(GL_TEXTURE_2D, texture_moon);
	gluQuadricTexture(quadric, GL_TRUE); 
	gluSphere(quadric, 0.5, 50, 50);
	glBindTexture(GL_TEXTURE_2D, 0);
	gluQuadricTexture(quadric, GL_FALSE);
}

void drawColoredTree()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // face
    glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture_colured_tree);
	glBegin(GL_QUADS);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(2.0f, 2.0f, 0.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-2.0f, 2.0f, 0.0f);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-2.0f, -2.0f, 0.0f);
		
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(2.0f, -2.0f, 0.0f);

	glEnd();

}