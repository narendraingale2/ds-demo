
#include<stdio.h>
#include "model.h"
#include "utility.h"
#include "shape.h"

void drawMoon()
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindTexture(GL_TEXTURE_2D, texture_moon);
	gluQuadricTexture(quadric, GL_TRUE); 
	gluSphere(quadric, 0.5, 50, 50);
	glBindTexture(GL_TEXTURE_2D, 0);
	gluQuadricTexture(quadric, GL_FALSE);
}