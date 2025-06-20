
#include<stdio.h>
#include "model.h"
#include "utility.h"
#include "shape.h"

void drawMoon()
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluQuadricTexture(quadric, GL_TRUE); 
	glBindTexture(GL_TEXTURE_2D, texture_moon);
	gluSphere(quadric, 0.5, 50, 50);
	glBindTexture(GL_TEXTURE_2D, 0);
}