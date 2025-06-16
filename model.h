#include<windows.h>

// OpenGl realated header files
#include<gl/GL.h>
#include<gl/GLU.h>
extern GLUquadric *quadric;
extern GLuint texture_moon;

void drawMoon()
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluQuadricTexture(quadric, GL_TRUE); 
	glBindTexture(GL_TEXTURE_2D, texture_moon);
	gluSphere(quadric, 0.5, 50, 50);
	glBindTexture(GL_TEXTURE_2D, 0);
}