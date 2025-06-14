#include<windows.h>

// OpenGl realated header files
#include<gl/GL.h>
#include<gl/GLU.h>
extern GLUquadric *quadric;

void drawMoon()
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluSphere(quadric, 0.3, 50, 50);
}